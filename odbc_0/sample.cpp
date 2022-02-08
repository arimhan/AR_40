#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <sql.h>
#include <sqlext.h>


SQLHENV		g_hEnv;			//환경핸들
SQLHDBC		g_hDbc;			//연결핸들
SQLHSTMT	g_hStmt;		//명령핸들
//SQLHDESC	g_hDesc;		//설명자 핸들

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

	// 결과
	ret = SQLBindCol(g_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &lName);
	ret = SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &lPrice);
	ret = SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &lKorean);

	TCHAR sql[MAX_PATH] = L"select * from tblCigar";


	//SQLRETURN SQL_API SQLExecDirectW
	//(
	//	SQLHSTMT    hstmt,				//연결 핸들
	//	_In_reads_opt_(TextLength) SQLWCHAR * szSqlStr, //실행한 SQL문
	//	SQLINTEGER  TextLength			//SQL문의 문자열 길이
	//);
	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql, SQL_NTS);

	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		std::wcout << Name << " " << Price << " " << Korean << std::endl;
	}
	SQLCloseCursor(g_hStmt);

	//SQLRETURN  SQL_API SQLBindCol(
	//	SQLHSTMT StatementHandle,            //명령 핸들
	//	SQLUSMALLINT ColumnNumber,			 //바인딩 될 컬럼의 번호
	//	SQLSMALLINT TargetType,				 //데이터 타입
	//	_Inout_updates_opt_(_Inexpressible_(BufferLength)) SQLPOINTER TargetValue,
	//	//결과값을 저장하는 버퍼
	//	SQLLEN BufferLength,				 //버퍼의 길이
	//	_Inout_opt_ SQLLEN * StrLen_or_Ind); //컬럼의 길이나 상태를 리턴
	ret = SQLBindCol(g_hStmt, 1, SQL_C_ULONG, &Price, 0, &lPrice);

	TCHAR sql2[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	wsprintf(sql2, L"select price from tblCigar where  name='%s'", L"장미");
	ret = SQLExecDirect(g_hStmt, (SQLTCHAR*)&sql2, SQL_NTS);

	//SQLRETURN  SQL_API SQLFetch(SQLHSTMT StatementHandle);
	while (SQLFetch(g_hStmt) != SQL_NO_DATA)
	{
		std::wcout << Price << std::endl;
	}
	SQLCloseCursor(g_hStmt);

	//TCHAR sql3[MAX_PATH] = { 0, };// L"select name,price,korean from tblCigar='%s'";
	//wsprintf(sql3, L"insert into tblCigar (name,price, korean) values ('%s',%d,%d)",
	//				L"디스플러스", 4100, 1);
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
	//	L"코로나", L"88 Light");
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
////환경핸들 : 환경에 저장되는 정보는 현재 상태, 진단 정보, 환경의 속성등과 연결에 관련된 정보들이 있다
//
//SQLHDBC g_hDbc;
////연결핸들 : 데이터 소스에 연결 및 해제하는 것이 가장 주된 기능. 데이터 소스나 드라이버에 관한 정보를 조사하거나
////트랜잭션 처리에도 사용한다.
////속성 : 로그인 타임 아웃 설정, 패킷 크기, 비동기 액세스 모드, 트랙젝션 모드 지정, SQLSETCONNECTARRT()함수사용
//
//SQLHSTMT g_hStmt;
////명령핸들 : 데이터 소스에 연결한 후 원하는 데이터를 액세스하기 위한 SQL 명령을 저장하며 그 결과셋과 SQL문의 파라미터 정보를 가진다.
////속성 : 커서의 종류, 쿼리 타임아웃값, 결과셋의 레코드 갯수등의 속성을 갖고 지정할 수 있으며, SQLSETSTMTATTR()함수 사용
//
//void main()
//{
//	setlocale(LOCALE_ALL, "korean");
//	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_hEnv) != SQL_SUCCESS) //환경핸들 할당
//	{
//		return;
//	}
//	SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3_80, SQL_IS_INTEGER); //환경핸들 설정
//
//	if (SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc) != SQL_SUCCESS) //연결핸들 할당
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
//	//연결 핸들을 할당하면 실제 데이터 소스와 연결할 수 있다
//
//	SQLRETURN ret = SQLDriverConnect(g_hDbc, NULL, InCon, _countof(InCon), NULL, 0, &cbOutLen, SQL_DRIVER_NOPROMPT);
//
//	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
//	{
//		return;
//	}
//	if (SQLAllocHandle(SQL_HANDLE_STMT, g_hDbc, &g_hStmt) != SQL_SUCCESS) //명령핸들 할당
//	{
//		return;
//	}
//	SQLLEN IName, IPrice, IKorean;
//	TCHAR Name[21];
//
//	int Price;
//	BOOL Korean;
//	//결과
//
//	//첫번째 필드로 각각의 레코드들을 리턴해줌
//	ret = SQLBindCol(g_hStmt, 1, SQL_UNICODE, Name, sizeof(Name), &IName);
//	ret = SQLBindCol(g_hStmt, 2, SQL_C_ULONG, &Price, 0, &IPrice);
//	ret = SQLBindCol(g_hStmt, 3, SQL_C_ULONG, &Korean, 0, &IKorean);
//
//	//tblCigar에 모든 데이터(*)를 찾아줘
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
//	wsprintf(sql2, L"select Name, Price, Korean from tblCigar where name = '%s'", L"장미");
//	//Cigar 테이블에서 이름이 장미에 대한 정보를 주세요
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
//	wsprintf(sql3, L"insert into tblCigar (name, price, korean) VALUE ('%s', %d, %d)", L"레종", 4500, 1);
//	//테이블에 추가
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
