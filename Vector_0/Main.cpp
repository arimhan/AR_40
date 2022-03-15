#include "Main.h"


bool AMain::Init()
{
	
	//8각형에서 정점 기준이 되는 0, 1, 번을 먼저 기준으로 잡는다.
	m_VertexList[0].p = AVector3(0.0f, 0.0f, 0.0f);
	m_VertexList[1].p = AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[3].p = AVector3(1.0f, 0.0f, 0.0f);

	//방향벡터 2개를 이용해 나머지 정점들을 세팅한다.
	AVector3 vDir0 = m_VertexList[1].p - m_VertexList[0].p;
	AVector3 vDir1 = m_VertexList[3].p - m_VertexList[0].p;
	m_VertexList[2].p = (vDir0 + vDir1).Normal();

	//정 반대인 정점들을 세팅할 수 있다. 5번, 6번, 7번 정점 순
	m_VertexList[5].p = (vDir0 * -1.0f).Normal();
	m_VertexList[6].p = ((vDir0 - vDir1) * -1.0f).Normal();
	m_VertexList[7].p = (vDir1 * -1.0f).Normal();

	//4번 정점은 방향벡터가 3번과 5번이 필요하다. 방향벡터 재 설정 후 구현한다.
	vDir0 = m_VertexList[3].p - m_VertexList[0].p;
	vDir1 = m_VertexList[5].p - m_VertexList[0].p;
	m_VertexList[4].p = (vDir0 + vDir1).Normal();
	m_VertexList[8].p = ((vDir0 + vDir1) * -1.0f).Normal();


}
bool AMain::Frame() {}
bool AMain::Render() {}
bool AMain::Release(){}