#include "ODBC.h"


bool main()
{
	setlocale(LC_ALL, "korean");
	AODBC odbc;

	odbc.Init();
	//����
	//odbc.Connect(0, L"\\gameuser.dsn");
	//1. ���ν��� ���� �� ������Ʈ �����
	odbc.CreatePrepare();	// �������ν��� ȣ�� -> AccountCreate
	odbc.DeleteProcedure();	// �������ν��� �� �� 1�� ���� ��
	/*

	SQLSMALLINT cbCon;
	SQLWCHAR connStrbuf[1024] = { 0, };
	ret = SQLConnect(hDbc, (SQLWCHAR*)SQLID, SQL_NTS, (SQLWCHAR*)SQLSV, SQL_NTS, (SQLWCHAR*)SQLPW, SQL_NTS);
	

	InsertProcedure();
	UpdateProcedure();	// DB�� ����
	*/
	odbc.Release();
	return true;

}