//#include <iostream>
//using namespace std;
//�迭 Stack����
////class itemType {}; //Stack �� datatype. �ڷ����� ���ϴ� ���ø�ȭ ��Ų��.
//typedef int itemType; //�ӽ÷� �ڷ��� int������ ����
//
//class Stack
//{
//private:
//	//������ ���� ���
//	itemType* stack;
//	int p;
//
//public:
//	//�����Ϳ� ���� ������ ����
//	//������ Stack���� ���� �ʱ�ȭ �� �����ϴ� ������ ����
//	Stack(int max = 100)
//	{
//		stack = new itemType[max]; p = 0;
//	}
//	~Stack() { delete stack; }
//
//	//inline���� �Լ� �θ��� ���ʿ��� ���� ����
//	inline void push(itemType v)
//	{
//		stack[p++] = v;
//	}
//	inline itemType pop()
//	{
//		return stack[--p];
//	}
//	inline int empty()
//	{
//		return p;
//	}
//};
//
////���� ǥ���
//// ���ÿ� ���۷��带 ���Խ�Ű�� ���� ��ɾ�. �� ���۷��带 �ص��ϰ� ���ÿ��� �� �� ���۷��带
//// ���� �� ������ �����ϰ� ����� ���Խ�Ű�� ���� ��ɾ�μ� �� ������ �ص�
//int main()
//{
//char c; Stack acc(50); int x;
//	while (cin.get(c))
//	{
//		x = 0;
//		while (x == ' ') cin.get(c);
//		if (c == '+') x = acc.pop() + acc.pop();
//		if (c == '*') x = acc.pop() * acc.pop();
//		while(c>= '0' && c<='9')
//		{
//			x = 10 * x + (c - '0'); cin.get(c);
//		}
//		acc.push(x);
//	}
//	cout << acc.pop() << '\n';
//
//	Stack save(50);
//	while (cin.get(c))
//	{
//		if (c == ')') cout.put(save.pop());
//		if (c == '+') save.push(c);
//		if (c == '*') save.push(c);
//		while (c >= '0' && c <= '9')
//		{
//			cout.put(c); cin.get(c);
//		}
//		if (c != '(') cout << ' ';
//	}
//	cout << '\n';
//
//
//}