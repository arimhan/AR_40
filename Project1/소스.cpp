#include <stdio.h>



void main()
{
	//int i, k[10], a = 0, b = 0;
	//for (i = 0; i < 10; i++)
	//{
	//	k[i] = 10 - i;
	//}
	//int* p = k;
	//p += 5;
	//a = *(p + 1);
	//b = p[3];

	//int a = 2, b = 3, c = 1;
	//a *= (b++) * (++c);

	//int number[3] = { 1,2,3 };
	//number[1];

	int num[] = { 1,3,5,7,9 }, * ptr = num + 2;
	printf("%d, %d\n", *ptr, *ptr + 1);


}


//void maximun(float a, float b) 
//{
//	if (a > b)
//	{
//		printf("max°ª : %f", a);
//	}
//}
//
//void minimun(float a, float b)
//{
//	if (a > b)
//	{
//		printf("max°ª : %f", a);
//	}
//}
//
//void main()
//{
//	float a, b;
//	float max, min;
//	scanf("%f, %f", &a, &b);
//	max = maximun(a, b);
//	min = minimun(a, b);
//	
//
//}




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