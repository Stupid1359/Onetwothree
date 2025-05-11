#ifndef UNITCONVERTER_H
#define UNITCONVERTER_H

#include <iostream>	 // 输入输出流
#include <cmath>	 // 数学函数库
#include <string>	 // 字符串处理
#include <map>		 // 映射容器
#include <vector>	 // 动态数组容器
#include <iomanip>	 // 输入输出格式化
#include <sstream>	 // 字符串流
#include <stack>	 // 栈容器
#include <cctype>	 // 字符处理函数
#include <algorithm> // 算法函数
#include <stdexcept> // 标准异常
#include <limits>	 // 数值限制

using namespace std; // 使用标准命名空间

// ====================== 单位换算模块 ======================

class UnitConverter
{
private:
	// 单位转换因子映射表
	static map<string, double> lengthUnits; // 长度单位
	static map<string, double> weightUnits; // 重量单位
	static map<string, double> areaUnits;	// 面积单位
	static map<string, double> volumeUnits; // 体积单位
	static map<string, double> speedUnits;	// 速度单位
	static map<string, double> timeUnits;	// 时间单位
	// 单位名称
	static vector<string> tolengthUnits; // 长度单位
	static vector<string> toweightUnits; // 重量单位
	static vector<string> toareaUnits;	 // 面积单位
	static vector<string> tovolumeUnits; // 体积单位
	static vector<string> tospeedUnits;	 // 速度单位
	static vector<string> totimeUnits;	 // 时间单位

	// 初始化单位转换因子
	static void initializeUnits();

public:
	// 长度转换
	static void convertLength(double value, const string &fromUnit);

	// 重量转换
	static void convertWeight(double value, const string &fromUnit);

	// 面积转换
	static void convertArea(double value, const string &fromUnit);

	// 体积转换
	static void convertVolume(double value, const string &fromUnit);

	// 速度转换
	static void convertSpeed(double value, const string &fromUnit);

	// 温度转换
	static void convertTemperature(double value, const string &fromUnit);

	// 时间转换
	static void convertTime(double value, const string &fromUnit);
};

#endif