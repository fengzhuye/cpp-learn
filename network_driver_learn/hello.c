#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/ip.h>

/* for in_device, in_ifaddr */
#include <linux/inetdevice.h>

MODULE_AUTHOR("Brook");
MODULE_DESCRIPTION("Kernel module for demo");
MODULE_LICENSE("GPL");

#define MAX_ETH_FRAME_SIZE   1792
struct nic_priv {
    /* you can use array to queue more packet */
    unsigned char *tx_buf;
    unsigned int  tx_len;
    u32           msg_enable;
};

static struct net_device *nic_dev[2];
/* netif msg type, defined in netdevice.h
    NETIF_MSG_DRV           = 0x0001,
    NETIF_MSG_PROBE         = 0x0002,
    NETIF_MSG_LINK          = 0x0004,
    NETIF_MSG_TIMER         = 0x0008,
    NETIF_MSG_IFDOWN        = 0x0010,
    NETIF_MSG_IFUP          = 0x0020,
    NETIF_MSG_RX_ERR        = 0x0040,
    NETIF_MSG_TX_ERR        = 0x0080,
    NETIF_MSG_TX_QUEUED     = 0x0100,
    NETIF_MSG_INTR          = 0x0200,
    NETIF_MSG_TX_DONE       = 0x0400,
    NETIF_MSG_RX_STATUS     = 0x0800,
    NETIF_MSG_PKTDATA       = 0x1000,
    NETIF_MSG_HW            = 0x2000,
    NETIF_MSG_WOL           = 0x4000,
*/
#define DEF_MSG_ENABLE 0xffff

static void dump(unsigned char *buf)
{
    unsigned char *p, sbuf[2*(sizeof(struct ethhdr) + sizeof(struct iphdr))];
    int i;
    p = sbuf;

    for(i = 0; i < sizeof(struct ethhdr); i++) {
        p += sprintf(p, "%02X ", buf[i]);
    }
    printk("eth %s\n", sbuf);

    p = sbuf;
    for(i = 0; i < sizeof(struct iphdr); i++) {
        p += sprintf(p, "%02X ", buf[sizeof(struct ethhdr) + i]);
    }
    printk("iph %s\n", sbuf);

    p = sbuf;
    for(i = 0; i < 4; i++) {
        p += sprintf(p, "%02X ", buf[sizeof(struct ethhdr) + sizeof(struct iphdr) + i]);
    }
    printk("payload %s\n", sbuf);
}


static void
nic_rx(struct net_device *netdev, int len, unsigned char *buf)
{
    struct sk_buff *skb;
    struct nic_priv *priv = netdev_priv(netdev);

    netif_info(priv, hw, netdev, "%s(#%d), rx:%d\n",
                __func__, __LINE__, len);
    /*
     * The packet has been retrieved from the transmission
     * medium. Build an skb around it, so upper layers can handle it
     */
    skb = dev_alloc_skb(len + 2);
    if (!skb) {
        netif_err(priv, rx_err, netdev,
                  "%s(#%d), rx: low on mem - packet dropped\n",
                  __func__, __LINE__);
        netdev->stats.rx_dropped++;
        return;
    }
    skb_reserve(skb, 2); /* align IP on 16B boundary */
    memcpy(skb_put(skb, len), buf, len);

    /* Write metadata, and then pass to the receive level */
    skb->dev = netdev;
    skb->protocol = eth_type_trans(skb, netdev);
    skb->ip_summed = CHECKSUM_UNNECESSARY; /* don't check it */
    netdev->stats.rx_packets++;
    netdev->stats.rx_bytes += len;
    netif_rx(skb);
}

static int nic_open(struct net_device *netdev)
{
    struct nic_priv *priv = netdev_priv(netdev);
    netif_info(priv, ifup, netdev, "%s(#%d), priv:%p\n",
                __func__, __LINE__, priv);
    /* may be using DMA */
    priv->tx_buf = kmalloc(MAX_ETH_FRAME_SIZE, GFP_KERNEL);
    if (priv->tx_buf == NULL) {
        netif_info(priv, ifup, netdev, "%s(#%d), cannot alloc tx buf\n",
                    __func__, __LINE__);
        return -ENOMEM;
    }
    netif_start_queue(netdev);
    return 0;
}

static int nic_close(struct net_device *netdev)
{
    struct nic_priv *priv = netdev_priv(netdev);
    netif_info(priv, ifdown, netdev, "%s(#%d), priv:%p\n",
                __func__, __LINE__, priv);
    netif_stop_queue(netdev);
    return 0;
}

static void nic_hw_xmit(struct net_device *netdev)
{
    struct nic_priv *priv = netdev_priv(netdev);
    struct iphdr *iph;
    u32 *saddr, *daddr;
    struct in_device* in_dev;
    struct in_ifaddr* if_info;

    if (priv->tx_len < sizeof(struct ethhdr) + sizeof(struct iphdr)) {
        netif_info(priv, hw, netdev, "%s(#%d), too short\n",
                   __func__, __LINE__);
        return;
    }
    dump(priv->tx_buf);
    iph = (struct iphdr *)(priv->tx_buf + sizeof(struct ethhdr));
    saddr = &iph->saddr;
    daddr = &iph->daddr;

    netif_info(priv, hw, netdev, "%s(#%d), orig, src:%pI4, dst:%pI4, len:%d\n",
                __func__, __LINE__, saddr, daddr, priv->tx_len);

    in_dev = nic_dev[(netdev == nic_dev[0] ? 1 : 0)]->ip_ptr;
    if (in_dev) {
        if_info = in_dev->ifa_list;
        for (if_info = in_dev->ifa_list; if_info; if_info=if_info->ifa_next) {
#if 0
            printk("label:%s, address=%pI4\n",
               if_info->ifa_label, &if_info->ifa_address);
#endif
            *saddr = *daddr = if_info->ifa_address;
            ((u8 *)saddr)[3]++;
            netif_info(priv, hw, netdev, "%s(#%d), new, src:%pI4, dst:%pI4\n",
                        __func__, __LINE__, saddr, daddr);
            break;
        }
        if (!if_info) {
            /* drop packet */
            netdev->stats.tx_dropped++;
            netif_info(priv, hw, netdev, "%s(#%d), drop packet\n",
                        __func__, __LINE__);
            return;
        }
    }

    iph->check = 0;         /* and rebuild the checksum (ip needs it) */
    iph->check = ip_fast_csum((unsigned char *)iph, iph->ihl);

    netdev->stats.tx_packets++;
    netdev->stats.tx_bytes += priv->tx_len;

    nic_rx(nic_dev[(netdev == nic_dev[0] ? 1 : 0)], priv->tx_len, priv->tx_buf);
}

static netdev_tx_t nic_start_xmit(struct sk_buff *skb,
                                  struct net_device *netdev)
{
    struct nic_priv *priv = netdev_priv(netdev);
    netif_info(priv, drv, netdev, "%s(#%d), orig, src:%pI4, dst:%pI4\n",
                __func__, __LINE__, &(ip_hdr(skb)->saddr), &(ip_hdr(skb)->daddr));
    priv->tx_len = skb->len;
    if (likely(priv->tx_len < MAX_ETH_FRAME_SIZE)) {
        if (priv->tx_len < ETH_ZLEN) {
            memset(priv->tx_buf, 0, ETH_ZLEN);
            priv->tx_len = ETH_ZLEN;
        }
        skb_copy_and_csum_dev(skb, priv->tx_buf);
        dev_kfree_skb_any(skb);
    } else {
        dev_kfree_skb_any(skb);
        netdev->stats.tx_dropped++;
        return NETDEV_TX_OK;
    }

    nic_hw_xmit(netdev);
    return NETDEV_TX_OK;
}

static int nic_validate_addr(struct net_device *netdev)
{
    struct nic_priv *priv = netdev_priv(netdev);
    netif_info(priv, drv, netdev, "%s(#%d), priv:%p\n",
                __func__, __LINE__, priv);
    return eth_validate_addr(netdev);
}

static int nic_change_mtu(struct net_device *netdev, int new_mtu)
{
    struct nic_priv *priv = netdev_priv(netdev);
    netif_info(priv, drv, netdev, "%s(#%d), priv:%p\n",
                __func__, __LINE__, priv);
    return eth_change_mtu(netdev, new_mtu);
}

static int nic_set_mac_addr(struct net_device *netdev, void *addr)
{
    struct nic_priv *priv = netdev_priv(netdev);
    netif_info(priv, drv, netdev, "%s(#%d), priv:%p\n",
                __func__, __LINE__, priv);
    return eth_mac_addr(netdev, addr);
}

/*
 * This function is called to fill up an eth header, since arp is not
 * available on the interface
 */
int snull_header(struct sk_buff *skb, struct net_device *netdev,
                unsigned short type, const void *daddr, const void *saddr,
                unsigned len)
{
    struct nic_priv *priv = netdev_priv(netdev);
    struct ethhdr *eth = (struct ethhdr *)skb_push(skb, ETH_HLEN);
    struct net_device *dst_netdev;

    netif_info(priv, drv, netdev, "%s(#%d)\n",
                __func__, __LINE__);
    dst_netdev = nic_dev[(netdev == nic_dev[0] ? 1 : 0)];
    eth->h_proto = htons(type);
    memcpy(eth->h_source, saddr ? saddr : netdev->dev_addr, netdev->addr_len);
    memcpy(eth->h_dest, dst_netdev->dev_addr, dst_netdev->addr_len);
    return (netdev->hard_header_len);
}

static const struct header_ops snull_header_ops = {
        .create  = snull_header,
};

static const struct net_device_ops nic_netdev_ops = {
    /* Kernel calls ndo_open() and ndo_validate_addr()
     * when you bring up the NIC
     */
    .ndo_open               = nic_open,
    .ndo_validate_addr      = nic_validate_addr,

    /* when you shut down the NIC, kernel call the .ndo_stop() */
    .ndo_stop               = nic_close,

    /* Kernel calls ndo_start_xmit() when it wants to 
     *   transmit a packet. 
     */
    .ndo_start_xmit         = nic_start_xmit,

    /* ndo_change_mtu() is called, when you change MTU */
    .ndo_change_mtu         = nic_change_mtu,

    /* ndo_set_mac_address() is called,
     *   when you change the MAC addr
     */
    .ndo_set_mac_address    = nic_set_mac_addr,
};

static struct net_device* nic_alloc_netdev(void)
{
    struct net_device *netdev;

    netdev = alloc_etherdev(sizeof(struct nic_priv));
    if (!netdev) {
        pr_err("%s(#%d): alloc dev failed",
               __func__, __LINE__);
        return NULL;
    }
    eth_hw_addr_random(netdev);
    netdev->netdev_ops = &nic_netdev_ops;

    /* keep the default flags, just add NOARP */
    netdev->flags |= IFF_NOARP;

    /* There are no explicit users, so this is 
     *     now equivalent to NETIF_F_HW_CSUM. */
    netdev->features |= NETIF_F_HW_CSUM;

    netdev->header_ops = &snull_header_ops;

    return netdev;
}

static int __init brook_init(void)
{
    int ret;
    struct nic_priv *priv;

    nic_dev[0] = nic_alloc_netdev();
    if (!nic_dev[0]) {
        pr_err("%s(#%d): alloc netdev[0] failed", __func__, __LINE__);
        return -ENOMEM;
    }

    nic_dev[1] = nic_alloc_netdev();
    if (!nic_dev[1]) {
        pr_err("%s(#%d): alloc netdev[1] failed", __func__, __LINE__);
        ret = -ENOMEM;
        goto alloc_2nd_failed;
    }

    ret = register_netdev(nic_dev[0]);
    if (ret) {
        pr_err("%s(#%d): reg net driver failed. ret:%d",
               __func__, __LINE__, ret);
        goto reg1_failed;
    }

    ret = register_netdev(nic_dev[1]);
    if (ret) {
        pr_err("%s(#%d): reg net driver failed. ret:%d",
               __func__, __LINE__, ret);
        goto reg2_failed;
    }

    priv = netdev_priv(nic_dev[0]);
    priv->msg_enable = DEF_MSG_ENABLE;
    priv = netdev_priv(nic_dev[1]);
    priv->msg_enable = DEF_MSG_ENABLE;
    return 0;

reg2_failed:
    unregister_netdev(nic_dev[0]);
reg1_failed:
    free_netdev(nic_dev[1]);
alloc_2nd_failed:
    free_netdev(nic_dev[0]);
    return ret;
}
module_init(brook_init);

static void __exit brook_exit(void)
{
    int i;
    pr_info("%s(#%d): remove module", __func__, __LINE__);
    for (i = 0; i < ARRAY_SIZE(nic_dev); i++) {
        unregister_netdev(nic_dev[i]);
        free_netdev(nic_dev[i]);
    }
}
module_exit(brook_exit);
