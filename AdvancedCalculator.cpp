#include "AdvancedCalculator.h"

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
BigInt::BigInt() {}

BigInt::BigInt(string num)
{
    if (num[0] == '-')
    {
        negative = true;
        num = num.substr(1);
    }
    for (int i = num.size() - 1; i >= 0; i--)
        digits.push_back(num[i] - '0');
    trim();
}

BigInt::BigInt(const vector<int> &d, bool neg) : digits(d), negative(neg)
{
    trim();
}

void BigInt::trim()
{
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
    if (digits.size() == 1 && digits[0] == 0)
        negative = false;
}

string BigInt::toString() const
{
    string s = negative ? "-" : "";
    for (int i = digits.size() - 1; i >= 0; i--)
        s += digits[i] + '0';
    return s;
}

bool BigInt::abs_less(const BigInt &b) const
{
    if (digits.size() != b.digits.size())
        return digits.size() < b.digits.size();
    for (int i = digits.size() - 1; i >= 0; i--)
        if (digits[i] != b.digits[i])
            return digits[i] < b.digits[i];
    return false;
}

bool BigInt::operator<(const BigInt &b) const
{
    if (negative != b.negative)
        return negative;
    return negative ? b.abs_less(*this) : abs_less(b);
}

bool BigInt::operator==(const BigInt &b) const
{
    return digits == b.digits && negative == b.negative;
}

bool BigInt::operator<=(const BigInt &b) const
{
    return *this < b || *this == b;
}

bool BigInt::operator>(const BigInt &b) const
{
    return !(*this <= b);
}

BigInt BigInt::operator-() const
{
    BigInt r = *this;
    if (!(digits.size() == 1 && digits[0] == 0))
        r.negative = !r.negative;
    return r;
}

vector<int> BigInt::add(const vector<int> &a, const vector<int> &b)
{
    vector<int> res;
    int carry = 0;
    for (int i = 0; i < max(a.size(), b.size()) || carry; i++)
    {
        if (i < a.size())
            carry += a[i];
        if (i < b.size())
            carry += b[i];
        res.push_back(carry % 10);
        carry /= 10;
    }
    return res;
}

vector<int> BigInt::sub(const vector<int> &a, const vector<int> &b)
{
    vector<int> res;
    int borrow = 0;
    for (int i = 0; i < a.size(); i++)
    {
        int val = a[i] - borrow - (i < b.size() ? b[i] : 0);
        if (val < 0)
        {
            val += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        res.push_back(val);
    }
    while (res.size() > 1 && res.back() == 0)
        res.pop_back();
    return res;
}

BigInt BigInt::operator+(const BigInt &b) const
{
    if (negative == b.negative)
        return BigInt(add(digits, b.digits), negative);
    if (abs_less(b))
        return BigInt(sub(b.digits, digits), b.negative);
    else
        return BigInt(sub(digits, b.digits), negative);
}

BigInt BigInt::operator-(const BigInt &b) const
{
    return *this + (-b);
}

BigInt BigInt::operator*(const BigInt &b) const
{
    vector<int> res(digits.size() + b.digits.size());
    for (int i = 0; i < digits.size(); ++i)
        for (int j = 0; j < b.digits.size(); ++j)
            res[i + j] += digits[i] * b.digits[j];
    int carry = 0;
    for (int i = 0; i < res.size(); ++i)
    {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }
    BigInt result(res, negative ^ b.negative);
    result.trim();
    return result;
}

BigInt BigInt::divmod(const BigInt &b, BigInt &rem) const
{
    BigInt dividend = *this, divisor = b;
    dividend.negative = divisor.negative = false;
    rem = BigInt("0");
    vector<int> res;

    for (int i = dividend.digits.size() - 1; i >= 0; i--)
    {
        rem.digits.insert(rem.digits.begin(), dividend.digits[i]);
        rem.trim();
        int x = 0, l = 0, r = 9;
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (divisor * BigInt(to_string(m)) <= rem)
            {
                x = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        res.push_back(x);
        rem = rem - divisor * BigInt(to_string(x));
    }

    reverse(res.begin(), res.end());
    BigInt quotient(res, negative ^ b.negative);
    quotient.trim();
    rem.negative = negative;
    rem.trim();
    return quotient;
}

BigInt BigInt::operator/(const BigInt &b) const
{
    BigInt rem;
    return divmod(b, rem);
}

BigInt BigInt::operator%(const BigInt &b) const
{
    BigInt rem;
    divmod(b, rem);
    return rem;
}

string BigInt::calculate(const string &a, const string &b, const string &op)
{
    BigInt A(a), B(b);
    BigInt result;
    if (op == "+")
        result = A + B;
    else if (op == "-")
        result = A - B;
    else if (op == "*")
        result = A * B;
    else if (op == "/")
    {
        if (B == BigInt("0"))
            return "除数不能为0";
        result = A / B;
    }
    else if (op == "%")
    {
        if (B == BigInt("0"))
            return "模不能为0";
        result = A % B;
    }
    else
        return "无效的运算符";
    return result.toString();
}

// ----------------------------------------------------------
// ------------------------ 方程求解 ------------------------
double FormulaSolve::poly(const vector<double> &a, double x)
{
    double sum = 0;
    for (int i = 0; i < a.size(); i++)
        sum = sum * x + a[i];
    return sum;
}

double FormulaSolve::deriv(const vector<double> &a, double x)
{
    double sum = 0;
    int degree = a.size() - 1;
    for (int i = 0; i < degree; i++)
        sum = sum * x + a[i] * (degree - i);
    return sum;
}

double FormulaSolve::solve(int n, const vector<double> &a, double x, int max_iter, double eps)
{
    for (int step = 0; step < max_iter; step++)
    {
        double fx = poly(a, x);
        double dfx = deriv(a, x);
        if (fabs(dfx) < eps)
            break;
        double xnext = x - fx / dfx;
        if (fabs(xnext - x) < eps)
            return xnext;
        x = xnext;
    }
    return x;
}

// ----------------------------------------------------------
// ------------------------ 矩阵运算 ------------------------
vector<vector<int>> MatrixCalc::calculate(int r1, int c1, int r2, int c2, const string &op, const vector<vector<int>> &A, const vector<vector<int>> &B)
{
    if (op == "+")
    {
        if (r1 != r2 || c1 != c2)
            throw invalid_argument("矩阵加法要求两个矩阵大小相同");
        vector<vector<int>> C(r1, vector<int>(c1));
        for (int i = 0; i < r1; i++)
            for (int j = 0; j < c1; j++)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }

    else if (op == "-")
    {
        if (r1 != r2 || c1 != c2)
            throw invalid_argument("矩阵减法要求两个矩阵大小相同");
        vector<vector<int>> C(r1, vector<int>(c1));
        for (int i = 0; i < r1; i++)
            for (int j = 0; j < c1; j++)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }

    else if (op == "*")
    {
        if (c1 != r2)
            throw invalid_argument("矩阵乘法要求前一个矩阵的列数等于后一个的行数");
        vector<vector<int>> C(r1, vector<int>(c2, 0));
        for (int i = 0; i < r1; i++)
            for (int j = 0; j < c2; j++)
                for (int k = 0; k < c1; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return C;
    }

    else
    {
        throw invalid_argument("不支持的操作符：" + op);
    }
}

void MatrixCalc::printMatrix(const vector<vector<int>> &M)
{
    for (const auto &row : M)
    {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

// ----------------------------------------------------------
// ------------------------- 求质数 -------------------------
PrimeSieve::PrimeSieve(int limit) : n(limit)
{
    st.assign(n + 1, false);
    get_primes();
}

void PrimeSieve::get_primes()
{
    for (int i = 2; i <= n; i++)
    {
        if (!st[i])
            primes.push_back(i);
        for (int j = 0; j < primes.size() && primes[j] <= n / i; j++)
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}

void PrimeSieve::print(int perLine) const
{
    for (int i = 0; i < primes.size(); i++)
    {
        cout << setw(8) << primes[i];
        if ((i + 1) % perLine == 0)
            cout << '\n';
    }
    if (primes.size() % perLine != 0)
        cout << '\n';
}

// ----------------------------------------------------------
// ------------------------- 求约数 -------------------------
vector<int> DivisorTool::get_divisors(int x)
{
    vector<int> res;
    for (int i = 1; i <= x / i; i++)
    {
        if (x % i == 0)
        {
            res.push_back(i);
            if (i != x / i)
                res.push_back(x / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

void DivisorTool::print(const vector<int> &divisors, int perLine)
{
    for (int i = 0; i < divisors.size(); i++)
    {
        cout << setw(10) << divisors[i];
        if ((i + 1) % perLine == 0)
            cout << '\n';
    }
    if (divisors.size() % perLine != 0)
        cout << '\n';
}

// ----------------------------------------------------------
// ------------------------ 求组合数 ------------------------
long long Combination::power(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

Combination::Combination(int n, long long m) : mod(m)
{
    // 预处理阶乘和逆元
    fact.assign(n + 1, 1);
    inv_fact.assign(n + 1, 1);

    // 计算所有阶乘 fact[i] = i! % mod
    for (int i = 2; i <= n; i++)
    {
        fact[i] = fact[i - 1] * i % mod;
    }

    // 计算所有逆元阶乘 inv_fact[i] = (i!)^(-1) % mod
    inv_fact[n] = power(fact[n], mod - 2);
    for (int i = n - 1; i >= 0; i--)
    {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
    }
}

long long Combination::get(int n, int k)
{
    if (k < 0 || k > n)
        return 0;
    return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}

// ----------------------------------------------------------
// ---------------------- 求斐波那契数 ----------------------
long long Fibonacci::Matrix::mod = 1e9 + 7;

Fibonacci::Matrix::Matrix()
{
    m[0][0] = m[0][1] = m[1][0] = m[1][1] = 0;
}

Fibonacci::Matrix Fibonacci::Matrix::identity()
{
    Matrix mat;
    mat.m[0][0] = mat.m[1][1] = 1;
    return mat;
}

Fibonacci::Matrix Fibonacci::Matrix::base()
{
    Matrix mat;
    mat.m[0][0] = mat.m[0][1] = mat.m[1][0] = 1;
    mat.m[1][1] = 0;
    return mat;
}

Fibonacci::Matrix Fibonacci::Matrix::operator*(const Matrix &b) const
{
    Matrix c;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            for (int k = 0; k < 2; ++k)
                c.m[i][j] = (c.m[i][j] + m[i][k] * b.m[k][j]) % mod;
    return c;
}

Fibonacci::Matrix Fibonacci::fastpow(Matrix a, long long n)
{
    Matrix res = Matrix::identity();
    while (n)
    {
        if (n & 1)
            res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

Fibonacci::Fibonacci(long long m)
{
    Matrix::mod = m;
}

long long Fibonacci::get(long long n)
{
    if (n == 0)
        return 0;
    Matrix res = fastpow(Matrix::base(), n - 1);
    return res.m[0][0];
}

// ----------------------------------------------------------
// ----------------------- 求GCD和LCM -----------------------
long long GCDandLCM::gcd(long long a, long long b)
{
    return b ? gcd(b, a % b) : a;
}

long long GCDandLCM::lcm(long long a, long long b)
{
    if (a == 0 || b == 0)
        return 0;
    return a / gcd(a, b) * b;
}