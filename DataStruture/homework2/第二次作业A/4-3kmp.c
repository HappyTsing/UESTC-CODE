#include<stdio.h>
#include<stdlib.h>
#define Maxsize 30
typedef struct
{
	char data[Maxsize];
	int length;
}SqString;

void StrAssign(SqString *s, char cstr[]);
int BF(SqString s, SqString t);
void GetNext(SqString t, int next[]);
int KMPIndex1(SqString s, SqString t);
void GetNextval(SqString t, int nextval[]);
int KMPIndex2(SqString s, SqString t);
int main(void)
{
	SqString ss, st;
	StrAssign(&ss, "abcabcdabcdeabcdefabcdefg");
	StrAssign(&st, "abcdeabcdefab");
	printf("ºÚµ•∆•≈‰Œª÷√:   %d", BF(ss, st));
	printf("\nKMP∆•≈‰Œª÷√:    %d", KMPIndex1(ss, st));
	printf("\n∏ƒΩ¯KMP∆•≈‰Œª÷√:%d", KMPIndex2(ss, st));
	return 0;

}

void StrAssign(SqString * s, char cstr[])
{
	int i;
	for (i = 0; cstr[i] != '\0'; i++)
	{
		(*s).data[i] = cstr[i];
	}
	(*s).length = i;
}
int BF(SqString s, SqString t)
{
	int i = 0,j = 0;
	while (i < s.length&&j < t.length)
	{
		if (s.data[i] == t.data[j])
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= t.length)
		return (i - t.length);
	else
		return -1;
}
void GetNext(SqString t, int next[])
{
	int j=0, k=-1;
	next[0] = -1;
	while (j < t.length - 1)
	{
		if (k==-1||(t.data[j]=t.data[k]))
		{
			j++;
			k++;
			next[j] = k;
		}
		else
			k = next[k];
	}
}
int KMPIndex1(SqString s, SqString t)
{
	int next[Maxsize], i = 0, j = 0;
	GetNext(t, next);
	while (i < s.length&&j < t.length)
	{
		if (j == -1 || (s.data[i] == t.data[j]))
		{
			i++;
			j++;
		}
		else
			j = next[j];

	}
	if (j >= t.length)
		return (i - t.length);
	else
		return -1;
}
void GetNextval(SqString t, int nextval[])
{
	int j = 0, k = -1;
	nextval[0] = -1;
	while (j < t.length)
	{
		if (k == -1 || (t.data[j] = t.data[k]))
		{
			j++;
			k++;
			if (t.data[j] != t.data[k])
				nextval[j] = k;
			else
				nextval[j] = nextval[k];
		}
		else
			k = nextval[k];
	}
}
int KMPIndex2(SqString s, SqString t)
{
	int nextval[Maxsize], i = 0, j = 0;
	GetNextval(t, nextval);
	while (i < s.length&&j < t.length)
	{
		if (j == -1 || (s.data[i] == t.data[j]))
		{
			i++;
			j++;
		}
		else
			j = nextval[j];
	}
	if (j >= t.length)
		return (i - t.length);
	else
		return -1;
}