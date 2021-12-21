#pragma once
#include <iostream>

using namespace std;
#define MAX 10 // Queue size

template <class T>
class AQueue
{
public:
	int front;
	int rear;
	int size;
	T* values;
public:
	AQueue()
	{
		front = nullptr;
		rear = nullptr;
		size = MAX;
		values = new T[size]; //Queue size만큼 배열생성
	}
	~AQueue()
	{
		delete[] valuse;
	}
public:
	void Push(T values);
	void Pop();
	void Empty();
	bool IsFull();
	ostream& operator << (ostream& os, AQueue<T>& q);
};

