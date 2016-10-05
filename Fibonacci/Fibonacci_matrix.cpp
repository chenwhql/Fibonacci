#include<cstdio>
#include<windows.h>
using namespace std;

#define LOCAL

typedef unsigned long long ull;

void matrix_multiply(ull rlt[2][2], ull a[2][2], ull b[2][2])
{
	ull tmp[2][2];
	tmp[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
	tmp[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
	tmp[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
	tmp[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
	rlt[0][0] = tmp[0][0];
	rlt[0][1] = tmp[0][1];
	rlt[1][0] = tmp[1][0];
	rlt[1][1] = tmp[1][1];
}

//矩阵幂算法
ull fibonacci(int n)
{
	ull base[2][2] = { { 1, 1 }, { 1, 0 } };
	ull rlt[2][2] = { { 1, 0 }, { 0, 1 } };  //单位矩阵

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
	LARGE_INTEGER n_freq;
	LARGE_INTEGER n_begin_time, n_end_time;
	ull rlt = 0;

	//printf("Fibonacci matrix multiplication method\n");
	printf("matrix multiplication\n");
	//printf("please input n: ");

	QueryPerformanceFrequency(&n_freq);
	while (scanf("%d", &n) == 1)
	{

		QueryPerformanceCounter(&n_begin_time);

		rlt = fibonacci(n);

		QueryPerformanceCounter(&n_end_time);

		//printf("input: %d\n", n);
		//printf("result: %lld\n", fibonacci(n));
		//printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart); printf("input: %d\n", n);
		printf("input: %d ", n);
		printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart);
	}
	return 0;
}