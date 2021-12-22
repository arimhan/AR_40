//#include <iostream>
//using namespace std;
//배열 Stack구현
////class itemType {}; //Stack 내 datatype. 자료형을 정하던 템플릿화 시킨다.
//typedef int itemType; //임시로 자료형 int형으로 지정
//
//class Stack
//{
//private:
//	//데이터 구현 방법
//	itemType* stack;
//	int p;
//
//public:
//	//데이터에 허용된 연산을 정의
//	//생성자 Stack에서 스택 초기화 및 생성하는 구성자 역할
//	Stack(int max = 100)
//	{
//		stack = new itemType[max]; p = 0;
//	}
//	~Stack() { delete stack; }
//
//	//inline으로 함수 부름의 불필요한 연산 제거
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
////후위 표기식
//// 스택에 오퍼랜드를 삽입시키기 위한 명령어. 각 오퍼랜드를 해독하고 스택에서 두 개 오퍼랜드를
//// 삭제 및 연산을 수행하고 결과를 삽입시키기 위한 명령어로서 각 연산자 해독
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