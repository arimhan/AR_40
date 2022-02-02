#include "Odbc.h"

bool AOdbc::Init()
{
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
	{
		return false;
	}
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		return false;
	}
	return true;
}
bool AOdbc::Connect(const TCHAR* dsn)
{
	SQLWCHAR dir[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, dir);
	std::wstring dbpath = dir;
	dbpath += dsn; //L"\\cigarette.dsn";// L"\\cigarette.accdb";

	SQLTCHAR OutCon[255];
	SQLSMALLINT cbOutCon;
	TCHAR InCon[256] = { 0, };
	//_stprintf(InCon, 
	//	_T("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s;"), dbpath.c_str());
	int iSize = sizeof(OutCon);
	_stprintf(InCon, _T("FileDsn=%s"), dbpath.c_str());
	SQLSMALLINT cbOutLen;
	SQLRETURN ret = SQLDriverConnect(m_hDbc, NULL,
		InCon, _countof(InCon),
		OutCon, _countof(OutCon),
		&cbOutLen, SQL_DRIVER_NOPROMPT);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return false;
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		return false;
	}
	return true;
}
bool AOdbc::ExecTableInfo(const TCHAR* szTableName)
{
	ATableInfo table;
	table.szTableName = szTableName;
	wstring sql = L"select * from ";//tblCigar";
	sql += szTableName;
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql.c_str(), SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}

	SQLSMALLINT iNumCols;
	SQLNumResultCols(m_hStmt, &table.iNumCol);
	for (int iCols = 1; iCols <= table.iNumCol; iCols++)
	{
		AColumnInfo column;
		column.icol = iCols;
		int iSize = _countof(column.szColName);
		SQLDescribeCol(m_hStmt, iCols, column.szColName,
			iSize, &column.NameLengthPtr,
			&column.pfSqlType,
			&column.ColumnSizePtr,
			&column.DecimalDigitsPtr, &column.pfNullable);
		table.ColumnList.push_back(column);
	}
	SQLLEN ITemp;
	TCHAR szData[100][21] = { 0, };
	int iData[100];
	ARecord rData;
	for (int iBind = 0; iBind < table.ColumnList.size(); iBind++)
	{
		switch (table.ColumnList[iBind].pfSqlType)
		{
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		{
			AField data;
			data.iDataType = SQL_UNICODE;
			ret = SQLBindCol(m_hStmt, iBind + 1, SQL_UNICODE, szData[iBind], sizeof(szData[iBind]), &ITemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case SQL_INTEGER:
		{
			AField data;
			data.iDataType = SQL_INTEGER;
			ret = SQLBindCol(m_hStmt, iBind + 1, SQL_INTEGER, &iData[iBind], 0, &ITemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case -7:
		{
			AField data;
			data.iDataType = SQL_C_ULONG;
			ret = SQLBindCol(m_hStmt, iBind + 1, SQL_C_ULONG, &iData[iBind], 0, &ITemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		};
		}
	}
	while (SQLFetch(m_hStmt) != SQL_NO_DATA) //No Data 예외처리
	{
		for (int iCol = 0; iCol < table.ColumnList.size(); iCol++)
		{
			rData.record[iCol].iDataType = rData.record[iCol].iDataType;
			if (rData.record[iCol].iDataType == SQL_UNICODE)
			{
				rData.record[iCol].szData = szData[iCol];
			}
			else
			{
				rData.record[iCol].szData = to_wstring(iData[iCol]);
			}
		}
		m_RealStringData.push_back(rData);
	}
	SQLCloseCursor(m_hStmt);
	m_TableList.push_back(table);
	return true;
}
bool AOdbc::ExecInsert(const TCHAR* sql, int iTableIndex)
{
	TCHAR sql3[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql3, L"insert into tblCigar (name,price, korean) values ('%s',%d,%d)",
					L"디스플러스", 4100, 1);
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql3, SQL_NTS);
	if (ret != SQL_SUCCESS )
	{
		Check();
		return false;
	}	
	SQLLEN len;
	SQLSMALLINT Cols;
	//Select문 제외
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &Cols);
	SQLCloseCursor(m_hStmt);
	return true;
}
void AOdbc::Check()
{
	SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER iSQLCode;
	SQLSMALLINT length;
	SQLError(m_hEnv, m_hDbc,
		m_hStmt,
		szSQLState,
		&iSQLCode,
		errorBuffer,
		sizeof(errorBuffer),
		&length);
	MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}
bool AOdbc::Result(const TCHAR* sql, int iTableIndex)
{
	SQLLEN lName, lPrice, lKorean;
	TCHAR Name[21];
	int Price;
	BOOL Korean;

	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}
	ret = SQLBindCol(m_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &lName);
	ret = SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	ret = SQLBindCol(m_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);

	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql, SQL_NTS);

	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		std::wcout << Name << " " << Price << " " << Korean << std::endl;
	}
	SQLCloseCursor(m_hStmt);



	SQLLEN len;
	SQLSMALLINT iNumCols;
	//Select문 제외
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &iNumCols);


	SQLCloseCursor(m_hStmt);

	return true;
}
bool AOdbc::Exec(const TCHAR* sql)
{
	return true;
}
bool AOdbc::ExecSelect(const TCHAR* sql, int iTableIndex)
{
	SQLLEN lName, lPrice, lKorean;
	TCHAR Name[21];
	int Price;
	BOOL Korean;

	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}

	ret = SQLBindCol(m_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &lName);
	ret = SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	ret = SQLBindCol(m_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);
	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql, SQL_NTS);

	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		std::wcout << Name << " " << Price << " " << Korean << std::endl;
	}
	SQLCloseCursor(m_hStmt);


	SQLLEN len;
	SQLSMALLINT iNumCols;
	//Select문 제외
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &iNumCols);

	// 결과
	//ret = SQLBindCol(m_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &lName);
	//ret = SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	//ret = SQLBindCol(m_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);
	//while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	//{
	//	std::wcout << Name << " " << Price << " " << Korean << std::endl;
	//}
	SQLCloseCursor(m_hStmt);
	return true;
}
bool AOdbc::ExecUpdata(const TCHAR* sql, int iTableIndex)
{	
	TCHAR sql[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf((TCHAR*)sql, L"update tblCigar set name='%s' where name='%s'",
		L"코로나", L"88 Light");
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql, SQL_NTS);
	if (ret != SQL_SUCCESS && ret != SQL_NO_DATA) // 성공여부 및 data여부 동시체크
	{
		Check();
		return false;
	}

	SQLLEN len;
	SQLSMALLINT Cols;
	//Select문 제외
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &Cols);

	SQLCloseCursor(m_hStmt);
	return true;
}
bool AOdbc::ExecDelete(const TCHAR* sql, int iTableIndex)
{
	TCHAR sql2[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql2, L"delete from tblCigar where name='%s'", L"xxxxxx");
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql2, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		Check();
		return false;
	}
	SQLLEN len;
	SQLSMALLINT Cols;
	//Select문 제외
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &Cols);

	SQLCloseCursor(m_hStmt);
	return true;
}
bool AOdbc::Release()
{
	SQLCloseCursor(m_hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	return true;
}