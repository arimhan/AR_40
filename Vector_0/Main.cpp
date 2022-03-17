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

	m_iNumVertex = sizeof(m_VertexList) / sizeof(m_VertexList[0]); //버텍스 리스트는 버텍스리스트를 0번값으로 나누어준다.

	//VertexObj의 형태 그리기
	DWORD indiced[] =
	{
		0,1,2,
		0,2,3,
		0,3,4,
		0,4,5,
		0,5,6,
		0,6,7,
		0,7,8,
	};
	m_iNumIndex = sizeof(indiced) / sizeof(indiced[0]);

	//VertexObj를 해당하는 쉐이더(hlsl) 파일을 불러와 그릴 수 있도록 한다. 
	//Client.h 내 Attach함수를 사용해 VertexShader -> PixelShader -> GeometryShader 순으로 진행한다.
	//InputLayout으로 
	//D3D10_INPUT_ELEMENT_DESC함수를 활용한다.

}



bool AMain::Frame() {}
bool AMain::Render() {}
bool AMain::Release(){}