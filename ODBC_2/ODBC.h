#define _CRT_SECURE_NO_WARNINGS
#pragma once
//--------------------------------------------------------------------
#define SQLSV L"KGCATEST" //ODBC 서버 이름 (KGCAGAME을 가리키는)
#define SQLID L"sa"
#define SQLPW L"rksk!312"
//--------------------------------------------------------------------
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class AODBC
{
public:


	SQLHENV		hEnv = SQL_NULL_HENV;
	SQLHDBC		hDbc = SQL_NULL_HDBC;
	SQLHSTMT	hStmt = SQL_NULL_HSTMT;
	SQLHSTMT	g_stmtAccount = SQL_NULL_HSTMT;
	SQLRETURN	ret;

	SQLWCHAR	id[10] = L"NONE";
	SQLWCHAR	pw[10] = L"NONE";
	TCHAR		Incon[256] = { 0, };
	//SQLHSTMT	m_hStmtArrat[5];

public:
	bool Init();
	bool Connect(int iType, const TCHAR* dsn);
	void Check();
	
	bool CreatePrepare();
	bool DeleteProcedure();
	bool InsertProcedure();
	bool UpdateProcedure();

	void Release();
};

