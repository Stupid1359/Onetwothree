#ifndef BASICCALCULATOR_H
#define BASICCALCULATOR_H

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

// ====================== 基本运算模块 ======================

class BasicCalculator
{
private:
	// 运算符优先级
	static int getPriority(char op);

	// 执行基本运算
	static double applyOp(double a, double b, char op);

public:
	// 计算表达式（支持加减乘除和次方）
	static double calculateExpression(const string &expr);

	// 次方运算
	static double power(double base, double exponent);
	static long long power(long long base, long long exponent, long long mod = 1000000000);

	// 开方运算
	static double squareRoot(double num);

	// 对数运算
	static double logarithm(double num, double base = 2.718281828);

	// 三角函数
	static double sinFunc(double x, bool rad);

	static double cosFunc(double x, bool rad);

	static double tanFunc(double x, bool rad);

	static double arcsinFunc(double x, bool rad);

	static double arccosFunc(double x, bool rad);

	static double arctanFunc(double x, bool rad);

	static double sinhFunc(double x, bool rad);

	static double coshFunc(double x, bool rad);

	static double tanhFunc(double x, bool rad);

	// 阶乘
	static vector<int> factorial(int n);

	// 倒数
	static double reciprocal(double num);
};

#endif