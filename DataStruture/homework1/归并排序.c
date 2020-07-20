#include<stdio.h>
#include<stdlib.h>
void merge_sort(int a[],int low,int high);
void merge(int a[],int low,int mid,int high);
int main(void)
{
    int a[5],i;
    printf("输入五个测试数据\n");
    for(i=0;i<5;i++)
        scanf("%d",&a[i]);
    merge_sort(a,0,4);
    for(i=0;i<5;i++)
        printf("%d  ",a[i]);
    return 0;
}




void merge_sort(int a[],int low,int high)
{
    int mid;
    if(low<high){
    mid=(low+high)/2;  //low+ (high-low)/ 2更好，可以防止整数超界 
    merge_sort(a,low,mid);
    merge_sort(a,mid+1,high);
    merge(a,low,mid,high);
    }
}
void merge(int a[],int low,int mid,int high)
{
    int *b;
    int mind=low;
    int bigmid=mid+1; //分成两部分，第二部分的开头是数组下标为mid+1
    int i=low;        //最后将数组b复制到a时的开头为low
    b=(int*)malloc((high+1)*sizeof(int));  //分配和a一样多的空间
    while(low<=mid&&bigmid<=high)
    {
        if(a[low]<a[bigmid])      //前部分和后部分数组对比，小的那部分放进数组b
            b[mind++]=a[low++];
        else
            b[mind++]=a[bigmid++];
    }
    while(low<=mid)
        b[mind++]=a[low++]; 
	//循环完成后，两个部分的数组其中一个被消耗完，将未被消耗完的数组元素传入b中
    while(bigmid<=high)
        b[mind++]=a[bigmid++];
    for(i;i<=high;i++)   
    //此时数组b已经有序，b在该函数结束后被销毁，该步骤将内容转移到a中，来保存改变。
        a[i]=b[i];
}
