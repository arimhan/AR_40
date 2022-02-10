#include "ODBC.h"


bool main()
{
	setlocale(LC_ALL, "korean");
	AODBC odbc;

	odbc.Init();
	//연결
	//odbc.Connect(0, L"\\gameuser.dsn");
	//1. 프로시저 삭제 및 업데이트 만들기
	odbc.CreatePrepare();	// 저장프로시저 호출 -> AccountCreate
	odbc.DeleteProcedure();	// 저장프로시저 내 값 1개 삭제 후
	/*

	SQLSMALLINT cbCon;
	SQLWCHAR connStrbuf[1024] = { 0, };
	ret = SQLConnect(hDbc, (SQLWCHAR*)SQLID, SQL_NTS, (SQLWCHAR*)SQLSV, SQL_NTS, (SQLWCHAR*)SQLPW, SQL_NTS);
	

	InsertProcedure();
	UpdateProcedure();	// DB값 수정
	*/
	odbc.Release();
	return true;

}