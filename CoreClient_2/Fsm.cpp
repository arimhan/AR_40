#include "Fsm.h"

void AFsm::AddTransition(DWORD dwState, DWORD dwEvent, DWORD dwOutput)
{
	AFsmState* pStateFsm = nullptr;
	auto iter = m_mapStateClass.find(dwState);


	if (iter != m_mapStateClass.end())
	{//m_mapStateClass 여기에 상태가 있으면 second(상태값) 으로 바꿔준다.
		pStateFsm = iter->second;
	}
	else
	{//상태가 없을 경우, 새로 생성해준다.
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
