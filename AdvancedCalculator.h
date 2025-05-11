#ifndef ADVANCEDCALCULATOR_H
#define ADVANCEDCALCULATOR_H

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

// ====================== 高级运算模块 ======================

// ----------------------------------------------------------
// ------------------------ 大数运算 ------------------------
class BigInt
{
public:
    vector<int> digits;
    bool negative = false;

    BigInt();

    BigInt(string num);

    BigInt(const vector<int> &d, bool neg = false);

    void trim();

    string toString() const;

    bool abs_less(const BigInt &b) const;

    bool operator<(const BigInt &b) const;

    bool operator==(const BigInt &b) const;

    bool operator<=(const BigInt &b) const;

    bool operator>(const BigInt &b) const;

    BigInt operator-() const;

    static vector<int> add(const vector<int> &a, const vector<int> &b);

    static vector<int> sub(const vector<int> &a, const vector<int> &b);

    BigInt operator+(const BigInt &b) const;

    BigInt operator-(const BigInt &b) const;

    BigInt operator*(const BigInt &b) const;

    BigInt divmod(const BigInt &b, BigInt &rem) const;

    BigInt operator/(const BigInt &b) const;

    BigInt operator%(const BigInt &b) const;

    static string calculate(const string &a, const string &b, const string &op);
};

// ----------------------------------------------------------
// ------------------------ 方程求解 ------------------------
class FormulaSolve
{
public:
    // 计算多项式值 f(x)
    static double poly(const vector<double> &a, double x);

    // 计算导数值 f'(x)
    static double deriv(const vector<double> &a, double x);

    // 牛顿迭代法求近似根
    static double solve(int n, const vector<double> &a, double x = 1.0, int max_iter = 100, double eps = 1e-8);
};

// ----------------------------------------------------------
// ------------------------ 矩阵运算 ------------------------
class MatrixCalc
{
public:
    static vector<vector<int>> calculate(int r1, int c1, int r2, int c2, const string &op, const vector<vector<int>> &A, const vector<vector<int>> &B);

    static void printMatrix(const vector<vector<int>> &M);
};

// ----------------------------------------------------------
// ------------------------- 求质数 -------------------------
class PrimeSieve
{
private:
    vector<int> primes; // 存储所有质数
    vector<bool> st;    // 表示 i 是否被筛掉
    int n;

public:
    PrimeSieve(int limit);

    void get_primes();

    void print(int perLine = 10) const;
};

// ----------------------------------------------------------
// ------------------------- 求约数 -------------------------
class DivisorTool
{
public:
    static vector<int> get_divisors(int x);

    static void print(const vector<int> &divisors, int perLine = 10);
};

// ----------------------------------------------------------
// ------------------------ 求组合数 ------------------------
class Combination
{
private:
    long long mod;
    vector<long long> fact;     // 阶乘数组
    vector<long long> inv_fact; // 逆元阶乘数组

    // 计算 a^b % mod
    long long power(long long a, long long b);

public:
    Combination(int n, long long m = 1e9 + 7);

    long long get(int n, int k);
};

// ----------------------------------------------------------
// ---------------------- 求斐波那契数 ----------------------
class Fibonacci
{
private:
    struct Matrix
    {
        long long m[2][2];
        static long long mod;

        Matrix();

        static Matrix identity();

        static Matrix base();

        Matrix operator*(const Matrix &b) const;
    };

    Matrix fastpow(Matrix a, long long n);

public:
    Fibonacci(long long m = 1e9 + 7);

    long long get(long long n);
};

// ----------------------------------------------------------
// ----------------------- 求GCD和LCM -----------------------
class GCDandLCM
{
public:
    // 最大公约数
    static long long gcd(long long a, long long b);

    // 最小公倍数
    static long long lcm(long long a, long long b);
};

#endif