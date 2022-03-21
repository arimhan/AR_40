#include "Matrix.h"

AMatrix AMatrix::operator * (AMatrix const& Matrix)
{
	AMatrix OutMatrix;
	for (int iCol = 0; iCol < 4; iCol++)
	{
		for (int iRow = 0; iRow < 4; iRow++)
		{
			OutMatrix.m[iRow][iCol] = m[iRow][0] * Matrix.m[0][iCol] +
				m[iRow][1] * Matrix.m[1][iCol] +
				m[iRow][2] * Matrix.m[2][iCol] +
				m[iRow][3] * Matrix.m[3][iCol];
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
//�������
void AMatrix::Identity()
{
	//������� ����
	_11 = _12 = _13 = _14 = 0.0f;
	_21 = _22 = _23 = _24 = 0.0f;
	_31 = _32 = _33 = _34 = 0.0f;
	_41 = _42 = _43 = _44 = 0.0f;
	//4x4 0���� ���� ��, �밢�� ���� ���� 1.0f���� ����
	_11 = _22 = _33 = _44 = 1.0f;
}

//��ġ���
AMatrix AMatrix::Transpose()
{
	AMatrix am;
	am._11 = _11;	am._12 = _21;	am._13 = _31;	am._14 = _41;
	am._21 = _12;	am._22 = _22;	am._23 = _32;	am._24 = _42;
	am._31 = _13;	am._32 = _23;	am._33 = _33;	am._34 = _43;
	am._41 = _14;	am._42 = _24;	am._43 = _34;	am._44 = _44;
	return am;
}
//������ ���� �� ��� ���
AMatrix AMatrix::ViewLookAt(AVector3& vPosition, AVector3& vTarget, AVector3& vUp)
{
	AMatrix mat;
	AVector3 vDirection = (vTarget - vPosition).Normal();		//Z Axis
	AVector3 vRightVector = (vUp ^ vDirection).Normal();		//X Axis
	AVector3 vUpVector = (vDirection ^ vRightVector).Normal();	//Y Axis

	_11 = vRightVector.x;		_12 = vUpVector.x;		_13 = vDirection.x;
	_21 = vRightVector.y;		_22 = vUpVector.y;		_23 = vDirection.y;
	_31 = vRightVector.z;		_32 = vUpVector.z;		_33 = vDirection.z;

	_41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
	_42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
	_43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
	memcpy((void*)&mat, this, 16 * sizeof(float));
	return mat;
}
//������ ���� �� ��� ���
AMatrix	AMatrix::CreateViewLook(AVector3& vPosition, AVector3& vTarget, AVector3& vUp)
{
	AMatrix mat;
	AVector3 vDirection = vTarget - vPosition;
	vDirection = vDirection.Normal();
	float fDot = vUp | vDirection;

	//������ �ٻ�ȭ �۾� (���� P���͸� ������ P���� -> ����ȭ �Ͽ� ���Ѵ�)
	AVector3 vUpVector = vUp - (vDirection * fDot);
	vUpVector = vUpVector.Normal();
	AVector3 vRightVector = vUpVector ^ vDirection;

	_11 = vRightVector.x;		_12 = vUpVector.x;		_13 = vDirection.x;
	_21 = vRightVector.y;		_22 = vUpVector.y;		_23 = vDirection.y;
	_31 = vRightVector.z;		_32 = vUpVector.z;		_33 = vDirection.z;

	_41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
	_42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
	_43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
	memcpy((void*)&mat, this, 16 * sizeof(float));

	return mat;
}
//���� ���� ��� ���
AMatrix	AMatrix::PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect)
{
	float h, w, Q;
	h = 1 / tan(fovy * 0.5f);
	w = h / Aspect;
	Q = fFarPlane / (fFarPlane - fNearPlane);

	AMatrix mat;
	memset(this, 0, sizeof(AMatrix));

	_11 = w;
	_22 = h;
	_33 = Q;
	_43 = -Q * fNearPlane;
	_34 = 1;

	memcpy((void*)&mat, this, 16 * sizeof(float));
	return mat;
}


AMatrix::AMatrix() 
{ 
	//AMatrix �����ڷ� ȣ���ϸ鼭 �ٷ� ��������� ������ �� �ֵ��� �Ѵ�.
	Identity(); 
}