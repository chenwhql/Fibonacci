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

	BigInteger operator += (const BigInteger& b)
	{
		*this = *this + b;
		return *this;
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

//迭代法
BigInteger fibonacci(int n)
{
	BigInteger a = 1, b = 1, c = 0;
	if (n == 1 || n == 2)
		return 1;
	else
	{
		for (int i = 3; i <= n; ++i)
		{
			c = b;
			b = a + b;
			a = c;
		}
	}
		
	return b;
}

int main()
{
#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("fib_iter.txt","w",stdout);
#endif
	int n = 0;
	//double t_start = 0.0, t_end = 0.0;
	LARGE_INTEGER n_freq;
	LARGE_INTEGER n_begin_time, n_end_time;
	BigInteger rlt = 0;

	//printf("Fibonacci iterative method\n");
	printf("iterative method\n");
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
		/*printf("input: %d\n", n);
		printf("result: %lld\n", fibonacci(n));
		printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart);*/
		/*printf("input: %d ", n);
		printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart);*/
	}
	return 0;
}