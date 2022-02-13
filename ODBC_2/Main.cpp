#include "ODBC.h"


bool main()
{
	setlocale(LC_ALL, "korean");
	AODBC odbc;

	odbc.Init();
	//����
	odbc.Connect(1, L"\\gameuser.dsn");
	int Select = 0;

	while (cin)
	{

		cout << "                   <<DB���� ���α׷�>>    " << endl;
		cout << "�ش��ϴ� ��ȣ ���� �� ���͸� �����ּ���!" << endl;
		cout << "���� ���� 1, ���� ���� 2, ��й�ȣ ���� 3, ��ü���� ��ȸ 4, ���� 9   : ";
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



	//1. ���ν��� ���� �� ������Ʈ �����
	//odbc.CreatePrepare();	// �������ν��� ȣ�� -> AccountCreate
	//odbc.DeleteProcedure();	// �������ν��� �� �� 1�� ���� ��

	//odbc.InsertProcedure();
	//odbc.UpdateProcedure();	// DB�� ����

	odbc.Release();
	return true;

}