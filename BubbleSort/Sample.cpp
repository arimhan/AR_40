#include <iostream>

using namespace std;

//bool Swap(int* a, int* b)
//{
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//	return true;
//}

void BubbleSort(int arr[], int count)
{
	int a, b;
	int temp;

	for (a = 0; a < count - 1; a++)
	{
		for (b = 0; b < (count-a)-1; b++)
		{
			if (arr[b] > arr[b + 1])
			{
				temp = arr[a];
				arr[b] = arr[b + 1];
				arr[b + 1] = temp;
			}
		}
	}
}
// 값 이상하게 출력됨 (5, 4, 4,,,,)

int main()
{
	int arr[5] = { 5, 4, 1, 3, 2 };
	int a;
	BubbleSort(arr, sizeof(arr) / sizeof(int));

	for (a = 0; a < 5; a++)
		cout << " " << arr[a];
	return 0;
}