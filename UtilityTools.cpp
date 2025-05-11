#include "UtilityTools.h"

#include <iostream>  // 输入输出流
#include <cmath>     // 数学函数库
#include <string>    // 字符串处理
#include <map>       // 映射容器
#include <vector>    // 动态数组容器
#include <iomanip>   // 输入输出格式化
#include <sstream>   // 字符串流
#include <stack>     // 栈容器
#include <cctype>    // 字符处理函数
#include <algorithm> // 算法函数
#include <stdexcept> // 标准异常
#include <limits>    // 数值限制

using namespace std; // 使用标准命名空间

// ====================== 实用工具模块 ======================

// 进制转换
string UtilityTools::convertBase(const string &number, int fromBase, int toBase)
{
    if (fromBase < 2 || fromBase > 36 || toBase < 2 || toBase > 36)
    {
        throw runtime_error("进制范围必须在2-36之间");
    }

    // 先将输入数转换为十进制
    long long decimal = 0;
    for (char c : number)
    {
        int digit;
        if (isdigit(c))
        {
            digit = c - '0';
        }
        else if (isalpha(c))
        {
            digit = toupper(c) - 'A' + 10;
        }
        else
        {
            throw runtime_error("无效的数字字符");
        }

        if (digit >= fromBase)
        {
            throw runtime_error("数字字符超出源进制范围");
        }

        decimal = decimal * fromBase + digit;
    }

    // 处理0的特殊情况
    if (decimal == 0)
        return "0";

    // 将十进制数转换为目标进制
    string result;
    while (decimal > 0)
    {
        int digit = decimal % toBase;
        char c;
        if (digit < 10)
        {
            c = '0' + digit;
        }
        else
        {
            c = 'A' + digit - 10;
        }
        result = c + result;
        decimal /= toBase;
    }

    return result;
}

// BMI计算
double UtilityTools::calculateBMI(double weight, double height, const string &unit)
{
    if (weight <= 0 || height <= 0)
    {
        throw runtime_error("体重和身高必须为正数");
    }

    if (unit == "kg")
    {
        // 公斤和米
        return weight / (height * height);
    }
    else if (unit == "lb")
    {
        // 磅和英寸
        return (weight / (height * height)) * 703;
    }
    else
    {
        throw runtime_error("无效的单位, 使用kg或lb");
    }
}

// 数字转大写中文
const vector<string> UtilityTools::chineseDigits = {
    "零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};
const vector<string> UtilityTools::chineseUnits = {
    "", "拾", "佰", "仟", "万", "拾", "佰", "仟", "亿", "拾", "佰", "仟", "兆"};
string UtilityTools::numberToChinese(double num)
{
    if (num < 0 || num > 999999999999.99)
    {
        throw runtime_error("数字超出转换范围(0-999999999999.99)");
    }

    // 分离整数和小数部分
    long long integerPart = static_cast<long long>(num);
    int decimalPart = static_cast<int>((num - integerPart) * 100 + 0.5); // 四舍五入到两位小数

    if (integerPart == 0 && decimalPart == 0)
        return "零元整";

    string result;

    // 处理整数部分
    if (integerPart > 0)
    {
        vector<int> sections;
        while (integerPart > 0)
        {
            sections.push_back(integerPart % 10000);
            integerPart /= 10000;
        }

        for (int i = sections.size() - 1; i >= 0; i--)
        {
            int section = sections[i];
            if (section == 0)
            {
                if (!result.empty())
                    result += "零";
                continue;
            }

            string sectionStr = convertSection(section);
            result += sectionStr;

            // 添加节权位
            if (i > 0)
            {
                result += chineseUnits[i + 3]; // 万,亿,兆
            }
        }

        result += "元";
    }

    // 处理小数部分
    if (decimalPart > 0)
    {
        int jiao = decimalPart / 10;
        int fen = decimalPart % 10;

        if (jiao > 0)
        {
            result += chineseDigits[jiao] + "角";
        }
        if (fen > 0)
        {
            result += chineseDigits[fen] + "分";
        }
    }
    else
    {
        result += "整";
    }

    return result;
}

// 转换一个节(4位数)为中文
string UtilityTools::convertSection(int section)
{
    string result;
    int qian = section / 1000;
    int bai = (section % 1000) / 100;
    int shi = (section % 100) / 10;
    int ge = section % 10;

    if (qian > 0)
    {
        result += chineseDigits[qian] + "仟";
    }

    if (bai > 0)
    {
        result += chineseDigits[bai] + "佰";
    }
    else if (!result.empty() && (shi > 0 || ge > 0))
    {
        result += "零";
    }

    if (shi > 0)
    {
        if (shi != 1 || !result.empty())
        { // 避免"一十"变成"十"
            result += chineseDigits[shi];
        }
        result += "拾";
    }
    else if (!result.empty() && ge > 0)
    {
        result += "零";
    }

    if (ge > 0)
    {
        result += chineseDigits[ge];
    }

    return result;
}