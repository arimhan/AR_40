#include <stdio.h>
#include <vector>

void maximun(float a, float b) 
{
	if (a > b)
	{
		printf("max°ª : %f", a);
	}
}

void minimun(float a, float b)
{
	if (a > b)
	{
		printf("max°ª : %f", a);
	}
}

void main()
{
	float a, b;
	float max, min;
	scanf("%f, %f", &a, &b);
	max = maximun(a, b);
	min = minimun(a, b);
	

}




//void swap(int* u, int* v)
//{
//	int temp;
//	temp = *u;
//	*u = *v;
//	*v = temp;
//}

//void main()
//{
//	float a, b;
//	float max, min;
//	scanf(" %f %f", &a, &b);
//	swap(&a, &b);
//}