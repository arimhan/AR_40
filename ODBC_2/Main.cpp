#include "ODBC.h"


bool main()
{
	setlocale(LC_ALL, "korean");
	AODBC odbc;

	odbc.Init();
	//연결
	odbc.Connect(1, L"\\gameuser.dsn");
	int Select = 0;

	while (cin)
	{

		cout << "                   <<DB관리 프로그램>>    " << endl;
		cout << "해당하는 번호 기입 후 엔터를 눌러주세요!" << endl;
		cout << "계정 생성 1, 계정 삭제 2, 비밀번호 수정 3, 전체계정 조회 4, 종료 9   : ";
		cin >> Select;

		if (Select == 9) break;

		switch (Select)
		{
			case CreateAccount:
			{
				odbc.CreatePrepare();
			}break;
			case Delete:
			{
				odbc.DeleteProcedure();
				odbc.ExecuteDeletePrepare();
			}break;
			case Correction:
			{
				odbc.UpdateProcedure();
				odbc.ExecuteUpDatePrepare();
			}break;
			case AllAccount:
			{
				odbc.ExecuteTableInfo(L"gameuser");
			}break;

		}
		system("pause");
		system("cls");
	}



	//1. 프로시저 삭제 및 업데이트 만들기
	//odbc.CreatePrepare();	// 저장프로시저 호출 -> AccountCreate
	//odbc.DeleteProcedure();	// 저장프로시저 내 값 1개 삭제 후

	//odbc.InsertProcedure();
	//odbc.UpdateProcedure();	// DB값 수정

	odbc.Release();
	return true;

}