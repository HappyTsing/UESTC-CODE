#include<stdio.h>
#include<stdlib.h>
void merge_sort(int a[],int low,int high);
void merge(int a[],int low,int mid,int high);
int main(void)
{
    int a[5],i;
    printf("���������������\n");
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
    mid=(low+high)/2;  //low+ (high-low)/ 2���ã����Է�ֹ�������� 
    merge_sort(a,low,mid);
    merge_sort(a,mid+1,high);
    merge(a,low,mid,high);
    }
}
void merge(int a[],int low,int mid,int high)
{
    int *b;
    int mind=low;
    int bigmid=mid+1; //�ֳ������֣��ڶ����ֵĿ�ͷ�������±�Ϊmid+1
    int i=low;        //�������b���Ƶ�aʱ�Ŀ�ͷΪlow
    b=(int*)malloc((high+1)*sizeof(int));  //�����aһ����Ŀռ�
    while(low<=mid&&bigmid<=high)
    {
        if(a[low]<a[bigmid])      //ǰ���ֺͺ󲿷�����Աȣ�С���ǲ��ַŽ�����b
            b[mind++]=a[low++];
        else
            b[mind++]=a[bigmid++];
    }
    while(low<=mid)
        b[mind++]=a[low++]; 
	//ѭ����ɺ��������ֵ���������һ���������꣬��δ�������������Ԫ�ش���b��
    while(bigmid<=high)
        b[mind++]=a[bigmid++];
    for(i;i<=high;i++)   
    //��ʱ����b�Ѿ�����b�ڸú������������٣��ò��轫����ת�Ƶ�a�У�������ı䡣
        a[i]=b[i];
}
