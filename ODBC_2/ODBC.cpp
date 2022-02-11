#include "ODBC.h"

bool AODBC::Init()
{
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS) { return false; }
	//ȯ�漳�� 3_8V (ODBC DRIVER 17)
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS) { return false; }
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS) { return false; }
	return true;
}
bool AODBC::Connect(int iType, const TCHAR* dsn)
{
	cout << "������ ������ �õ��մϴ�...��ȭ���ڰ� �߸� ���� : 127.0.0.1" << endl;
	cout << "ID : sa, PW : rksk!312 �Է� �� KGCAGAME�� ������ �������ּ���!" << endl;

	SQLTCHAR OutCon[255];
	//SQLSMALLINT cbOutCon;
	TCHAR InCon[256] = { 0, };
	int iSize = sizeof(OutCon);
	SQLSMALLINT cbOutLen;
	SQLRETURN ret;

	switch (iType)
	{
		case 0:
		{
			//dsn���� ����
			_stprintf(InCon, _T("Dsn=%s"), dsn);
			ret = SQLConnect(m_hDbc, (SQLTCHAR*)dsn, SQL_NTS, (SQLTCHAR*)SQLID, SQL_NTS, (SQLTCHAR*)SQLPW, SQL_NTS);
		} break;
		case 1:
		{
			SQLWCHAR dir[MAX_PATH] = { 0, };
			GetCurrentDirectory(MAX_PATH, dir);
			wstring dbpath = dir;
			dbpath += L"\\gameuser.dsn";
			_stprintf(InCon, _T("FileDsn=%s"),dbpath.c_str());
			//_stprintf(InCon, _T("%S"), _T("Driver = {SQL Server};Server=directx.kr;Address=127.0.0.1,1433;Network=dbmssocn;Database=KGCAGAME;id=sa;pw=rksk!312}"));
			ret = SQLDriverConnect(m_hDbc, NULL, InCon, _countof(InCon), OutCon, _countof(OutCon), &cbOutLen, SQL_DRIVER_NOPROMPT);
			//NOPROMPT �ڵ� , PROMPT ����
		}break;
		case 2:
		{
			//SQL SERVER ��ȭ���� -> 127.0.0.1 / sa, rksk!312 /KGCAGAME
			HWND hWnd = GetDesktopWindow();
			SQLSMALLINT len;
			ret = SQLDriverConnect(m_hDbc, hWnd, (SQLWCHAR*)L"Driver={SQL Server}", SQL_NTS, (SQLWCHAR*)InCon, _countof(InCon), &len, SQL_DRIVER_PROMPT);
			//NOPROMPT �ڵ� , PROMPT ����
		}break;
	};


	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return false;
	}
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		return false;
	}
	cout << "���� �Ϸ�!";
	return true;
}
void AODBC::Check()
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

void AODBC::CreatePrepare()
{
	SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_stmtAccount);
	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;
	ret = SQLBindParameter(m_stmtAccount, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
	ret = SQLBindParameter(m_stmtAccount, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL);
	ret = SQLBindParameter(m_stmtAccount, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(pw), 0, pw, sizeof(pw), NULL);

	//���� ����
	TCHAR callsp[] = L"{? = call AccountCreate(?,?)}";
	ret = SQLPrepare(m_stmtAccount, callsp, SQL_NTS);

	ExecutePrepare();
}
void AODBC::ExecutePrepare()
{
	SQLRETURN ret;

	wcout << L"���� ID: ";
	wcin >> ID;
	wcout << L"���� PW: ";
	wcin >> PW;

	memcpy(id, ID, sizeof(id));
	memcpy(pw, PW, sizeof(pw));
	ret = SQLExecute(m_stmtAccount);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return;
	}
	cout << "���� ������ �Ϸ�Ǿ����ϴ�." << endl;
}

void AODBC::DeleteProcedure()
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_stmtAccountDel);
	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;

	ret = SQLBindParameter(m_stmtAccountDel, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
	ret = SQLBindParameter(m_stmtAccountDel, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL);

	TCHAR callspDel[] = L"{? = call DeleteUser(?)}";
	ret = SQLPrepare(m_stmtAccountDel, callspDel, SQL_NTS);

	wcout << L"���� ID: ";
	wcin >> ID;
	memcpy(id, ID, sizeof(id));

	ret = SQLExecute(m_stmtAccount);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return;
	}
	while (SQLMoreResults(m_stmtAccount) != SQL_NO_DATA);
	SQLFreeStmt(m_stmtAccountDel, SQL_CLOSE);
	SQLCloseCursor(m_stmtAccountDel);
	
	/*
	TCHAR callspDel[MAX_PATH] = { 0, };
	wsprintf(callspDel, L"delete from gameuser where userid = '%s'", L"test");
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&callspDel, SQL_NTS);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
	}
	SQLLEN len;
	SQLSMALLINT cols;
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &cols);

	SQLCloseCursor(m_hStmt);
	*/
}
void AODBC::ExecuteDelPrepare()
{
}
void AODBC::UpdateProcedure()
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_stmtUpdate);
	SWORD sReturn = 0;



	TCHAR callspIn[MAX_PATH] = { 0, };
	wsprintf(callspIn, L"update from gameuser ()values ('%s')", L"3333");
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&callspIn, SQL_NTS);
	if (ret != SQL_SUCCESS)
	{
		//check();
		return;
	}
	SQLLEN len;
	SQLSMALLINT cols;
	SQLRowCount(m_hStmt, &len);
	SQLNumResultCols(m_hStmt, &cols);

	SQLCloseCursor(m_hStmt);
}

void AODBC::ExecuteUpDatePrepare()
{
}

void AODBC::Release()
{
	SQLCloseCursor(m_hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	SQLDisconnect(m_hDbc);
}