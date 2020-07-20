#include<stdio.h>
void quicksort(int a[], int low, int high);
int partition(int a[], int low, int high);

int main(void)
{
	int a[5], i;
	printf("ÊäÈë5¸ö²âÊÔÊý¾Ý\n");
	for (i = 0; i < 5; i++)
	{
		scanf("%d", &a[i]);

	}
	quicksort(a, 0, 4);
	for (i = 0; i < 5; i++)
	{
		printf("%d  ", a[i]);

	}
	return 0;
}
void quicksort(int a[], int low, int high)
{
	if (low < high)
	{
		int middle = partition(a, low, high);
		quicksort(a, low, middle - 1);
		quicksort(a, middle + 1, high);
	}
}

int partition(int a[], int low, int high)
{
	int part_element = a[low];   //此时a[low]空闲，故先移动high
	for (;;)
	{
		while (low < high&&a[high] >= part_element)
		high--;                //找到一个比选定数小的数，将其放在low指向的地方，此时low不可动，但high指向的地方可以被改变，故下一步移动low
		if (low >= high) break;
		a[low++] = a[high];

		while (low < high&&a[low] <= part_element)
		low++;
		if (low >= high)break;
		a[high--] = a[low];
	}
	a[low] = part_element;     //此时low和high指向一个位置，这个位置就是选定数应该存在的位置
	return low;
}
