#include "Thread.h"

void AThread::Create()
{
    if (m_bStarted != false) return;
	m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID);
    m_bStarted = true;
}
void AThread::Create(LPVOID pObject)
{
    if (m_bStarted != false) return;
    m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID);
    m_pObject = pObject;
    m_bStarted = true;
}
bool AThread::RunServer() { return false; }
unsigned int WINAPI	AThread::Runner(LPVOID param)
{
    AThread* pThread = (AThread*)param;
    if (pThread != nullptr)
    {
        pThread->RunServer();
        return 1;
    }
    return 0;
}
void AThread::Join() { ::WaitForSingleObject((HANDLE)m_hThread, INFINITE); }
void AThread::Detach() { CloseHandle((HANDLE)m_hThread); }

AThread::AThread() 
{
    m_bStarted = false;
    m_pObject = nullptr;
}
AThread::AThread(LPVOID pValue)
{
    m_bStarted = false;
    m_pObject = nullptr;
    Create(pValue);
}
AThread::~AThread() 
{ 
    CloseHandle((HANDLE)m_hThread); 
}