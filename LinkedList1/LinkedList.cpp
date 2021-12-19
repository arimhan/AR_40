#include "LinkedList.h"

LinkedList::LinkedList() 
{
    m_pHead =  new Node();
    m_pTail = m_pHead;
    m_iCount = 0;
    //�����ڿ���, �Ӹ� = Node �����Ҵ�
    // ���� = �Ӹ� ����
    // ī��Ʈ 0���� �ʱ�ȭ
}
LinkedList::~LinkedList()
{
    Node* Temp = m_pHead->GetNext();
    delete m_pHead;
    for (int i = 0; i < m_iCount; i++)
    {
        m_pHead = Temp;
        Temp = Temp->GetNext();
        delete m_pHead;
    }
    //�Ҹ��ڿ��� �Ӹ�->GetNext(nextã�ƿ���)���� *Temp�� ����Ű�� �Ӹ������� ����
    // m_iCount������ŭ ���鼭 �Ӹ� -> Temp->next�� ������ temp�� �ְ� �Ӹ������� ����
}
int LinkedList::GetDataCount()
{
    return m_iCount;
}
void LinkedList::Insert(int data) 
{
    Node* pNode = new Node(data);
    cout << m_iCount + 1 << "��° ��� ���� " << "������: " << pNode->GetData() << endl;
    m_pTail->SetNext(pNode);
    m_pTail = pNode;
    m_iCount++;
    //��� ���� ��, data�� �޾� *pNode �����Ҵ� �� ����
    // ����->Next (pNode)���� 
    // -> �߰������� �ƴ� �� �ڿ� �����ϴ� �ڵ��̹Ƿ� ����->next�� ���� ������� ��带 ����Ű���� ����
    // ���� = pNode ����
    //Count�� ���� (���� �� ����)
}
bool LinkedList::Delete(int deldata) 
{
    Node* pTemp = m_pHead;
    Node* Temp = pTemp->GetNext();

    if (m_pHead->GetNext() == nullptr)
    {
        cout << "��� ����!!" << endl;
        return false;
    }
    for (int i = 0; i < m_iCount; i++)
    {
        if (Temp->GetData() == deldata) //����������
        {
            pTemp->SetNext(Temp->GetNext()); //
            if (Temp == nullptr)
            {
                m_pTail = pTemp;
            }
            delete Temp;
            m_iCount--;
            break;
        }
        pTemp = Temp;
        Temp = Temp->GetNext();
    }
    return true;

    //������ ���� 2���� ����� ���
    //������ ����� Temp ������ ����, Temp�� ��带 ����Ű�� ������ ����
    //��尡 ���� �� return false �ϵ��� bool Ÿ������ ����
    //Temp = Temp ������ ����ų �ּҸ� �ް�, pTemp�� Temp�� �ճ�带 ����Ű���� ��
    //������ ã�� �� Temp�� �� ���� Temp�� ������带 �������ش�.
    //���� ���� �ִ� �������� ��� ������ �ٲ��ش�.
}
void LinkedList::Display() 
{
    Node* Temp = m_pHead->GetNext();
    for (int i = 0; i < m_iCount; i++)
    {
        cout << i + 1 << " ��° ������: " << Temp->GetData() << endl;
        Temp = Temp->GetNext();
    }
    //*Temp = m_pHead->next�� ���� ����Ű��
    //m_iCount �� ��ŭ data�� �ҷ����� ���ó��
    // Temp�� Temp -> next�� ���� �ֱ�
}