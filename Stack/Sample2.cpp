#include <iostream>
using namespace std;
//���� Stack�����̳� ���õ��� ���� ����Ʈ�� ����
//C++ �˰��� å 34 ~ 36page
typedef int itemType; //�ӽ� �ڷ���

class Stack
{
public:
// ���ÿ��� ��� ������ �����Ǵ��� �������̽� ���� �κ�
	//int z;
	Stack(int max);
	~Stack();
	void push(itemType v);
	itemType pop();
	int empty();
private:
// ������ ���õ� �⺻���� �ڷᱸ��
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
	t->key = v; t->next = head->next; // t->next���� next���� ������ ���� �ʾ� ���������� ����
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