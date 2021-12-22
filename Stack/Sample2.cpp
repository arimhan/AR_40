#include <iostream>
using namespace std;
//같은 Stack구현이나 스택들의 연결 리스트로 구현
//C++ 알고리즘 책 34 ~ 36page
typedef int itemType; //임시 자료형

class Stack
{
public:
// 스택에서 어떠한 연산이 제공되는지 인터페이스 구성 부분
	//int z;
	Stack(int max);
	~Stack();
	void push(itemType v);
	itemType pop();
	int empty();
private:
// 구현과 관련된 기본적인 자료구조
	struct node { itemType key; struct node* next; };
	struct node* head, * z;
};
Stack::Stack(int max)
{
	head = new node; z = new node;
	head->next = z; z->next = z;
}
Stack::~Stack()
{
	struct node* t = head;
	while (t != z)
	{
		head = t; t = t->next; delete head;
	}
}
void Stack::push(itemType v)
{
	struct node* t = new node;
	t->key = v; t->next = head->next; // t->next에서 next값이 연결이 되지 않아 엑세스위반 오류
	head->next = t;
	cout << "%d Values input" << v;
}
itemType Stack::pop()
{
	itemType x;
	struct node* t = head->next;
	head->next = t->next; x = t->key;
	cout << "%d Values pop" << t;
	delete t; return x;
}
int Stack::empty()
{
	cout << "Stack is Empty! \n";
	return head->next == z;
}

int main()
{
	Stack* st = nullptr;
	st->push(10); st->push(9); st->push(8); st->push(7);
	cout << "\n";
}