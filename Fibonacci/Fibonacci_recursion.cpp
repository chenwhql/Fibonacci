#include<cstdio>
#include<ctime>
using namespace std;

typedef unsigned long long ull;

//µ›πÈÀ„∑®
ull fibonacci(int n)
{
	if (n == 1 || n == 2)
		return 1;
	else
		return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
	int n = 0;
	double t_start = 0.0, t_end = 0.0;
	ull rlt = 0;
	printf("Fibonacci recursion method\n");
	printf("please input n: ");
	scanf("%d", &n);
	t_start = (double)clock();
	rlt = fibonacci(n);
	t_end = (double)clock();
	printf("result: %lld\n", fibonacci(n));
	printf("time: %lf s\n", (t_end - t_start)/CLOCKS_PER_SEC);
	return 0;
}