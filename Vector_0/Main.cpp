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

	m_iNumVertex = sizeof(m_VertexList) / sizeof(m_VertexList[0]); //���ؽ� ����Ʈ�� ���ؽ�����Ʈ�� 0�������� �������ش�.

	//VertexObj�� ���� �׸���
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

	//VertexObj�� �ش��ϴ� ���̴�(hlsl) ������ �ҷ��� �׸� �� �ֵ��� �Ѵ�. 
	//Client.h �� Attach�Լ��� ����� VertexShader -> PixelShader -> GeometryShader ������ �����Ѵ�.
	//InputLayout���� 
	//D3D10_INPUT_ELEMENT_DESC�Լ��� Ȱ���Ѵ�.

}



bool AMain::Frame() {}
bool AMain::Render() {}
bool AMain::Release(){}