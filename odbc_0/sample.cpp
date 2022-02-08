#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <sql.h>
#include <sqlext.h>


SQLHENV		g_hEnv;			//ȯ���ڵ�
SQLHDBC		g_hDbc;			//�����ڵ�
SQLHSTMT	g_hStmt;		//����ڵ�
//SQLHDESC	g_hDesc;		//������ �ڵ�

void Check()
{
	SQLTCHAR szSQLState[SQL_SQLSTATE_SIZE + 1];
	SQLTCHAR errorBuffer[SQL_MAX_MESSAGE_LENGTH + 1];
	SQLINTEGER iSQLCode;
	SQLSMALLINT length;
	SQLError(g_hEnv, g_hDbc,
		g_hStmt,
		szSQLState,
		&iSQLCode,
		errorBuffer,
		sizeof(errorBuffer),
		&length);
	MessageBox(NULL, errorBuffer, szSQLState, MB_OK);
}
void main()
{


	setlocale(LC_ALL, "korean");
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv) != SQL_SUCCESS)
	{
		return;
	}
	if (SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION,
		(SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return;
	}
	if (SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc) != SQL_SUCCESS)
	{
		return;
	}
	SQLWCHAR dir[MAX_PATH] = { 0, };
	GetCurrentDirectory(MAX_PATH, dir);
	std::wstring dbpath = dir;
	dbpath += L"\\cigarette.dsn"; //L"\\cigarette.dsn";// L"\\cigarette.accdb";

	SQLTCHAR OutCon[255];
	SQLSMALLINT cbOutCon;
	TCHAR InCon[256] = { 0, };
	//_stprintf(InCon, 
	//	_T("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=%s;"), dbpath.c_str());
	int iSize = sizeof(OutCon);
	_stprintf(InCon, _T("FileDsn=%s"), dbpath.c_str());
	SQLSMALLINT cbOutLen;
	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL,
		InCon, _countof(InCon),
		OutCon, _countof(OutCon),
		&cbOutLen, SQL_DRIVER_NOPROMPT);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return;
	}

	if (SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt) != SQL_SUCCESS)
	{
		return;
	}

	SQLLEN lName, lPrice, lKorean;
	TCHAR Name[21];
	int Price;
	BOOL Korean;

	// ���
	ret = SQLBindCol(g_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &lName);
	ret = SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	ret = SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);

	TCHAR sql[MAX_PATH] = L"select * from tblCigar";


	//SQLRETURN SQL_API SQLExecDirectW
	//(
	//	SQLHSTMT    hstmt,				//���� �ڵ�
	//	_In_reads_opt_(TextLength) SQLWCHAR * szSqlStr, //������ SQL��
	//	SQLINTEGER  TextLength			//SQL���� ���ڿ� ����
	//);
	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql, SQL_NTS);

	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		std::wcout << Name << " " << Price << " " << Korean << std::endl;
	}
	SQLCloseCursor(g_hStmt);

	//SQLRETURN  SQL_API SQLBindCol(
	//	SQLHSTMT StatementHandle,            //��� �ڵ�
	//	SQLUSMALLINT ColumnNumber,			 //���ε� �� �÷��� ��ȣ
	//	SQLSMALLINT TargetType,				 //������ Ÿ��
	//	_Inout_updates_opt_(_Inexpressible_(BufferLength)) SQLPOINTER TargetValue,
	//	//������� �����ϴ� ����
	//	SQLLEN BufferLength,				 //������ ����
	//	_Inout_opt_ SQLLEN * StrLen_or_Ind); //�÷��� ���̳� ���¸� ����
	ret = SQLBindCol(g_hStmt, 1, SQL_C_ULONG, &Price, 0, &lPrice);

	TCHAR sql2[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql2, L"select price from tblCigar where  name='%s'", L"���");
	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql2, SQL_NTS);

	//SQLRETURN  SQL_API SQLFetch(SQLHSTMT StatementHandle);
	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		std::wcout << Price << std::endl;
	}
	SQLCloseCursor(g_hStmt);

	//TCHAR sql3[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	//wsprintf(sql3, L"insert into tblCigar (name,price, korean) values ('%s',%d,%d)",
	//				L"���÷���", 4100, 1);
	//ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql3, SQL_NTS);
	//if (ret != SQL_SUCCESS )
	//{
	//	Check();
	//	return;
	//}	
	//SQLCloseCursor(g_hStmt);

	//TCHAR sql3[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	//wsprintf(sql3, L"delete from tblCigar where name='%s'",
	//	L"xxxxxx");
	//ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql3, SQL_NTS);
	//if (ret != SQL_SUCCESS)
	//{
	//	Check();
	//	return;
	//}
	//SQLCloseCursor(g_hStmt);

	//TCHAR sql4[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	//wsprintf(sql4, L"update tblCigar set name='%s' where name='%s'",
	//	L"�ڷγ�", L"88 Light");
	//ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql4, SQL_NTS);
	//if (ret != SQL_SUCCESS)
	//{
	//	Check();
	//	return;
	//}
	SQLCloseCursor(g_hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
	SQLDisconnect(g_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
}

//#define _CRT_SECURE_NO_WARNINGS
//#include <windows.h>
//#include <iostream>
//#include <tchar.h>
//#include <string>
//#include <sql.h>
//#include <sqlext.h>
//using namespace std;
//
//
//SQLHENV g_hEnv;
////ȯ���ڵ� : ȯ�濡 ����Ǵ� ������ ���� ����, ���� ����, ȯ���� �Ӽ���� ���ῡ ���õ� �������� �ִ�
//
//SQLHDBC g_hDbc;
////�����ڵ� : ������ �ҽ��� ���� �� �����ϴ� ���� ���� �ֵ� ���. ������ �ҽ��� ����̹��� ���� ������ �����ϰų�
////Ʈ����� ó������ ����Ѵ�.
////�Ӽ� : �α��� Ÿ�� �ƿ� ����, ��Ŷ ũ��, �񵿱� �׼��� ���, Ʈ������ ��� ����, SQLSETCONNECTARRT()�Լ����
//
//SQLHSTMT g_hStmt;
////����ڵ� : ������ �ҽ��� ������ �� ���ϴ� �����͸� �׼����ϱ� ���� SQL ����� �����ϸ� �� ����°� SQL���� �Ķ���� ������ ������.
////�Ӽ� : Ŀ���� ����, ���� Ÿ�Ӿƿ���, ������� ���ڵ� �������� �Ӽ��� ���� ������ �� ������, SQLSETSTMTATTR()�Լ� ���
//
//void main()
//{
//	setlocale(LOCALE_ALL, "korean");
//	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv) != SQL_SUCCESS) //ȯ���ڵ� �Ҵ�
//	{
//		return;
//	}
//	SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER); //ȯ���ڵ� ����
//
//	if (SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc) != SQL_SUCCESS) //�����ڵ� �Ҵ�
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
//	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, InCon, _countof(InCon), NULL, 0, &cbOutLen, SQL_DRIVER_NOPROMPT);
//
//	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//	{
//		return;
//	}
//	if (SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt) != SQL_SUCCESS) //����ڵ� �Ҵ�
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
//	ret = SQLBindCol(g_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &IName);
//	ret = SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &IPrice);
//	ret = SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &IKorean);
//
//	//tblCigar�� ��� ������(*)�� ã����
//	TCHAR sql[MAX_PATH] = L"select * from tblCigar";
//
//	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql, SQL_NTS);
//
//	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
//	{
//		wcout << Name << " " << Price << " " << Korean << endl;
//	}
//	SQLCloseCursor(g_hStmt);
//
//	TCHAR sql2[MAX_PATH] = { 0, };
//	//L"select Name, Price, Korean from tblCigar = '%s'";
//	wsprintf(sql2, L"select Name, Price, Korean from tblCigar where name = '%s'", L"���");
//	//Cigar ���̺��� �̸��� ��̿� ���� ������ �ּ���
//	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql2, SQL_NTS);
//
//	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
//	{
//		wcout << Name << " " << Price << " " << Korean;
//	}
//	SQLCloseCursor(g_hStmt);
//
//	TCHAR sql3[MAX_PATH] = { 0, };
//	//L"select Name, Price, Korean from tblCigar = '%s'";
//	wsprintf(sql3, L"insert into tblCigar (name, price, korean) VALUE ('%s', %d, %d)", L"����", 4500, 1);
//	//���̺� �߰�
//	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql3, SQL_NTS);
//	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
//	{
//		wcout << Name << " " << Price << " " << Korean;
//	}
//	SQLCloseCursor(g_hStmt);
//
//	SQLFreeHandle(SQL_HANDLE_STMT, g_hStmt);
//	SQLDisconnect(g_hDbc);
//	SQLFreeHandle(SQL_HANDLE_DBC, g_hDbc);
//	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
//}
//
//
