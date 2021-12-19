#pragma once
#include <iostream>
using namespace std;
//연결리스트 https://huangdi.tistory.com/96
//new, delete https://hwan-shell.tistory.com/12

// delete 와 free가 등장하는데, 차이를 이해할 필요가 있다.
// 힙은 아래에서 위로 주소값을 할당받는데,(스택은 100, 96, 92.../ 힙은 0, 4, 8..식으로 방향이 다름)
// new = 반환 값이 주소값 (포인터로 받아야 함) -> 힙이라는 메모리 영역에서 주소 받아옴 -> delete로 해제
// delete(주소 값을 넣어 해제) -> 해당 시작 주소부터 해당 데이터의 끝 까지 메모리 해제처리
// malloc : 포인터의 타입을 모르기 때문에 리턴값의 자료형은 (void*) , int *i = (int*)malloc(sizeof(int))처럼 자료형을 앞에 선언해줘야 함
//		- 객체 생성 시 초기 값을 줄 수 없음 (생성자 X)
//		- 객체 생성 시 예외처리 없이 NULL값 반환.
//		- realloc으로 할당된 메모리 크기를 재조정 가능.
// new : type-safe로 해당 객체에 맞는 포인터로 반환. 별도의 자료형 선언할 필요 X
//		- 객체 생성 시 초기 값을 줄 수 있음. (test a = new Test(123);) -> 생성자가 호출
//		- 객체 생성 시 에러 발생하면 예외처리.
//		- 할당된 크기에 대한 메모리 재조정 불가능.
// type-safe? : 컴파일러가 타입형을 확인해줌. int형은 int형으로.. string은 string으로 잘 저장되는지 확인해줌.


struct Node 
{
	int data;
	struct Node* link; //class일때 Node* link와 같은 선언
};

struct HeadNode 
{
	Node* head;
	//Node를 가리키는 포인터, head
};

class Singlist {
public:
	//List생성, 헤드노드
	HeadNode* createList() 
	{ //list생성, 헤드노드
		HeadNode* HNode = new HeadNode;
		//HeadNode를 가리키는 포인터, HNode
		HNode->head = nullptr;
		return HNode;
	}
	// List의 마지막에 노드 삽입
	void AddNode(HeadNode* HNode, int A)
	{
		Node* ANode = new Node; //ANode 동적할당 및 생성
		Node* LNode; // 기존 노드의 마지막 노드(Last Node)
		ANode->data = A; //동적할당 ANode의 data는 리턴받은 A를 추가(삽입)
		ANode->link = nullptr; //ANode의 link는 nullptr로 초기화

		if (HNode->head == nullptr) 
		{ //list가 비어있을 경우 전달받은 HNode의 head에 ANode(추가노드)넣기.
			HNode->head = ANode;
			return;
		}
		LNode = HNode->head; 
		//비어있지 않을 경우 head(가장 처음)노드가 LNode(가장 마지막 노드)를 가리키도록 (이중연결)

		while (LNode->link != nullptr) 
		{ //연결리스트의 가장 마지막 노드를 찾는 과정
			LNode = LNode->link;
			LNode->link = ANode;
			//마지막 노드를 찾고 while문을 나오면 뒤에 새로운 노드를 연결한다
		}
	}
	
	void DeleteNode(HeadNode* HNode)
	{
		Node* PrevNode; //삭제노드 이전 노드
		Node* DelNode; //삭제노드

		if (HNode->head == nullptr) return; 
		if (HNode->head->link == nullptr) //한 개의 노드만 가진 경우
		{
			delete HNode->head; //head가 가리키던 메모리 공간을 힙 영역에 반환(동적할당 해제)
			HNode->head = nullptr; //헤드 노드의 link 부분인 head를 nullptr처리
			return;
		}
		else //list에 노드 여러개 있을 경우
		{
			PrevNode = HNode->head; //HeadNode가 가리키는 노드가 이전 노드(PrevNode)가 되도록
			DelNode = HNode->head->link; //PrevNode 다음 위치를 DelNode로 설정
			while (DelNode->link != nullptr) //DelNode가 마지막 노드가 될 때 까지 반복
			{
				PrevNode = DelNode;	//PrevNode가 한 칸씩 이동하고,
				DelNode = PrevNode->link; //DelNode도 한 칸씩 끝으로 이동처리
			}
			free(DelNode); //마지막 노드의 메모리 공간을 반환
			PrevNode->link = nullptr;
		}
	}
};




//
//		if (H->head == NULL) { // 리스트가 비어있을 경우
//			H->head = NewNode;
//			return;
//		}
//
//		LastNode = H->head;   // 리스트가 비어있지 않은 경우에 연결리스트의 가장 처음 노드가 LastNode를 가리키게 한다.
//		while (LastNode->link != NULL) LastNode = LastNode->link; // 연결리스트의 마지막 노드를 찾는 과정
//		LastNode->link = NewNode; // 마지막 노드를 찾고 while문을 나오면 뒤에 새 노드를 가리키게 한다.
//	}
//
//	/* 리스트의 마지막 노드 삭제*/
//	void deleteNode(HeadNode* H) {
//		Node* prevNode;  // 삭제되는 노드의 앞 노드
//		Node* delNode;  // 삭제되는 노드
//
//		if (H->head == NULL) return; // 리스트가 빈 경우
//		if (H->head->link == NULL) { // 한 개의 노드만 가진 경우
//			delete H->head;  // head가 가리키던 메모리 공간을 힙 영역에 반환
//			H->head = NULL;  // 헤드 노드의 link 부분인 head를 null로 설정.
//			return;
//		}
//		else {  // 리스트에 노드 여러 개 있는 경우
//			prevNode = H->head; // 헤드 노드가 가리키는 노드가 prevNode가 되게 설정
//			delNode = H->head->link; // prevNode 다음 위치로 delNode 설정
//			while (delNode->link != NULL) { //delNode가 마지막노드가 될 때까지
//				prevNode = delNode;       // prevNode를 한칸씩 가고
//				delNode = prevNode->link; // delNode도 한칸씩 끝으로 간다.
//			}
//			free(delNode);  // 마지막 노드의 메모리 공간을 반환
//			prevNode->link = NULL;
//		}
//	}
//
//	/* 리스트의 특정 노드 삭제*/
//	void deleteThisNode(HeadNode* H, int deldata) {
//		Node* delNode;  // 삭제하려는 노드
//		Node* prevNode; // 삭제하려는 노드의 앞 노드
//		prevNode = H->head;
//
//		while (prevNode->link->data != deldata) {
//			prevNode = prevNode->link;
//		}
//
//		delNode = prevNode->link;   // prevNode가 가리키는 노드가 삭제할 노드
//		prevNode->link = delNode->link;  // prevNode가 delNode 다음 노드를 가리키도록
//		free(delNode);  // delNode 삭제
//
//		cout << deldata << " 데이터 값을 가진 노드가 삭제됐습니다." << endl;
//		return;
//	}
//
//	/* 리스트에 특정 노드 삽입*/
//	void addThisNode(HeadNode* H, int afterthisdata, int adddata) {
//		// afterthisdata: 이 데이터 뒤에 삽입하고 싶소.
//		// adddata: 이 데이터를 삽입하고 싶소.
//
//		Node* prevNode;  //삽입하려는 노드의 이전 노드
//		prevNode = H->head;
//
//		while (prevNode->data != afterthisdata) {
//			prevNode = prevNode->link;
//		}
//
//		Node* NewNode = new Node;
//		NewNode->data = adddata;
//		NewNode->link = prevNode->link;
//		prevNode->link = NewNode;
//		return;
//	}
//
//	/* 리스트의 특정 노드 검색*/
//	void searchNode(HeadNode* H, int thisdata) {
//		Node* someNode;
//		someNode = H->head;
//
//		while (someNode->data != thisdata) {
//			someNode = someNode->link;
//		}
//		cout << thisdata << " 데이터를 검색하는 데 성공했습니다." << endl;
//	}
//
//	/* 연결리스트 출력*/
//	void printList(HeadNode* L) {
//		//노드 순서대로 리스트 출력
//		Node* p;
//		cout << "연결리스트 목록 = ( ";
//		p = L->head;
//
//		while (p != NULL) {
//			cout << p->data;
//			p = p->link;
//			if (p != NULL) cout << " --> ";
//		}
//		cout << " )" << endl;
//	}
//};



