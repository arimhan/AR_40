#include "Fsm.h"

void AFsm::AddTransition(DWORD dwState, DWORD dwEvent, DWORD dwOutput)
{
	AFsmState* pStateFsm = nullptr;
	auto iter = m_mapStateClass.find(dwState);


	if (iter != m_mapStateClass.end())
	{//m_mapStateClass ���⿡ ���°� ������ second(���°�) ���� �ٲ��ش�.
		pStateFsm = iter->second;
	}
	else
	{//���°� ���� ���, ���� �������ش�.
		pStateFsm = new AFsmState(dwState);
		m_mapStateClass.insert(make_pair(dwEvent, pStateFsm));
	}
	pStateFsm->m_mapEvent.insert(make_pair(dwEvent, dwOutput));
}

DWORD AFsm::GetTransition(DWORD dwState, DWORD dwEvent)
{
	AFsmState* pStateFsm = nullptr;
	auto iterState = m_mapStateClass.find(dwState);
	if (iterState == m_mapStateClass.end())
	{
		// errer
		cout << "GetTransition Errer 1" << endl;
	}
	pStateFsm = iterState->second;
	auto iterOutput = pStateFsm->m_mapEvent.find(dwEvent);
	if (iterOutput == pStateFsm->m_mapEvent.end())
	{
		// errer
		cout << "GetTransition Errer 2" << endl;
	}
	return iterOutput->second;
}
