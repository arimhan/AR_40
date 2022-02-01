#include "Odbc.h"

void main()
{
	setlocale(LC_ALL, "korean");
	AOdbc odbc;
	odbc.Init();
	wstring dsn = L"\\..\\..\\data\\db\\cigarette.dsn";
	if (odbc.Connect(dsn.c_str()))
	{
		odbc.ExecTableInfo(L"tblCigar");
	}
	wstring sql = L"select * from tblCigar";
	odbc.Result(sql.c_str(), 0);

	//odbc.ExecSelect(sql.c_str(), 0);
	odbc.Release();
}


//	setlocale(LOCALE_ALL, "korean");
//	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS) //ȯ���ڵ� �Ҵ�
//	{
//		return;
//	}
//	SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER); //ȯ���ڵ� ����
//
//	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS) //�����ڵ� �Ҵ�
//	{
//		return;
//	}
//
//	SQLWCHAR dir[MAX_PATH] = { 0, };
//	GetCurrentDirectory(MAX_PATH, dir);
//
//	wstring dbpath = dir;
//	dbpath += L"\\cigarette.accdb";
//
//	TCHAR InCon[256] = { 0, };
//	_stprintf(InCon, _T("DRIVER={Microsoft Access Driver (*.mdb, *accdb)};DBQ=%s;"), dbpath.c_str());
//
//	SQLSMALLINT cbOutLen;
//	//���� �ڵ��� �Ҵ��ϸ� ���� ������ �ҽ��� ������ �� �ִ�
//
//	SQLRETURN ret = SQLDriverConnect(m_hDbc, NULL, InCon, _countof(InCon), NULL, 0, &cbOutLen, SQL_DRIVER_NOPROMPT);
//
//	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//	{
//		return;
//	}
//	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS) //����ڵ� �Ҵ�
//	{
//		return;
//	}
//	SQLLEN IName, IPrice, IKorean;
//	TCHAR Name[21];
//
//	int Price;
//	BOOL Korean;
//	//���
//
//	//ù��° �ʵ�� ������ ���ڵ���� ��������
//	ret = SQLBindCol(m_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &IName);
//	ret = SQLBindCol(m_hStmt, 2, SQL_C_ULONG, &Price, 0, &IPrice);
//	ret = SQLBindCol(m_hStmt, 3, SQL_C_ULONG, &Korean, 0, &IKorean);
//
//	//tblCigar�� ��� ������(*)�� ã����
//	TCHAR sql[MAX_PATH] = L"select * from tblCigar";
//
//	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql, SQL_NTS);
//
//	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
//	{
//		wcout << Name << " " << Price << " " << Korean << endl;
//	}
//	SQLCloseCursor(m_hStmt);
//
//	TCHAR sql2[MAX_PATH] = { 0, };
//	//L"select Name, Price, Korean from tblCigar = '%s'";
//	wsprintf(sql2, L"select Name, Price, Korean from tblCigar where name = '%s'", L"���");
//	//Cigar ���̺��� �̸��� ��̿� ���� ������ �ּ���
//	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql2, SQL_NTS);
//
//	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
//	{
//		wcout << Name << " " << Price << " " << Korean;
//	}
//	SQLCloseCursor(m_hStmt);
//
//	TCHAR sql3[MAX_PATH] = { 0, };
//	//L"select Name, Price, Korean from tblCigar = '%s'";
//	wsprintf(sql3, L"insert into tblCigar (name, price, korean) VALUE ('%s', %d, %d)", L"����", 4500, 1);
//	//���̺� �߰�
//	ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)&sql3, SQL_NTS);
//	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
//	{
//		wcout << Name << " " << Price << " " << Korean;
//	}
//	SQLCloseCursor(m_hStmt);
//
//	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
//	SQLDisconnect(m_hDbc);
//	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
//	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
//}
//
//
