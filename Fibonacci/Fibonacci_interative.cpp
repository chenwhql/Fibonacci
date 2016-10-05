#include<cstdio>
#include<windows.h>
using namespace std;

typedef unsigned long long ull;

#define LOCAL

//µü´ú·¨
ull fibonacci(int n)
{
	ull a = 1, b = 1, c = 0;
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
	LARGE_INTEGER n_freq;
	LARGE_INTEGER n_begin_time, n_end_time;
	ull rlt = 0;

	//printf("Fibonacci iterative method\n");
	printf("iterative method\n");
	//printf("please input n: ");
	QueryPerformanceFrequency(&n_freq);
	while (scanf("%d", &n) == 1)
	{

		QueryPerformanceCounter(&n_begin_time);

		rlt = fibonacci(n);

		QueryPerformanceCounter(&n_end_time);

		/*printf("input: %d\n", n);
		printf("result: %lld\n", fibonacci(n));
		printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart);*/
		printf("input: %d ", n);
		printf("time: %lf us\n", (double)(n_end_time.QuadPart - n_begin_time.QuadPart) / (double)n_freq.QuadPart);
	}
	return 0;
}