#include "ODBC.h"

bool AODBC::Init()
{
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) { return false; }
	//환경설정 3_8V (ODBC DRIVER 17)
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS) { return false; }
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) { return false; }
	return true;
}
bool AODBC::Connect(int iType, const TCHAR* dsn)
{
	SQLTCHAR OutCon[255];
	int iSize = sizeof(OutCon);
	SQLRETURN ret;

	//dsn으로 연결
	_stprintf(Incon, _T("Dsn=%s"), dsn);
	ret = SQLConnect(hDbc, (SQLTCHAR*)dsn, SQL_NTS, (SQLTCHAR*)L"sa", SQL_NTS, (SQLTCHAR*) L"rksk!312", SQL_NTS);

	return true;
}
void AODBC::Check()
{
	SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER iSQLCode;
	SQLSMALLINT length;
	SQLError(hEnv, hDbc, hStmt, szSQLState, &iSQLCode, errorBuffer, sizeof(errorBuffer), &length);
	MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}

bool AODBC::CreatePrepare()
{
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &g_stmtAccount);
	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;
	ret = SQLBindParameter(g_stmtAccount, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
	ret = SQLBindParameter(g_stmtAccount, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL);
	ret = SQLBindParameter(g_stmtAccount, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(pw), 0, pw, sizeof(pw), NULL);

	TCHAR callsp[] = L"{? = call AccountCreate(?,?)}";
	ret = SQLPrepare(g_stmtAccount, callsp, SQL_NTS);
	
	return true;
}

bool AODBC::DeleteProcedure()
{
	TCHAR callspDel[MAX_PATH] = { 0, };
	wsprintf(callspDel, L"delete from gameuser where userid = '%s'", L"3333");
	ret = SQLExecDirect(hStmt, (SQLTCHAR*)&callspDel, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		//check();
		return false;
	}
	SQLLEN len;
	SQLSMALLINT cols;
	SQLRowCount(hStmt, &len);
	SQLNumResultCols(hStmt, &cols);

	SQLCloseCursor(hStmt);
	return true;

}
bool AODBC::InsertProcedure()
{
	TCHAR callspIn[MAX_PATH] = { 0, };
	wsprintf(callspIn, L"insert from gameuser ()values ('%s')", L"3333");
	ret = SQLExecDirect(hStmt, (SQLTCHAR*)&callspIn, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		//check();
		return false;
	}
	SQLLEN len;
	SQLSMALLINT cols;
	SQLRowCount(hStmt, &len);
	SQLNumResultCols(hStmt, &cols);

	SQLCloseCursor(hStmt);
	return true;
}
bool AODBC::UpdateProcedure()
{
	return true;
}

void AODBC::Release()
{
	SQLCloseCursor(hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	SQLDisconnect(hDbc);
}