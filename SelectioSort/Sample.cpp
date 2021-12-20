#include <iostream>

using namespace std;

bool Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
	return true;
}

void SelectionSort(int arr[], int count)
{
	int a, b;
	int Index;

	for (a = 0; a < count - 1; a++)
	{
		Index = a;
		for (b = a + 1; b < count; b++)
		{
			if (arr[b] < arr[Index]) Index = b;
		}
		if (a != Index)
		{
			Swap(&arr[a], &arr[Index]);
		}
	}
}


int main()
{
	int arr[5] = { 5, 4, 1, 3, 2 };
	int a;
	SelectionSort(arr, sizeof(arr) / sizeof(int));

	for (a = 0; a < 5; a++)
		cout << " " << arr[a];
	return 0;
}