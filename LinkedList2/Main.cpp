#include "LinkedList.h"

void main()
{
	Singlist list;
	HeadNode* L;
	L = list.createList();

	cout << "1. �� ���� ����Ʈ�� �����߽��ϴ�." << endl << endl;

	int data1, data2, data3;
	cout << "2. ���� ����Ʈ�� �߰��� ����� �����͸� 3�� �����ּ���: ";
	cin >> data1 >> data2 >> data3;
	list.addNode(L, data1);
	list.printList(L);
	list.addNode(L, data2);
	list.printList(L);
	list.addNode(L, data3);
	list.printList(L);
	cout << endl;

	cout << "3. Ž���� ����� �����͸� �����ּ��� : ";
	int data4;
	cin >> data4;
	list.searchNode(L, data4);

	cout << endl;
	cout << "4-1. � ��� �ڿ� ��带 �߰��Ұǰ���? ";
	int data5, data6;
	cin >> data5;
	cout << "4-2. �� ��� �ڿ� � �����͸� ���� ��带 �߰��Ұǰ���? ";
	cin >> data6;
	list.addThisNode(L, data5, data6);
	list.printList(L);
	cout << endl;

	cout << "5. �����ϰ��� �ϴ� ��带 �˷��ּ��� : ";
	int data7;
	cin >> data7;
	list.deleteThisNode(L, data7);
	list.printList(L);
	cout << endl;

	cout << "6. ������ ��带 �����մϴ�." << endl;
	list.deleteNode(L);
	list.printList(L);
	cout << endl;

	cout << "�ǰ��ϴϱ� ������ �����ڽ��ϴ�." << endl;

}

//int main()
//{
//	return 0;
//}
