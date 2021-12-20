#include <stdio.h>
#define MAX 10
int Queue[MAX];
int front, rear;

void InitQueue()
{
	front = rear = 0;
}
void ClrearQueue()
{
	front = rear;
}
int put(int p)
{
	if ((rear + 1) % MAX == front)
	{
		printf("\n 가득 찼어요!");
		return -1;
	}
	Queue[rear] = p;
	rear = ++rear % MAX; //1,2,3....
	return p;
}
int get()
{
	if (front == rear)
	{
		printf("\n 공간이 있어요!");
		return -1;
	}
	int i = Queue[front]; //Queue의 front값을 가져옴
	front = ++front % MAX;
	return i;
}
void PrintQueue()
{
	printf("\n 큐 안에는.. : Top ---> Bottom\n");
	for (int i = front; i != rear; i = ++i% MAX)
	{
		printf("%-6d", Queue[i]);
	}
}
int main()
{
	InitQueue();
	printf("\nPush 5, 4, 7, 1, 2, 8");
	put(5);
	put(4);
	put(7);
	put(1);
	put(2);
	put(8);
	PrintQueue();

	printf("\nGet");
	int i = get(); //Queue내 front값을 가져와 출력
	PrintQueue();

	printf("\nPut 4, 7, 5, 2");
	put(4);
	put(7);
	put(5);
	put(2);
	PrintQueue();

	printf("\n이제 가득 찼어요. 9번은 다시 드릴게요~");
	put(9);
	PrintQueue();

	printf("\n이제 큐가 비었어요. 1개 꺼내볼게요~");
	i = get();
	printf("\n꺼낸 값은 %d 예요~",i);

}
