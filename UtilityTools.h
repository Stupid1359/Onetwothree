#ifndef UTILITYTOOLS_H
#define UTILITYTOOLS_H

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

// ====================== 实用工具模块 ======================

class UtilityTools
{
private:
	// 数字对应的大写中文
	static const vector<string> chineseDigits;
	static const vector<string> chineseUnits;

public:
	// 进制转换
	static string convertBase(const string &number, int fromBase, int toBase);

	// BMI计算
	static double calculateBMI(double weight, double height, const string &unit = "kg");

	// 数字转大写中文
	static string numberToChinese(double num);

private:
	// 转换一个节(4位数)为中文
	static string convertSection(int section);
};

#endif