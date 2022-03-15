#include "Main.h"


bool AMain::Init()
{
	
	//8�������� ���� ������ �Ǵ� 0, 1, ���� ���� �������� ��´�.
	m_VertexList[0].p = AVector3(0.0f, 0.0f, 0.0f);
	m_VertexList[1].p = AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[3].p = AVector3(1.0f, 0.0f, 0.0f);

	//���⺤�� 2���� �̿��� ������ �������� �����Ѵ�.
	AVector3 vDir0 = m_VertexList[1].p - m_VertexList[0].p;
	AVector3 vDir1 = m_VertexList[3].p - m_VertexList[0].p;
	m_VertexList[2].p = (vDir0 + vDir1).Normal();

	//�� �ݴ��� �������� ������ �� �ִ�. 5��, 6��, 7�� ���� ��
	m_VertexList[5].p = (vDir0 * -1.0f).Normal();
	m_VertexList[6].p = ((vDir0 - vDir1) * -1.0f).Normal();
	m_VertexList[7].p = (vDir1 * -1.0f).Normal();

	//4�� ������ ���⺤�Ͱ� 3���� 5���� �ʿ��ϴ�. ���⺤�� �� ���� �� �����Ѵ�.
	vDir0 = m_VertexList[3].p - m_VertexList[0].p;
	vDir1 = m_VertexList[5].p - m_VertexList[0].p;
	m_VertexList[4].p = (vDir0 + vDir1).Normal();
	m_VertexList[8].p = ((vDir0 + vDir1) * -1.0f).Normal();


}
bool AMain::Frame() {}
bool AMain::Render() {}
bool AMain::Release(){}