#include <stdio.h>
extern int Call_Arm(int, int, int, int, int, int, int);
int main()
{
  int a,b,c1, c2,c3,c4,c5,c6,c7;
	a=15;	
	a = Call_Arm(22,1,2,3,4,5,6);
  b=14;
	b = Call_Arm(22,1,2,3,4,5,6);
	c1 = 22;
	c2 = 1;
	c3 = 2;
	c4 = 3;	
	c5 = 4;
	c6 = 5;	
	c7 = 6;
	b = Call_Arm(c1,c2,c3,c4,c5,c6,c7);	
	c1 =a + b;
	return 0;
}
