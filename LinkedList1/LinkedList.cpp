#include "LinkedList.h"

LinkedList::LinkedList() 
{
    m_pHead =  new Node();
    m_pTail = m_pHead;
    m_iCount = 0;
    //생성자에서, 머리 = Node 동적할당
    // 꼬리 = 머리 연결
    // 카운트 0으로 초기화
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
    //소멸자에서 머리->GetNext(next찾아오기)값을 *Temp로 가리키고 머리데이터 삭제
    // m_iCount갯수만큼 돌면서 머리 -> Temp->next값 가져와 temp에 넣고 머리데이터 삭제
}
int LinkedList::GetDataCount()
{
    return m_iCount;
}
void LinkedList::Insert(int data) 
{
    Node* pNode = new Node(data);
    cout << m_iCount + 1 << "번째 노드 생성 " << "데이터: " << pNode->GetData() << endl;
    m_pTail->SetNext(pNode);
    m_pTail = pNode;
    m_iCount++;
    //노드 생성 시, data를 받아 *pNode 동적할당 및 생성
    // 꼬리->Next (pNode)연결 
    // -> 중간삽입이 아닌 맨 뒤에 삽입하는 코드이므로 꼬리->next에 현재 만드려는 노드를 가르키도록 설정
    // 꼬리 = pNode 연결
    //Count값 증가 (생성 시 마다)
}
bool LinkedList::Delete(int deldata) 
{
    Node* pTemp = m_pHead;
    Node* Temp = pTemp->GetNext();

    if (m_pHead->GetNext() == nullptr)
    {
        cout << "노드 없음!!" << endl;
        return false;
    }
    for (int i = 0; i < m_iCount; i++)
    {
        if (Temp->GetData() == deldata) //삭제데이터
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

    //포인터 변수 2개를 만들어 사용
    //삭제에 사용할 Temp 포인터 변수, Temp앞 노드를 가리키는 포인터 변수
    //노드가 없을 시 return false 하도록 bool 타입으로 세팅
    //Temp = Temp 다음을 가리킬 주소를 받고, pTemp은 Temp의 앞노드를 가르키도록 해
    //데이터 찾을 시 Temp의 앞 노드와 Temp의 다음노드를 연결해준다.
    //만일 끝에 있는 데이터일 경우 꼬리를 바꿔준다.
}
void LinkedList::Display() 
{
    Node* Temp = m_pHead->GetNext();
    for (int i = 0; i < m_iCount; i++)
    {
        cout << i + 1 << " 번째 데이터: " << Temp->GetData() << endl;
        Temp = Temp->GetNext();
    }
    //*Temp = m_pHead->next를 얻어와 가리키고
    //m_iCount 수 만큼 data를 불러오며 출력처리
    // Temp는 Temp -> next를 얻어와 넣기
}