#include "LinkedList.h"

LinkedList::LinkedList() 
{
    m_pHead =  new Node();
    m_pTail = m_pHead;
    m_iCount = 0;
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
}

bool LinkedList::AddNode(int pData)
{
    return false;
}

bool LinkedList::DeleteNode(int pData)
{
    return false;
}

void LinkedList::SearchNode()
{
}

void LinkedList::EditNode()
{
}

void LinkedList::Draw()
{
    
}
