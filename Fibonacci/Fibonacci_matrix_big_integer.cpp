#include<cstdio>
#include<iostream>
#include<vector>
#include<windows.h>
//#include<ctime>
using namespace std;

#define LOCAL

/*************大整数类BigInteger****************/
struct BigInteger{
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> s;

	BigInteger(long long num = 0){ *this = num; };

	BigInteger operator = (long long num)
	{
		s.clear();
		do{
			s.push_back(num % BASE);
			num /= BASE;
		} while (num > 0);
		return *this;
	}

	BigInteger operator + (const BigInteger& b) const
	{
		BigInteger c;
		c.s.clear();
		for (int i = 0, g = 0;; i++)
		{
			if (g == 0 && i >= s.size() && i >= b.s.size())
				break;
			int x = g;
			if (i < s.size()) x += s[i];
			if (i < b.s.size()) x += b.s[i];
			c.s.push_back(x % BASE);
			g = x / BASE;
		}
		return c;
	}

	BigInteger operator * (const BigInteger& b) const
	{
		BigInteger c;
		c.s.clear();
		for (int i = 0;; i++) {
			if (i >= s.size()) {
				break;
			}
			int x = 0;
			long long g = 0;
			if (i < s.size()) {
				x = s[i];
			}
			g = x;
			for (int j = 0, r = 0; j<b.s.size(); j++) {
				int k = i + j;
				g = x;
				g *= b.s[j];
				while (g) {
					if (k < c.s.size()) {
						c.s[k] = c.s[k] + g % BASE;
						if (c.s[k] / BASE) {
							r = c.s[k] / BASE;
							c.s[k] = c.s[k] % BASE;
						}
					}
					else {
						c.s.push_back(g%BASE);
					}
					g = g / BASE + r;
					r = 0;
					k++;
				}
			}
		}
		return c;
	}
};

ostream& operator << (ostream& out, const BigInteger& x)
{
	out << x.s.back();
	for (int i = x.s.size() - 2; i >= 0; i--)
	{
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for (int j = 0; j < strlen(buf); j++)
			out << buf[j];
	}
	return out;
}
/*********************************************/

void matrix_multiply(BigInteger rlt[2][2], BigInteger a[2][2], BigInteger b[2][2])
{
	BigInteger tmp[2][2];
	tmp[0][0] = (a[0][0] * b[0][0]) + (a[0][1] * b[1][0]);
	tmp[0][1] = (a[0][0] * b[0][1]) + (a[0][1] * b[1][1]);
	tmp[1][0] = (a[1][0] * b[0][0]) + (a[1][1] * b[1][0]);
	tmp[1][1] = (a[1][0] * b[0][1]) + (a[1][1] * b[1][1]);
	rlt[0][0] = tmp[0][0];
	rlt[0][1] = tmp[0][1];
	rlt[1][0] = tmp[1][0];
	rlt[1][1] = tmp[1][1];
}

//矩阵幂算法
BigInteger fibonacci(int n)
{
	BigInteger base[2][2] = { { 1, 1 }, { 1, 0 } };
	BigInteger rlt[2][2] = { { 1, 0 }, { 0, 1 } };  //单位矩阵

	if (n == 1 || n == 2)
		return 1;
	else
	{
		n = n - 2;  //减少两次运算
		while (n > 0)
		{
			if (n % 2 == 1)
			{
				matrix_multiply(rlt, rlt, base);
			}
			matrix_multiply(base, base, base);
			n /= 2;
		}
		return (rlt[0][0] + rlt[0][1]); //f(n-1)+f(n-2)
	}
}

int main()
{
#ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("fib_matrix.txt", "w", stdout);
#endif
	int n = 0;
	//double t_start = 0.0, t_end = 0.0;
	LARGE_INTEGER n_freq;
	LARGE_INTEGER n_begin_time, n_end_time;
	BigInteger rlt = 0;

	//printf("Fibonacci matrix multiplication method\n");
	printf("matrix multiplication\n");
	//printf("please input n: ");
	QueryPerformanceFrequency(&n_freq);
	while (scanf("%d", &n) == 1)
	{

		//t_start = (double)clock();
		QueryPerformanceCounter(&n_begin_time);

		rlt = fibonacci(n);

		//t_end = (double)clock();
		QueryPerformanceCounter(&n_end_time);

		//cout << "n: " << n << " rlt: " << rlt << "\ntime:" << (t_end - t_start) / CLOCKS_PER_SEC << " s" << endl;
		cout << "n: " << n << " rlt: " << rlt << "\ntime:" <<
			(double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart << " us" << endl;
		//cout << (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart << endl;
		//printf("input: %d\n", n);
		//printf("result: %lld\n", fibonacci(n));
		//printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart); printf("input: %d\n", n);
		/*printf("input: %d ", n);
		printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart);*/
	}
	return 0;
}