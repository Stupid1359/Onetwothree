#include "BasicCalculator.h"
#include "AdvancedCalculator.h"
#include "UnitConverter.h"
#include "UtilityTools.h"

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

// ====================== 辅助函数 ======================

// 去除字符串两端的空格
string trim(const string &str)
{
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

// 检查字符串是否为数字
bool isNumber(const string &s)
{
	if (s.empty())
		return false;
	size_t i = 0;

	// 处理正负号
	if (s[0] == '-' || s[0] == '+')
	{
		i++;
		if (i == s.length())
			return false; // 只有符号不是数字
	}

	bool hasDecimal = false;
	for (; i < s.length(); i++)
	{
		if (s[i] == '.')
		{
			if (hasDecimal)
				return false; // 多个小数点
			hasDecimal = true;
		}
		else if (!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}

// ====================== 用户界面与交互 ======================
void displayMainMenu()
{
	cout << endl;
	cout << "=-=-=-=-== 多功能计算器 ==-=-=-=-=" << endl;
	cout << "+           1. 基本运算          +" << endl;
	cout << "+           2. 高级运算          +" << endl;
	cout << "+           3. 单位换算          +" << endl;
	cout << "+           4. 实用工具          +" << endl;
	cout << "+           0. 退出              +" << endl;
	cout << "=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=" << endl;
	cout << "请选择功能: ";
}

void displayBasicCalcMenu()
{
	cout << endl;
	cout << "=-=-=-=-=-== 基本运算 ==-=-=-=-=-=" << endl;
	cout << "+   1. 四则运算 (支持括号和次方) +" << endl;
	cout << "+   2. 次方运算 (x^y)            +" << endl;
	cout << "+   3. 开方运算 (√x)             +" << endl;
	cout << "+   4. 对数运算 (lg, ln)         +" << endl;
	cout << "+   5. 三角函数 (sin,cos,tan..)  +" << endl;
	cout << "+   6. 阶乘 (x!)                 +" << endl;
	cout << "+   7. 倒数 (1/x)                +" << endl;
	cout << "+   8. 返回主菜单                +" << endl;
	cout << "=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=" << endl;
	cout << "请选择功能: ";
}

void displayAdvancedCalcMenu()
{
	cout << endl;
	cout << "=-=-=-=-=-== 高级运算 ==-=-=-=-=-=" << endl;
	cout << "+         1. 大数运算            +" << endl;
	cout << "+         2. 方程求解            +" << endl;
	cout << "+         3. 矩阵运算            +" << endl;
	cout << "+         4. 求质数              +" << endl;
	cout << "+         5. 求约数              +" << endl;
	cout << "+         6. 求组合数            +" << endl;
	cout << "+         7. 求斐波那契数        +" << endl;
	cout << "+         8. 求GCD和LCM          +" << endl;
	cout << "+         9. 返回主菜单          +" << endl;
	cout << "=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=" << endl;
	cout << "请选择功能: ";
}

void displayUnitConversionMenu()
{
	cout << endl;
	cout << "=-=-=-=-=-== 单位换算 ==-=-=-=-=-=" << endl;
	cout << "+         1. 长度转换            +" << endl;
	cout << "+         2. 重量转换            +" << endl;
	cout << "+         3. 面积转换            +" << endl;
	cout << "+         4. 体积转换            +" << endl;
	cout << "+         5. 速度转换            +" << endl;
	cout << "+         6. 温度转换            +" << endl;
	cout << "+         7. 时间转换            +" << endl;
	cout << "+         8. 返回主菜单          +" << endl;
	cout << "=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=" << endl;
	cout << "请选择功能: ";
}

void displayUtilityMenu()
{
	cout << endl;
	cout << "=-=-=-=-=-== 实用工具 ==-=-=-=-=-=" << endl;
	cout << "+         1. 进制转换            +" << endl;
	cout << "+         2. BMI计算             +" << endl;
	cout << "+         3. 数字转大写中文      +" << endl;
	cout << "+         4. 返回主菜单          +" << endl;
	cout << "=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=" << endl;
	cout << "请选择功能: ";
}

void clearInputBuffer()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ====================== 主函数 ======================
int main()
{
	int choice;
	do
	{
		displayMainMenu();
		cin >> choice;

		if (cin.fail())
		{
			cout << "输入无效，请输入数字！" << endl;
			clearInputBuffer();
			continue;
		}

		system("cls");

		switch (choice)
		{
		case 1:
		{ // 基本运算
			int basicChoice;
			do
			{
				displayBasicCalcMenu();
				cin >> basicChoice;
				clearInputBuffer();

				if (cin.fail())
				{
					cout << "输入无效，请输入数字！" << endl;
					clearInputBuffer();
					continue;
				}

				try
				{
					switch (basicChoice)
					{
					case 1:
					{ // 四则运算
						cout << "请输入表达式 (例如: 3+4*(5-2)): " << endl;
						string expr;
						getline(cin, expr);
						expr = trim(expr);
						double result = BasicCalculator::calculateExpression(expr);
						cout << "结果: " << expr << " = " << result << endl;
						system("pause");
						system("cls");
						break;
					}
					case 2:
					{ // 次方运算
						double base, exponent;
						cout << "请输入底数: ";
						cin >> base;
						cout << "请输入指数: ";
						cin >> exponent;
						if (base == 0 && exponent == 0)
							cout << "指数和底数不能均为0" << endl;
						else
						{
							if (floor(base) == base && floor(exponent) == exponent && base > 0 && exponent > 0)
							{
								long long baseInt = static_cast<long long>(base);
								long long exponentInt = static_cast<long long>(exponent);
								long long result = BasicCalculator::power(baseInt, exponentInt);
								cout << "结果: " << baseInt << "^" << exponentInt << " = " << result << " (mod 1e9)" << endl;
							}
							else
							{
								double result = BasicCalculator::power(base, exponent);
								cout << "结果: " << base << "^" << exponent << " = " << result << endl;
							}
						}
						system("pause");
						system("cls");
						break;
					}
					case 3:
					{ // 开方运算
						double num;
						cout << "请输入数字: ";
						cin >> num;
						if (num < 0)
							cout << "不能对负数开平方" << endl;
						else
						{
							double result = BasicCalculator::squareRoot(num);
							cout << "结果: √" << num << " = " << result << endl;
						}
						system("pause");
						system("cls");
						break;
					}
					case 4:
					{ // 对数运算
						double num, base;
						cout << "请输入数字: ";
						cin >> num;
						cout << "请输入底数(输入0使用自然对数): ";
						cin >> base;
						double result;
						if (num <= 0)
						{
							cout << "对数参数必须为正数" << endl;
						}
						else if (base < 0 || base == 1)
						{
							cout << "对数底数必须为正数且不等于1" << endl;
						}
						else if (base == 0)
						{
							result = BasicCalculator::logarithm(num);
							cout << "结果: ln(" << num << ") = " << result << endl;
						}
						else if (base == 10)
						{
							result = BasicCalculator::logarithm(num, base);
							cout << "结果: lg(" << num << ") = " << result << endl;
						}
						else
						{
							result = BasicCalculator::logarithm(num, base);
							cout << "结果: log_" << base << "(" << num << ") = " << result << endl;
						}
						system("pause");
						system("cls");
						break;
					}
					case 5:
					{ // 三角函数
						cout << "1.sin 2.cos 3.tan 4.arcsin 5.arccos 6.arctan" << endl;
						cout << "7.sinh 8.cosh 9.tanh ";
						int trigChoice;
						cout << "请选择函数: ";
						cin >> trigChoice;
						int rad;
						cout << "请选择 1.弧度 2.角度: ";
						cin >> rad;
						
						if (trigChoice < 1 || trigChoice > 9 || rad < 1 || rad > 2)
						{
							cout << "无效的函数或无效的弧度/角度" << endl;
							system("pause");
							system("cls");
							break;
						}
						rad = (rad == 1) ? 1 : 0;
						double x;
						cout << "请输入弧度/角度: ";
						cin >> x;
						double result;
						string funcName;
						switch (trigChoice)
						{
						case 1:
							result = BasicCalculator::sinFunc(x, rad);
							funcName = "sin";
							break;
						case 2:
							result = BasicCalculator::cosFunc(x, rad);
							funcName = "cos";
							break;
						case 3:
							result = BasicCalculator::tanFunc(x, rad);
							funcName = "tan";
							break;
						case 4:
							result = BasicCalculator::arcsinFunc(x, rad);
							funcName = "arcsin";
							break;
						case 5:
							result = BasicCalculator::arccosFunc(x, rad);
							funcName = "arccos";
							break;
						case 6:
							result = BasicCalculator::arctanFunc(x, rad);
							funcName = "arctan";
							break;
						case 7:
							result = BasicCalculator::sinhFunc(x, rad);
							funcName = "sinh";
							break;
						case 8:
							result = BasicCalculator::coshFunc(x, rad);
							funcName = "cosh";
							break;
						case 9:
							result = BasicCalculator::tanhFunc(x, rad);
							funcName = "tanh";
							break;
						default:
							cout << "无效选择！" << endl;
							continue;
						}
						cout << "结果: " << funcName << "(" << x << ") = " << result << endl;
						system("pause");
						system("cls");
						break;
					}
					case 6:
					{ // 阶乘
						int n;
						cout << "请输入整数(0-10000): ";
						cin >> n;
						if (n < 0)
							cout << "阶乘参数不能为负数" << endl;
						else if (n > 10000)
							cout << "数值过大" << endl;
						else
						{
							vector<int> result = BasicCalculator::factorial(n);
							cout << "结果: " << n << "! = ";
							for (int i = result.size() - 1; i >= 0; i--)
								cout << result[i];
							cout << endl;
						}
						system("pause");
						system("cls");
						break;
					}
					case 7:
					{ // 倒数
						double num;
						cout << "请输入数字: ";
						cin >> num;
						if (num == 0)
							cout << "零没有倒数" << endl;
						else
						{
							double result = BasicCalculator::reciprocal(num);
							cout << "结果: 1/" << num << " = " << result << endl;
						}
						system("pause");
						system("cls");
						break;
					}
					case 8: // 返回主菜单
						system("cls");
						break;
					default:
						cout << "无效选择，请重新输入！" << endl;
						system("pause");
						system("cls");
					}
				}
				catch (const exception &e)
				{
					cout << "错误: " << e.what() << endl;
				}
			} while (basicChoice != 8);
			break;
		}
		case 2:
		{
			int advancedChoice;
			do
			{
				displayAdvancedCalcMenu();
				cin >> advancedChoice;
				clearInputBuffer();

				if (cin.fail())
				{
					cout << "输入无效，请输入数字！" << endl;
					clearInputBuffer();
					continue;
				}

				try
				{
					string biga, bigb, oper;
					int n;
					switch (advancedChoice)
					{
					case 1: // 大数运算
					{
						cout << "支持的运算符: +, -, *, /, %" << endl;
						cout << "请输入第一个大数: ";
						getline(cin, biga);
						biga = trim(biga);
						cout << "请输入操作符: ";
						getline(cin, oper);
						oper = trim(oper);
						cout << "请输入第二个大数: ";
						getline(cin, bigb);
						bigb = trim(bigb);
						if (isNumber(biga) && isNumber(bigb))
							cout << "结果: " << biga << endl
								 << "    " << oper << " "
								 << bigb << endl
								 << "   == " << BigInt::calculate(biga, bigb, oper) << endl;
						else
							cout << "大数无效,请重新输入! " << endl;
						system("pause");
						system("cls");
						break;
					}
					case 2: // 方程求解
					{
						int n;
						cout << "请输入多项式的次数 n : ";
						cin >> n;
						vector<double> a(n + 1);
						cout << "请输入 " << n + 1 << " 个系数（从最高次项到常数项）: ";
						for (int i = 0; i <= n; i++)
						{
							cin >> a[i];
						}
						double x;
						cout << "请输入与该根接近的一个数: ";
						cin >> x;

						// 构造多项式表达式字符串
						string expr;
						for (int i = 0; i <= n; i++)
						{
							double coef = a[i];
							int exp = n - i;
							if (fabs(coef) < 1e-8)
								continue; // 跳过0系数

							// 符号
							if (!expr.empty())
								expr += (coef > 0 ? " + " : " - ");
							else if (coef < 0)
								expr += "-";

							coef = fabs(coef);

							// 系数部分（省略1除非是常数项）
							if (coef != 1 || exp == 0)
								expr += to_string(coef);

							// 幂部分
							if (exp > 0)
							{
								expr += "x";
								if (exp > 1)
									expr += "^" + to_string(exp);
							}
						}

						double root = FormulaSolve::solve(n, a, x);
						cout << "方程 " << expr << " 的一个近似实根为: " << root << endl;
						system("pause");
						system("cls");
						break;
					}
					case 3: // 矩阵运算
					{
						cout << "支持的操作：+, -, * " << endl;
						int r1, c1, r2, c2;
						cout << "请输入第一个矩阵的行数和列数: ";
						cin >> r1 >> c1;
						vector<vector<int>> A(r1, vector<int>(c1));
						cout << "请输入第一个矩阵的元素\n";
						for (int i = 0; i < r1; i++)
						{
							for (int j = 0; j < c1; j++)
							{
								cin >> A[i][j];
							}
						}

						cout << "请输入第二个矩阵的行数和列数: ";
						cin >> r2 >> c2;
						vector<vector<int>> B(r2, vector<int>(c2));
						cout << "请输入第二个矩阵的元素\n";
						for (int i = 0; i < r2; i++)
						{
							for (int j = 0; j < c2; j++)
							{
								cin >> B[i][j];
							}
						}

						string op;
						cout << "请输入操作符(+,-,*): ";
						cin >> op;

						try
						{
							vector<vector<int>> result = MatrixCalc::calculate(r1, c1, r2, c2, op, A, B);
							cout << "\n结果矩阵: " << endl;
							MatrixCalc::printMatrix(result);
						}
						catch (exception &e)
						{
							cout << "\n错误: " << e.what() << endl;
						}
						system("pause");
						system("cls");
						break;
					}
					case 4: // 求质数
					{
						int n;
						cout << "请输入一个正整数 n:" << endl;
						cin >> n;

						if (n < 2)
						{
							cout << "没有质数" << endl;
						}
						else
						{
							PrimeSieve sieve(n);
							cout << "\n2 到 " << n << " 之间的质数如下: " << endl;
							sieve.print();
						}
						system("pause");
						system("cls");
						break;
					}
					case 5: // 求约数
					{
						int x;
						cout << "请输入一个正整数：";
						cin >> x;

						if (x <= 0)
						{
							cout << "输入必须是正整数" << endl;
						}
						else
						{
							vector<int> divisors = DivisorTool::get_divisors(x);
							cout << x << " 的所有约数如下："
								 << "(共 " << divisors.size() << " 个)" << endl;
							DivisorTool::print(divisors);
						}
						system("pause");
						system("cls");
						break;
					}
					case 6: // 求组合数
					{
						int n, k;
						cout << "请输入两个整数 n 和 k (计算 C(n, k) ): ";
						cin >> n >> k;
						if (n < 0 || k < 0)
							cout << "n 和 k 必须为正整数" << endl;
						else if (k > n)
							cout << "k 不得大于 n" << endl;
						else
						{
							Combination comb(n);
							cout << "C(" << n << ", " << k << ") ≡  "
								 << comb.get(n, k) << " (mod 1e9+7)" << endl;
						}
						system("pause");
						system("cls");
						break;
					}
					case 7: // 求斐波那契数
					{
						long long n;
						cout << "请输入一个整数 n, 计算斐波那契数 F(n): ";
						cin >> n;

						Fibonacci fib;
						cout << "F(" << n << ") = "
							 << fib.get(n) << " (mod 1e9+7)" << endl;
						system("pause");
						system("cls");
						break;
					}
					case 8: // 求GCD和LCM
					{
						long long a, b;
						cout << "请输入两个整数 a 和 b: ";
						cin >> a >> b;

						cout << "gcd(" << a << ", " << b << ") = "
							 << GCDandLCM::gcd(a, b) << endl;
						cout << "lcm(" << a << ", " << b << ") = "
							 << GCDandLCM::lcm(a, b) << endl;
						system("pause");
						system("cls");
						break;
					}
					case 9: // 返回主菜单
						system("cls");
						break;
					default:
						cout << "无效选择，请重新输入！" << endl;
						system("pause");
						system("cls");
					}
				}
				catch (const exception &e)
				{
					cout << "错误: " << e.what() << endl;
				}
			} while (advancedChoice != 9);
			break;
		}
		case 3:
		{ // 单位换算
			int unitChoice;
			do
			{
				displayUnitConversionMenu();
				cin >> unitChoice;

				if (cin.fail())
				{
					cout << "输入无效，请输入数字！" << endl;
					clearInputBuffer();
					continue;
				}

				try
				{
					double value;
					string fromUnit;

					switch (unitChoice)
					{
					case 1: // 长度转换

						cout << "支持的单位: m, cm, mm, km, in, ft, yd, mi" << endl;
						cout << "请输入长度(如1.0ft): ";
						cin >> value >> fromUnit;
						UnitConverter::convertLength(value, fromUnit);
						system("pause");
						system("cls");
						break;
					case 2: // 重量转换
						cout << "支持的单位: kg, g, mg, lb, oz" << endl;
						cout << "请输入重量(如1.0lb): ";
						cin >> value >> fromUnit;
						UnitConverter::convertWeight(value, fromUnit);
						system("pause");
						system("cls");
						break;
					case 3: // 面积转换
						cout << "支持的单位: m2, cm2, km2, ha, acre, ft2, in2" << endl;
						cout << "请输入面积(如1.0acre): ";
						cin >> value >> fromUnit;
						UnitConverter::convertArea(value, fromUnit);
						system("pause");
						system("cls");
						break;
					case 4: // 体积转换
						cout << "支持的单位: m3, L, mL, gal, pt, ft3, in3 " << endl;
						cout << "请输入体积(如1.0gal): ";
						cin >> value >> fromUnit;
						UnitConverter::convertVolume(value, fromUnit);
						system("pause");
						system("cls");
						break;
					case 5: // 速度转换
						cout << "支持的单位: m/s, km/h, mph, ft/s, knot" << endl;
						cout << "请输入速度(如1.0mph): ";
						cin >> value >> fromUnit;
						UnitConverter::convertSpeed(value, fromUnit);
						system("pause");
						system("cls");
						break;
					case 6: // 温度转换
						cout << "支持的单位: C/℃ (摄氏), F/℉ (华氏), K (开尔文)" << endl;
						cout << "请输入温度(如1.0K): ";
						cin >> value >> fromUnit;
						UnitConverter::convertTemperature(value, fromUnit);
						system("pause");
						system("cls");
						break;
					case 7: // 时间转换
						cout << "支持的单位: s, ms, min, h, day, week, year" << endl;
						cout << "请输入时间(如1.0h): ";
						cin >> value >> fromUnit;
						UnitConverter::convertTime(value, fromUnit);
						system("pause");
						system("cls");
						break;
					case 8: // 返回主菜单
						system("cls");
						break;
					default:
						cout << "无效选择，请重新输入！" << endl;
						system("pause");
						system("cls");
					}
				}
				catch (const exception &e)
				{
					cout << "错误: " << e.what() << endl;
				}
				clearInputBuffer();
			} while (unitChoice != 8);
			break;
		}
		case 4:
		{ // 实用工具
			int utilityChoice;
			do
			{
				displayUtilityMenu();
				cin >> utilityChoice;

				if (cin.fail())
				{
					cout << "输入无效，请输入数字！" << endl;
					clearInputBuffer();
					continue;
				}

				try
				{
					switch (utilityChoice)
					{
					case 1:
					{ // 进制转换
						string number;
						int fromBase, toBase;
						cout << "请输入数字: ";
						cin >> number;
						cout << "请输入原进制(2-36): ";
						cin >> fromBase;
						cout << "请输入目标进制(2-36): ";
						cin >> toBase;
						string result = UtilityTools::convertBase(number, fromBase, toBase);
						cout << "结果: " << number << " (base " << fromBase << ") = "
							 << result << " (base " << toBase << ")" << endl;
						system("pause");
						system("cls");
						break;
					}
					case 2:
					{ // BMI计算
						clearInputBuffer();
						string unit;
						cout << "请输入单位(kg/m 或 lb/in): ";
						getline(cin, unit);
						unit = trim(unit);

						double weight, height;
						cout << "请输入体重: ";
						cin >> weight;
						cout << "请输入身高: ";
						cin >> height;
						double bmi;
						if (unit.empty() || unit == "kg/m")
						{
							bmi = UtilityTools::calculateBMI(weight, height);
						}
						else if (unit == "lb/in")
						{
							bmi = UtilityTools::calculateBMI(weight, height, "lb");
						}
						else
						{
							cout << "无效的单位, 使用kg/m计算" << endl;
							bmi = UtilityTools::calculateBMI(weight, height);
						}

						cout << "BMI结果: " << fixed << setprecision(2) << bmi << " (";
						if (bmi < 18.5)
							cout << "偏瘦";
						else if (bmi < 24)
							cout << "正常";
						else if (bmi < 28)
							cout << "超重";
						else if (bmi < 30)
							cout << "轻度肥胖";
						else if (bmi < 35)
							cout << "中度肥胖";
						else
							cout << "重度肥胖";
						cout << ")" << endl;
						system("pause");
						system("cls");
						break;
					}
					case 3:
					{ // 数字转大写中文
						double num;
						cout << "请输入数字(0-999999999999.99): ";
						cin >> num;
						clearInputBuffer();
						string result = UtilityTools::numberToChinese(num);
						cout << "大写中文: " << result << endl;
						system("pause");
						system("cls");
						break;
					}
					case 4: // 返回主菜单
						system("cls");
						break;
					default:
						cout << "无效选择，请重新输入！" << endl;
						system("pause");
						system("cls");
					}
				}
				catch (const exception &e)
				{
					cout << "错误: " << e.what() << endl;
				}
				// clearInputBuffer();
			} while (utilityChoice != 4);
			break;
		}
		case 0: // 退出
			system("cls");
			cout << "感谢使用，再见！" << endl;
			system("pause");
			break;
		default:
			cout << "无效选择，请重新输入！" << endl;
			system("pause");
			system("cls");
		}
	} while (choice != 0);

	return 0;
}