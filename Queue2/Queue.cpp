#include "Queue.h"

template <class T>
void Push(T values)
{
	if (!IsFull())
	{
		values[rear] = value;
		rear = (rear + 1) % size;
	}
}
void Pop()
{

}
void Empty()
{

}
bool IsFull()
{
}
template <class T>
ostream& operator << (ostream& os, AQueue<T>& q)
{

}
