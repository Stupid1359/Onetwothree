#include "BasicCalculator.h"

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

// 运算符优先级
int BasicCalculator::getPriority(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	if (op == '^')
		return 3;
	return 0;
}

// 执行基本运算
double BasicCalculator::applyOp(double a, double b, char op)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0)
			throw runtime_error("除数不能为零");
		return a / b;
	case '^':
		return pow(a, b);
	default:
		throw runtime_error("无效运算符");
	}
}

// 计算表达式
double BasicCalculator::calculateExpression(const string &expr)
{
	stack<double> values;
	stack<char> ops;

	for (size_t i = 0; i < expr.length(); i++)
	{
		if (expr[i] == ' ')
			continue;

		if (expr[i] == '(')
		{
			ops.push(expr[i]);
		}
		else if (expr[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();
				char op = ops.top();
				ops.pop();
				values.push(applyOp(val1, val2, op));
			}
			if (!ops.empty())
				ops.pop(); // 弹出 '('
		}
		else if (isdigit(expr[i]))
		{
			string numStr;
			while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.'))
			{
				numStr += expr[i++];
			}
			i--;
			values.push(stod(numStr));
		}
		else
		{
			while (!ops.empty() && getPriority(ops.top()) >= getPriority(expr[i]))
			{
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();
				char op = ops.top();
				ops.pop();
				values.push(applyOp(val1, val2, op));
			}
			ops.push(expr[i]);
		}
	}

	while (!ops.empty())
	{
		double val2 = values.top();
		values.pop();
		double val1 = values.top();
		values.pop();
		char op = ops.top();
		ops.pop();
		values.push(applyOp(val1, val2, op));
	}

	return values.top();
}

// 次方运算
double BasicCalculator::power(double base, double exponent)
{
	return pow(base, exponent);
}
long long BasicCalculator::power(long long base, long long exponent, long long mod)
{
	base %= mod;
	long long result = 1;
	while (exponent > 0)
	{
		if (exponent & 1)
			result = 1ll * result * base % mod;
		base = 1ll * base * base % mod;
		exponent >>= 1;
	}
	return result;
}

// 开方运算
double BasicCalculator::squareRoot(double num)
{
	return sqrt(num);
}

// 对数运算
double BasicCalculator::logarithm(double num, double base)
{
	return log(num) / log(base);
}

// 三角函数
double BasicCalculator::sinFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	return sin(x);
}

double BasicCalculator::cosFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	return cos(x);
}

double BasicCalculator::tanFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	return tan(x);
}

double BasicCalculator::arcsinFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	if (x < -1 || x > 1)
	{
		cout << "arcsin 定义域是 [-1, 1]" << endl;
		return NAN;
	}
	return asin(x);
}

double BasicCalculator::arccosFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	if (x < -1 || x > 1)
	{
		cout << "arccos 定义域是 [-1, 1]" << endl;
		return NAN;
	}
	return acos(x);
}

double BasicCalculator::arctanFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	return atan(x);
}

double BasicCalculator::sinhFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	return sinh(x);
}

double BasicCalculator::coshFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	return cosh(x);
}

double BasicCalculator::tanhFunc(double x, bool rad)
{
	if (!rad)
		x = x * M_PI / 180.0;
	return tanh(x);
}

// 阶乘
vector<int> BasicCalculator::factorial(int n)
{
	vector<int> A(1, 1);
	vector<int> B;
	int t = 0;
	for (int b = 1; b <= n; b++)
	{
		B.clear();
		for (int i = 0; i < A.size() || t; i++)
		{
			if (i < A.size())
				t += A[i] * b;
			B.push_back(t % 10);
			t /= 10;
		}
		while (B.size() > 1 && B.back() == 0)
			B.pop_back();
		A = B;
	}
	return A;
}

// 倒数
double BasicCalculator::reciprocal(double num)
{
	return 1.0 / num;
}