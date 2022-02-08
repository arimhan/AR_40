#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <tchar.h>
#include <iostream>

void ErrorMsg(SQLHENV henv, SQLHDBC hdbc, SQLHSTMT stmt)
{
	SQLTCHAR buffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLTCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
	SQLINTEGER sqlcode;
	SQLSMALLINT length;
	while (SQLError(henv, hdbc, stmt, sqlstate, &sqlcode, buffer, SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS)
	{
		std::cout << "" << buffer;
	}
}

void main()
{
	SQLHENV henv = SQL_NULL_HENV;
	SQLHDBC hdbc = SQL_NULL_HDBC;
	SQLHSTMT hstmt = SQL_NULL_HSTMT;
	SQLRETURN retcode;

	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, 0);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);

	SQLSMALLINT cbCon;
	SQLWCHAR connStrbuf[1024] = { 0, };
	retcode = SQLDriverConnect(hdbc, GetDesktopWindow(), (SQLWCHAR*)L"Driver={SQL Server}", 
		SQL_NTS, (SQLWCHAR*)connStrbuf, _countof(connStrbuf), &cbCon, SQL_DRIVER_PROMPT);
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;
	//SQLHSTSM, 1번째, 해당 값 return
	retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);

	//2,3번째 문자열로 값 input
	SQLWCHAR id[10] = L"test";
	retcode = SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL);
	SQLWCHAR pw[10] = L"1111";
	retcode = SQLBindParameter(hstmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(pw), 0, id, sizeof(id), NULL);


	//sql 해당 data table 불러오기
	TCHAR callsp[] = L"{?=call AccountCreate(?,?)}";
	retcode = SQLPrepare(hstmt, callsp, SQL_NTS);
	//retcode = SQLExecDirect(hstmt, callsp, SQL_NTS);
	retcode = SQLExecute(hstmt);
	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		// 에러메시지 출력 
		ErrorMsg(henv, hdbc, hstmt);
		return;
	}
	while (SQLMoreResults(hstmt) != SQL_NO_DATA);

	SQLFreeStmt(hstmt, SQL_UNBIND);
	SQLFreeStmt(hstmt, SQL_RESET_PARAMS);
	SQLCloseCursor(hstmt);


	SQLHSTMT hstmt1 = SQL_NULL_HSTMT;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt1);
	SWORD sReturn1 = 0;
	SQLLEN cbRetParam1 = SQL_NTS;
	retcode = SQLBindParameter(hstmt1, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn1, 0, &cbRetParam1);

	SQLWCHAR id1[10] = L"arimhan";
	retcode = SQLBindParameter(hstmt1, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id1), 0, id1, sizeof(id1), NULL);
	SQLWCHAR outpw[10] = { 0, };
	retcode = SQLBindParameter(hstmt1, 3, SQL_PARAM_OUTPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(outpw), 0, outpw, sizeof(outpw), NULL);

	TCHAR callsp1[] = L"{?=call CheckPaswordRet(?,?)}";
	retcode = SQLPrepare(hstmt1, callsp1, SQL_NTS);
	retcode = SQLExecute(hstmt1);


	if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO)
	{
		ErrorMsg(henv, hdbc, hstmt);
		return;
	}
	while (SQLMoreResults(hstmt1) != SQL_NO_DATA);

	SQLFreeStmt(hstmt1, SQL_UNBIND);
	SQLFreeStmt(hstmt1, SQL_RESET_PARAMS);
	SQLCloseCursor(hstmt1);

	return;
}