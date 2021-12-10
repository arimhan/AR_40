#include <iostream>
const int GetData1()
{
	int iValue = 4;
	return iValue;
}
const int* GetData2()
{
	int iValue = 4;
	return &iValue;
}
const int* const GetData3()
{
	int iValue =4;
	return &iValue;
}
int* const GetData4()
{
	int iValue = 4;
	return &iValue;
}
//=> iValue = 4, return &iValue

void main()
{
	int iRet1 = GetData1();
	int iRet2 = 4;
	const int* pRet = GetData2();
	// iRet1�� 2�� ���� 4�� �����ϸ� pRet�� GetData2�� ���� ������ �� ����! (�� ���ȭ)
	// *pRet = 88; ���� �Ұ����� ���̶�� ���

	const int* iRet3 = GetData3();
	iRet3 = &iRet2;
	// iRet3�� GetData3�� �� ���ȭ�� ����. ���⼭ iRet2�� �ּҰ��� ����?

	const int* const iRet4 = GetData3();
	const int* iRet5 = GetData4();
	iRet5 = &iRet2;
	//*iRet4, iRet4 �� �� �ּ� ���� �Ұ�
	//*iRet5 �� ���� �Ұ�
	//

	int* const iRet6 = GetData4();
	*iRet6 = 9;

	int data1 = 1;
	int data2 = 4;
	const int* dataConst1 = &data1;
	const int const* dataConst3 = &data1;
	int* const dataConst4 = &data1;

	*dataConst4 = 4;
	dataConst1 = &data2;
	int* const dataConst2 = &data1;
	*dataConst2 = 7;

	const int* const dataConst9 = &data1;
}