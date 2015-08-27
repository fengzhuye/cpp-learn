#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>

#define DEBUG

#ifdef DEBUG
#define MSG(message, args...) printk(KERN_DEBUG "irq:" message, ##args)
#else
#define MSG(message, args...)
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("guowei");

int irq;
char *interface;

// 下面这2个参数通过插入内核模块的时候赋值的...
module_param(irq, int, 0644);
module_param(interface, charp, 0644);

// 中断捕获的时候的处理函数
int irq_handle_function(int irq, void *device_id)
{
	static int count = 1;
	MSG("[%d]receive the irq at %ld.../n", count, jiffies);
	count++;
	return IRQ_NONE;
}

int init_module()
{
	// 注册中断捕获，第三个参数的意思是和其他设备共享该中断号，最后一个参数是设备的id，其实对于共享下的设备这个号码据说是随便写，一般都写irq的了。
	//只要注册成功就可以等待对应设备的该中断号的到来 就可以处理回调函数了。。
	if(request_irq(irq, irq_handle_function, IRQF_SHARED, interface, (void *)&irq))
	{
		MSG("regist irq failure.../n");
		return -EIO;
	}
	MSG("interface=%s and irq=%d.../n", interface, irq);
	MSG("regist irq success.../n");
	return 0;
}

void cleanup_module()
{
	free_irq(irq, &irq);
	MSG("unregist irq.../n");
}



