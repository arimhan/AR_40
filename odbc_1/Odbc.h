#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <vector>
#include <sql.h>
#include <sqlext.h>
using namespace std;

struct AColumnInfo
{
	SQLUSMALLINT		icol;
	SQLWCHAR			szColName[20];
	SQLSMALLINT			BufferLength;
	SQLSMALLINT			NameLengthPtr;
	SQLSMALLINT			pfSqlType;
	SQLULEN				ColumnSizePtr;
	SQLSMALLINT			DecimalDigitsPtr;
	SQLSMALLINT			pfNullable;
};
struct ATableInfo
{
	vector<AColumnInfo> ColumnList;
	SQLSMALLINT		    iNumCol;
	wstring			    szTableName;
};
struct AField
{
	wstring				szData;
	int					iDataType;
};
struct ARecord
{
	vector<AField>		record;
};
class AOdbc
{
public:
	SQLHENV				m_hEnv;//m_hEnv; 전역이었던 변수들 멤버변수로 전부 수정
	SQLHDBC				m_hDbc;
	SQLHSTMT			m_hStmt;
	vector<ATableInfo>	m_TableList;
	vector<ARecord>		m_RealStringData;
public:
	bool Init();
	bool Connect(const TCHAR* dsn);
	bool Release();
	bool ExecTableInfo(const TCHAR* szTableName);
	bool Exec(const TCHAR* sql);
	bool ExecSelect(const TCHAR* sql, int iTableIndex = 0);
	bool ExecUpdata(const TCHAR* sql, int iTableIndex = 0);
	bool ExecDelete(const TCHAR* sql, int iTableIndex = 0);
	bool ExecInsert(const TCHAR* sql, int iTableIndex = 0);
	void Check();

public:
	bool Result(const TCHAR* sql, int iTableIndex = 0);
};

