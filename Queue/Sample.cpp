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
		printf("\n ���� á���!");
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
		printf("\n ������ �־��!");
		return -1;
	}
	int i = Queue[front]; //Queue�� front���� ������
	front = ++front % MAX;
	return i;
}
void PrintQueue()
{
	printf("\n ť �ȿ���.. : Top ---> Bottom\n");
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
	int i = get(); //Queue�� front���� ������ ���
	PrintQueue();

	printf("\nPut 4, 7, 5, 2");
	put(4);
	put(7);
	put(5);
	put(2);
	PrintQueue();

	printf("\n���� ���� á���. 9���� �ٽ� �帱�Կ�~");
	put(9);
	PrintQueue();

	printf("\n���� ť�� ������. 1�� �������Կ�~");
	i = get();
	printf("\n���� ���� %d ����~",i);

}
