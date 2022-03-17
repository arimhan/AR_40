#include "Matrix.h"

AMatrix AMatrix::operator * (AMatrix const& Matrix)
{
	AMatrix OutMatrix;
	for (int iCol = 0; iCol < 4; iCol++)
	{
		for (int iRow = 0; iRow < 4; iRow++)
		{
			OutMatrix.m[iRow][iCol] = m[iRow][0] * Matrix.m[iCol][0] +
				m[iRow][1] * Matrix.m[iCol][1] +
				m[iRow][2] * Matrix.m[iCol][2] +
				m[iRow][3] * Matrix.m[iCol][3];
		}
	}
	return OutMatrix;
}

void AMatrix::XRotate(float fRadian)
{
	//X�� ����
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);
	_22 = fCos;
	_23 = fSin;
	_32 = -fSin;
	_33 = fCos;
}
void AMatrix::YRotate(float fRadian)
{
	//Y�� ����, Y���� ù��° -Sin ���̸� ������ȣ�� ���� ȸ�������� �޶�����
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);
	_11 = fCos;
	_13 = -fSin;
	_31 = fSin;
	_33 = fCos;
}
void AMatrix::ZRotate(float fRadian)
{
	//Z�� ����
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);
	_11 = fCos;
	_12 = fSin;
	_21 = -fSin;
	_22 = fCos;
}


//���� �� �������
void AMatrix::Translation(const AVector3& v)
{
	//��� �� ���� ������ _41, _42, _43 ���п��� �����Ѵ�
	_41 = v.x;
	_42 = v.y;
	_43 = v.z;
}
void AMatrix::Translation(float x, float y, float z)
{
	_41 = x;
	_42 = y;
	_43 = z;
}
void AMatrix::Scale(const AVector3& v)
{
	//��������� X, Y, Z�� ���п��� �����Ѵ�
	_11 = v.x;
	_22 = v.y;
	_33 = v.z;
}
void AMatrix::Scale(float x, float y, float z)
{
	_11 = x;
	_22 = y;
	_33 = z;
}
//��ġ���
AMatrix AMatrix::Transpose()
{
	AMatrix am;
	am._11 = 11;	am._12 = 21;	am._13 = 31;	am._14 = 41;
	am._21 = 12;	am._22 = 22;	am._23 = 32;	am._24 = 42;
	am._31 = 13;	am._32 = 23;	am._33 = 33;	am._34 = 43;
	am._41 = 14;	am._42 = 24;	am._43 = 34;	am._44 = 44;
	return am;
}


AMatrix::AMatrix() 
{ 
	//AMatrix �����ڷ� ȣ���ϸ鼭 �ٷ� ��������� ������ �� �ֵ��� �Ѵ�.
	Identity(); 
}