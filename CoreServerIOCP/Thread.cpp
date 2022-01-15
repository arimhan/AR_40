#include "Thread.h"

void AThread::Create()
{
    if (m_bStarted != false) return;
	m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID);
    m_bStarted = true;
    //_ACRTIMP uintptr_t __cdecl _beginthreadex(
    //    //typedef unsigned __int64
    //    _In_opt_  void* _Security,
    //    _In_      unsigned                 _StackSize,
    //    _In_      _beginthreadex_proc_type _StartAddress,
    //    _In_opt_  void* _ArgList,
    //    _In_      unsigned                 _InitFlag,
    //    _Out_opt_ unsigned* _ThrdAddr
    //);

}
void AThread::Create(LPVOID pObject)
{
    if (m_bStarted != false) return;
    m_hThread = _beginthreadex(nullptr, 0, Runner, this, 0, &m_iID);
    m_pObject = pObject;
    m_bStarted = true;
}
bool AThread::Run() { return false; }
unsigned int WINAPI	AThread::Runner(LPVOID param)
{
    AThread* pThread = (AThread*)param;
    if (pThread != nullptr)
    {
        pThread->Run();
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
{ CloseHandle((HANDLE)m_hThread); 
}