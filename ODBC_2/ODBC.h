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

enum menu {CreateAccount = 1, Delete,  Correction, AllAccount,};

struct AColInfo
{
	SQLSMALLINT	 iCol;
	SQLWCHAR	 szColName[20];
	SQLSMALLINT	 bufferLen;
	SQLSMALLINT	 NameLenPtr;
	SQLSMALLINT  pfSqlType;
	SQLULEN		 ColSizePtr;
	SQLSMALLINT	 DecimalDigitsPtr;
	SQLSMALLINT  pfNullable;
};
struct ATableInfo
{
	vector<AColInfo> ColList;
	SQLSMALLINT		 iNumcol;
	wstring			 szTableName;
};
struct AField
{
	wstring szData;
	int		iDataType;
};
struct ARecord
{
	vector<AField> record;
};

class AODBC
{
public:

	SQLHENV		m_hEnv;//hEnv = SQL_NULL_HENV;
	SQLHDBC		m_hDbc;//hDbc = SQL_NULL_HDBC;
	SQLHSTMT	m_hStmt;//hStmt = SQL_NULL_HSTMT;
	SQLHSTMT	m_stmtAccount;//Account = SQL_NULL_HSTMT;
	SQLHSTMT	m_stmtAccountDel;
	SQLHSTMT	m_stmtUpdate;
	
	vector<ATableInfo> m_TableList;
	vector<ARecord>	   m_StringData;
	SQLWCHAR	id[10];
	SQLWCHAR	pw[10];

public:
	bool Init();
	bool Connect(int iType, const TCHAR* dsn);
	void Check();
	bool ExecTableInfo(const TCHAR* szTableName);
	void Release();

	void CreatePrepare();
	void ExecutePrepare();

	void DeleteProcedure();
	void ExecuteDeletePrepare();

	void UpdateProcedure();
	void ExecuteUpDatePrepare();

};

