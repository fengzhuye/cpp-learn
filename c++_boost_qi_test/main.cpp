#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
using namespace boost::spirit;
int main()
{
    std::string cmd_str = "$AAA[BBB ][ 2 ] == 123  ";
    // 用于保存解析的各个字段
    std::string component_name;
    std::string variable_name;
    int vector_index = -1; // 如果非vector则默认为-1
    std::string target_value;
    std::vector<char> v;
    double time_out = 0.0;
    
    
    std::string::iterator iter_begin = cmd_str.begin();
    bool parse_ok = qi::phrase_parse(iter_begin, cmd_str.end(),
            // WAIT指令规则： WAIT $AAA[BBB][index] = true TIMEOUT 1.23
            // 其中非vector系统变量没有index项， TIMEOUT项可省略，也可以将TIMEOUT字段放在系统变量前
            //  Begin grammar
            (
                     ('$'
                     >>(+(qi::char_ - '[' - ascii::blank)[boost::phoenix::ref( component_name ) += qi::_1])  // 这里将获得系统变量AAA部分
                     >> '['
                     >> (+(qi::char_ - ']' - ascii::blank)[boost::phoenix::ref( variable_name ) += qi::_1])  // BBB部分
                     >> ']'
                     >> -('[' >> qi::int_[boost::phoenix::ref(vector_index) = qi::_1] >> ']'))  // index部分（如果存在）
                     >> lit("==")
                     >> qi::lexeme[(+(qi::char_-lit("TIMEOUT") - ascii::blank)[boost::phoenix::ref( target_value ) += qi::_1])][boost::phoenix::ref( v ) = qi::_1]
                     ^
                    (-(lit("TIMEOUT") >> qi::double_[boost::phoenix::ref(time_out) = qi::_1]))  // TIMEOUT值（如果存在）
            ),
            //  End grammar
            ascii::space  // skip the space
            );
    // 判断是否解析成功，语法不对会导致解析失败并输出错误信息
    if (!parse_ok || iter_begin != cmd_str.end())
    {
        std::cout << "Not good!" << std::endl;
        std::cout << component_name << "_" << variable_name << "_" << vector_index << std::endl; 
        std::cout << target_value << "_" << std::string(v.begin(),v.end()) << std::endl; 
    }
    else
    {
       std::cout << component_name << "_" << variable_name << "_" << vector_index << std::endl; 
       std::cout << target_value << "_" << std::string(v.begin(),v.end()) << std::endl; 
    }
    return 0;
}
