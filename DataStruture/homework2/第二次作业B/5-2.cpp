#include<stdio.h>
float average(float a[], int n)
{
	if (n == 1)
		return a[0];
	else {
		return((average(a, n-1 ))*(n -1) + a[n-1]) / n;
	}
}
int main(void)
{
	float a[5] = { 1,2,3,4,5 };
	printf("%f", average(a, 5));
	return 0;
}