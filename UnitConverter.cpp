#include "UnitConverter.h"

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

// ====================== 单位换算模块 ======================

// 静态成员变量定义
map<string, double> UnitConverter::lengthUnits;
map<string, double> UnitConverter::weightUnits;
map<string, double> UnitConverter::areaUnits;
map<string, double> UnitConverter::volumeUnits;
map<string, double> UnitConverter::speedUnits;
map<string, double> UnitConverter::timeUnits;
vector<string> UnitConverter::tolengthUnits = {"mm", "cm", "m", "km", "in", "ft", "yd", "mi"};
vector<string> UnitConverter::toweightUnits = {"mg", "g", "kg", "lb", "oz"};
vector<string> UnitConverter::toareaUnits = {"cm2", "m2", "km2", "ha", "acre", "ft2", "in2"};
vector<string> UnitConverter::tovolumeUnits = {"mL", "L", "m3", "gal", "pt", "ft3", "in3"};
vector<string> UnitConverter::tospeedUnits = {"m/s", "km/h", "mph", "ft/s", "knot"};
vector<string> UnitConverter::totimeUnits = {"ms", "s", "min", "h", "day", "week", "year"};
// 初始化单位转换因子
void UnitConverter::initializeUnits()
{
    static bool initalized = false;
    if (initalized)
        return;
        
    // 长度单位：以米为基准
    lengthUnits["m"] = 1.0;      // 米
    lengthUnits["cm"] = 0.01;    // 厘米
    lengthUnits["mm"] = 0.001;   // 毫米
    lengthUnits["km"] = 1000.0;  // 千米
    lengthUnits["in"] = 0.0254;  // 英寸
    lengthUnits["ft"] = 0.3048;  // 英尺
    lengthUnits["yd"] = 0.9144;  // 码
    lengthUnits["mi"] = 1609.34; // 英里

    // 重量单位：以千克为基准
    weightUnits["kg"] = 1.0;       // 千克
    weightUnits["g"] = 0.001;      // 克
    weightUnits["mg"] = 0.000001;  // 毫克
    weightUnits["lb"] = 0.453592;  // 磅
    weightUnits["oz"] = 0.0283495; // 盎司

    // 面积单位：以平方米为基准
    areaUnits["m2"] = 1.0;         // 平方米
    areaUnits["cm2"] = 0.0001;     // 平方厘米
    areaUnits["km2"] = 1000000.0;  // 平方千米
    areaUnits["ha"] = 10000.0;     // 公顷
    areaUnits["acre"] = 4046.86;   // 英亩
    areaUnits["ft2"] = 0.092903;   // 平方英尺
    areaUnits["in2"] = 0.00064516; // 平方英寸

    // 体积单位：以立方米为基准
    volumeUnits["m3"] = 1.0;           // 立方米
    volumeUnits["L"] = 0.001;          // 升
    volumeUnits["mL"] = 0.000001;      // 毫升
    volumeUnits["gal"] = 0.00378541;   // 加仑
    volumeUnits["pt"] = 0.000473176;   // 品脱
    volumeUnits["ft3"] = 0.0283168;    // 立方英尺
    volumeUnits["in3"] = 0.0000163871; // 立方英寸

    // 速度单位：以米/秒为基准
    speedUnits["m/s"] = 1.0;       // 米/秒
    speedUnits["km/h"] = 0.277778; // 千米/小时
    speedUnits["mph"] = 0.44704;   // 英里/小时
    speedUnits["ft/s"] = 0.3048;   // 英尺/秒
    speedUnits["knot"] = 0.514444; // 节

    // 时间单位：以秒为基准
    timeUnits["s"] = 1.0;           // 秒
    timeUnits["ms"] = 0.001;        // 毫秒
    timeUnits["min"] = 60.0;        // 分钟
    timeUnits["h"] = 3600.0;        // 小时
    timeUnits["day"] = 86400.0;     // 天
    timeUnits["week"] = 604800.0;   // 周
    timeUnits["year"] = 31536000.0; // 年(非闰年)
}

// 长度转换
void UnitConverter::convertLength(double value, const string &fromUnit)
{
    initializeUnits();
    if (lengthUnits.find(fromUnit) == lengthUnits.end())
    {
        cout<<"无效的长度单位\n";
        return;
    }
    for (int i = 1; i < tolengthUnits.size(); i++)
    {
        cout << value << " " << fromUnit << " = "
             << value * lengthUnits[fromUnit] / lengthUnits[tolengthUnits[i]]
             << " " << tolengthUnits[i] << endl;
    }
}

// 重量转换
void UnitConverter::convertWeight(double value, const string &fromUnit)
{
    initializeUnits();
    if (weightUnits.find(fromUnit) == weightUnits.end())
    {
        throw runtime_error("无效的重量单位");
        return;
    }
    for (int i = 1; i < toweightUnits.size(); i++)
    {
        cout << value << " " << fromUnit << " = "
             << value * weightUnits[fromUnit] / weightUnits[toweightUnits[i]]
             << " " << toweightUnits[i] << endl;
    }
}

// 面积转换
void UnitConverter::convertArea(double value, const string &fromUnit)
{
    initializeUnits();
    if (areaUnits.find(fromUnit) == areaUnits.end())
    {
        throw runtime_error("无效的面积单位");
        return;
    }
    for (int i = 1; i < toareaUnits.size(); i++)
    {
        cout << value << " " << fromUnit << " = "
             << value * areaUnits[fromUnit] / areaUnits[toareaUnits[i]]
             << " " << toareaUnits[i] << endl;
    }
}

// 体积转换
void UnitConverter::convertVolume(double value, const string &fromUnit)
{
    initializeUnits();
    if (volumeUnits.find(fromUnit) == volumeUnits.end())
    {
        throw runtime_error("无效的体积单位");
        return;
    }
    for (int i = 1; i < tovolumeUnits.size(); i++)
    {
        cout << value << " " << fromUnit << " = "
             << value * volumeUnits[fromUnit] / volumeUnits[tovolumeUnits[i]]
             << " " << tovolumeUnits[i] << endl;
    }
}

// 速度转换
void UnitConverter::convertSpeed(double value, const string &fromUnit)
{
    initializeUnits();
    if (speedUnits.find(fromUnit) == speedUnits.end())
    {
        throw runtime_error("无效的速度单位");
        return;
    }
    for (int i = 1; i < tospeedUnits.size(); i++)
    {
        cout << value << " " << fromUnit << " = "
             << value * speedUnits[fromUnit] / speedUnits[tospeedUnits[i]]
             << " " << tospeedUnits[i] << endl;
    }
}

// 温度转换
void UnitConverter::convertTemperature(double value, const string &fromUnit)
{
    string from = fromUnit;
    transform(from.begin(), from.end(), from.begin(), ::toupper);

    // 先将所有温度转换为摄氏度
    double celsius;
    if (from == "C" || from == "℃" || from=="c")
    {
        celsius = value;
    }
    else if (from == "F" || from == "℉"||from=="f")
    {
        celsius = (value - 32) * 5 / 9;
    }
    else if (from == "K"||from=="k")
    {
        celsius = value - 273.15;
    }
    else
    {
        throw runtime_error("无效的温度单位");
        return;
    }

    // 从摄氏度转换为目标单位
    cout << value << " " << fromUnit << " = "
         << celsius << " " << "C" << endl;
    cout << value << " " << fromUnit << " = "
         << celsius * 9 / 5 + 32 << " " << "F" << endl;
    cout << value << " " << fromUnit << " = "
         << celsius + 273.15 << " " << "K" << endl;
}

// 时间转换
void UnitConverter::convertTime(double value, const string &fromUnit)
{
    initializeUnits();
    if (timeUnits.find(fromUnit) == timeUnits.end())
    {
        throw runtime_error("无效的时间单位");
        return;
    }
    for (int i = 1; i < totimeUnits.size(); i++)
    {
        cout << value << " " << fromUnit << " = "
             << value * timeUnits[fromUnit] / timeUnits[totimeUnits[i]]
             << " " << totimeUnits[i] << endl;
    }
}