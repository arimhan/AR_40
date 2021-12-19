#pragma once
#include <iostream>
using namespace std;
//���Ḯ��Ʈ https://huangdi.tistory.com/96
//new, delete https://hwan-shell.tistory.com/12

// delete �� free�� �����ϴµ�, ���̸� ������ �ʿ䰡 �ִ�.
// ���� �Ʒ����� ���� �ּҰ��� �Ҵ�޴µ�,(������ 100, 96, 92.../ ���� 0, 4, 8..������ ������ �ٸ�)
// new = ��ȯ ���� �ּҰ� (�����ͷ� �޾ƾ� ��) -> ���̶�� �޸� �������� �ּ� �޾ƿ� -> delete�� ����
// delete(�ּ� ���� �־� ����) -> �ش� ���� �ּҺ��� �ش� �������� �� ���� �޸� ����ó��
// malloc : �������� Ÿ���� �𸣱� ������ ���ϰ��� �ڷ����� (void*) , int *i = (int*)malloc(sizeof(int))ó�� �ڷ����� �տ� ��������� ��
//		- ��ü ���� �� �ʱ� ���� �� �� ���� (������ X)
//		- ��ü ���� �� ����ó�� ���� NULL�� ��ȯ.
//		- realloc���� �Ҵ�� �޸� ũ�⸦ ������ ����.
// new : type-safe�� �ش� ��ü�� �´� �����ͷ� ��ȯ. ������ �ڷ��� ������ �ʿ� X
//		- ��ü ���� �� �ʱ� ���� �� �� ����. (test a = new Test(123);) -> �����ڰ� ȣ��
//		- ��ü ���� �� ���� �߻��ϸ� ����ó��.
//		- �Ҵ�� ũ�⿡ ���� �޸� ������ �Ұ���.
// type-safe? : �����Ϸ��� Ÿ������ Ȯ������. int���� int������.. string�� string���� �� ����Ǵ��� Ȯ������.


struct Node 
{
	int data;
	struct Node* link; //class�϶� Node* link�� ���� ����
};

struct HeadNode 
{
	Node* head;
	//Node�� ����Ű�� ������, head
};

class Singlist {
public:
	//List����, �����
	HeadNode* createList() 
	{ //list����, �����
		HeadNode* HNode = new HeadNode;
		//HeadNode�� ����Ű�� ������, HNode
		HNode->head = nullptr;
		return HNode;
	}
	// List�� �������� ��� ����
	void AddNode(HeadNode* HNode, int A)
	{
		Node* ANode = new Node; //ANode �����Ҵ� �� ����
		Node* LNode; // ���� ����� ������ ���(Last Node)
		ANode->data = A; //�����Ҵ� ANode�� data�� ���Ϲ��� A�� �߰�(����)
		ANode->link = nullptr; //ANode�� link�� nullptr�� �ʱ�ȭ

		if (HNode->head == nullptr) 
		{ //list�� ������� ��� ���޹��� HNode�� head�� ANode(�߰����)�ֱ�.
			HNode->head = ANode;
			return;
		}
		LNode = HNode->head; 
		//������� ���� ��� head(���� ó��)��尡 LNode(���� ������ ���)�� ����Ű���� (���߿���)

		while (LNode->link != nullptr) 
		{ //���Ḯ��Ʈ�� ���� ������ ��带 ã�� ����
			LNode = LNode->link;
			LNode->link = ANode;
			//������ ��带 ã�� while���� ������ �ڿ� ���ο� ��带 �����Ѵ�
		}
	}
	
	void DeleteNode(HeadNode* HNode)
	{
		Node* PrevNode; //������� ���� ���
		Node* DelNode; //�������

		if (HNode->head == nullptr) return; 
		if (HNode->head->link == nullptr) //�� ���� ��常 ���� ���
		{
			delete HNode->head; //head�� ����Ű�� �޸� ������ �� ������ ��ȯ(�����Ҵ� ����)
			HNode->head = nullptr; //��� ����� link �κ��� head�� nullptró��
			return;
		}
		else //list�� ��� ������ ���� ���
		{
			PrevNode = HNode->head; //HeadNode�� ����Ű�� ��尡 ���� ���(PrevNode)�� �ǵ���
			DelNode = HNode->head->link; //PrevNode ���� ��ġ�� DelNode�� ����
			while (DelNode->link != nullptr) //DelNode�� ������ ��尡 �� �� ���� �ݺ�
			{
				PrevNode = DelNode;	//PrevNode�� �� ĭ�� �̵��ϰ�,
				DelNode = PrevNode->link; //DelNode�� �� ĭ�� ������ �̵�ó��
			}
			free(DelNode); //������ ����� �޸� ������ ��ȯ
			PrevNode->link = nullptr;
		}
	}
};




//
//		if (H->head == NULL) { // ����Ʈ�� ������� ���
//			H->head = NewNode;
//			return;
//		}
//
//		LastNode = H->head;   // ����Ʈ�� ������� ���� ��쿡 ���Ḯ��Ʈ�� ���� ó�� ��尡 LastNode�� ����Ű�� �Ѵ�.
//		while (LastNode->link != NULL) LastNode = LastNode->link; // ���Ḯ��Ʈ�� ������ ��带 ã�� ����
//		LastNode->link = NewNode; // ������ ��带 ã�� while���� ������ �ڿ� �� ��带 ����Ű�� �Ѵ�.
//	}
//
//	/* ����Ʈ�� ������ ��� ����*/
//	void deleteNode(HeadNode* H) {
//		Node* prevNode;  // �����Ǵ� ����� �� ���
//		Node* delNode;  // �����Ǵ� ���
//
//		if (H->head == NULL) return; // ����Ʈ�� �� ���
//		if (H->head->link == NULL) { // �� ���� ��常 ���� ���
//			delete H->head;  // head�� ����Ű�� �޸� ������ �� ������ ��ȯ
//			H->head = NULL;  // ��� ����� link �κ��� head�� null�� ����.
//			return;
//		}
//		else {  // ����Ʈ�� ��� ���� �� �ִ� ���
//			prevNode = H->head; // ��� ��尡 ����Ű�� ��尡 prevNode�� �ǰ� ����
//			delNode = H->head->link; // prevNode ���� ��ġ�� delNode ����
//			while (delNode->link != NULL) { //delNode�� ��������尡 �� ������
//				prevNode = delNode;       // prevNode�� ��ĭ�� ����
//				delNode = prevNode->link; // delNode�� ��ĭ�� ������ ����.
//			}
//			free(delNode);  // ������ ����� �޸� ������ ��ȯ
//			prevNode->link = NULL;
//		}
//	}
//
//	/* ����Ʈ�� Ư�� ��� ����*/
//	void deleteThisNode(HeadNode* H, int deldata) {
//		Node* delNode;  // �����Ϸ��� ���
//		Node* prevNode; // �����Ϸ��� ����� �� ���
//		prevNode = H->head;
//
//		while (prevNode->link->data != deldata) {
//			prevNode = prevNode->link;
//		}
//
//		delNode = prevNode->link;   // prevNode�� ����Ű�� ��尡 ������ ���
//		prevNode->link = delNode->link;  // prevNode�� delNode ���� ��带 ����Ű����
//		free(delNode);  // delNode ����
//
//		cout << deldata << " ������ ���� ���� ��尡 �����ƽ��ϴ�." << endl;
//		return;
//	}
//
//	/* ����Ʈ�� Ư�� ��� ����*/
//	void addThisNode(HeadNode* H, int afterthisdata, int adddata) {
//		// afterthisdata: �� ������ �ڿ� �����ϰ� �ͼ�.
//		// adddata: �� �����͸� �����ϰ� �ͼ�.
//
//		Node* prevNode;  //�����Ϸ��� ����� ���� ���
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
//	/* ����Ʈ�� Ư�� ��� �˻�*/
//	void searchNode(HeadNode* H, int thisdata) {
//		Node* someNode;
//		someNode = H->head;
//
//		while (someNode->data != thisdata) {
//			someNode = someNode->link;
//		}
//		cout << thisdata << " �����͸� �˻��ϴ� �� �����߽��ϴ�." << endl;
//	}
//
//	/* ���Ḯ��Ʈ ���*/
//	void printList(HeadNode* L) {
//		//��� ������� ����Ʈ ���
//		Node* p;
//		cout << "���Ḯ��Ʈ ��� = ( ";
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



