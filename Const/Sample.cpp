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
	// iRet1과 2는 값이 4로 동일하며 pRet은 GetData2의 값을 변경할 수 없다! (값 상수화)
	// *pRet = 88; 수정 불가능한 식이라고 경고

	const int* iRet3 = GetData3();
	iRet3 = &iRet2;
	// iRet3은 GetData3의 값 상수화인 상태. 여기서 iRet2의 주소값을 넣음?

	const int* const iRet4 = GetData3();
	const int* iRet5 = GetData4();
	iRet5 = &iRet2;
	//*iRet4, iRet4 값 및 주소 변경 불가
	//*iRet5 값 변경 불가
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