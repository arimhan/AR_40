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
	//cout << "������ ������ �õ��մϴ�...��ȭ���ڰ� �߸� ���� : 127.0.0.1" << endl;
	//cout << "ID : sa, PW : rksk!312 �Է� �� KGCAGAME�� ������ �������ּ���!" << endl;
	cout << "������ ������ �õ��մϴ�..������ �� �� ��� DB���� �� SQL�� DB�� ������ּ���." << endl;

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
			//���� ������� ������. DB��� �� ������Ʈ ���� �� dsn������ Ȯ���Ͽ� ����ó��
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

bool AODBC::ExecTableInfo(const TCHAR* szTableName)
{
	ATableInfo info;
	info.szTableName = szTableName;
	wstring sql = L"select * from ";
	sql += szTableName;
	SQLRETURN ret = SQLExecDirect(m_hStmt, (SQLTCHAR*)sql.c_str(), SQL_NTS);
	
	if (ret != SQL_SUCCESS )
	{
		Check();
		return false;
	}

	SQLSMALLINT iNumCols;
	SQLNumResultCols(m_hStmt, &info.iNumcol);
	for (int iCols = 1; iCols <= info.iNumcol; iCols++)
	{
		AColInfo col;
		col.iCol = iCols;
		int iSize = _countof(col.szColName);
		SQLDescribeCol(m_hStmt, iCols, col.szColName, iSize, &col.NameLenPtr, &col.pfSqlType, &col.ColSizePtr, &col.DecimalDigitsPtr, &col.pfNullable);
		info.ColList.push_back(col);
	}

	SQLLEN iTemp;
	TCHAR szData[100][21] = { 0, };
	int iData[100];
	ARecord rData;

	for (int iBind = 0; iBind < info.ColList.size(); iBind++)
	{
		switch (info.ColList[iBind].pfSqlType)
		{
		case SQL_TYPE_TIMESTAMP:
		{
			AField data;
			data.iDataType = SQL_UNICODE;
			ret = SQLBindCol(m_hStmt, iBind + 1,
				SQL_TYPE_TIMESTAMP,
				&szData[iBind],
				0,
				&iTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case SQL_WCHAR:
		case SQL_WVARCHAR: {
			AField data;
			data.iDataType = SQL_UNICODE;
			ret = SQLBindCol(m_hStmt, iBind + 1,
				SQL_UNICODE,
				szData[iBind],
				sizeof(szData[iBind]),
				&iTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case SQL_INTEGER: {
			AField data;
			data.iDataType = SQL_INTEGER;
			ret = SQLBindCol(m_hStmt, iBind + 1,
				SQL_INTEGER,
				&iData[iBind],
				0,
				&iTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		}break;
		case -7: {
			AField data;
			data.iDataType = SQL_C_ULONG;
			ret = SQLBindCol(m_hStmt, iBind + 1,
				SQL_C_ULONG,
				&iData[iBind],
				0,
				&iTemp);
			if (ret != SQL_SUCCESS)
			{
				Check();
				return false;
			}
			rData.record.push_back(data);
		};
		}
	}


	while (SQLFetch(m_hStmt) != SQL_NO_DATA)
	{
		for (int iCol = 0; iCol < info.ColList.size(); iCol++)
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
		m_StringData.push_back(rData);
		wcout << L"ID: " << rData.record[1].szData << L"  ";
		wcout << L"PW: " << rData.record[2].szData << endl << endl;
	}
	SQLCloseCursor(m_hStmt);
	m_TableList.push_back(info);

	return true;

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
	SQLWCHAR	ID[10] = { 0, };
	SQLWCHAR	PW[10] = { 0, };
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
void AODBC::ExecuteDeletePrepare()
{
	SQLRETURN	ret;
	SQLWCHAR	ID[10] = { 0, };
	wcout << L"���� ID: ";
	wcin >> ID;
	memcpy(id, ID, sizeof(id));

	ret = SQLExecute(m_stmtAccountDel);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return;
	}
	while (SQLMoreResults(m_stmtAccountDel) != SQL_NO_DATA);
	SQLFreeStmt(m_stmtAccountDel, SQL_CLOSE);
	SQLCloseCursor(m_stmtAccountDel);
}
void AODBC::UpdateProcedure()
{
	SQLRETURN ret;
	ret = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_stmtUpdate);
	SWORD sReturn = 0;
	SQLLEN cbRetParam = SQL_NTS;

	ret = SQLBindParameter(m_stmtUpdate, 1, SQL_PARAM_OUTPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &sReturn, 0, &cbRetParam);
	ret = SQLBindParameter(m_stmtUpdate, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(id), 0, id, sizeof(id), NULL);
	ret = SQLBindParameter(m_stmtUpdate, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, sizeof(pw), 0, pw, sizeof(pw), NULL);

	TCHAR callupdate[] = L"{? = call UpdateUser(?,?)}";
	ret = SQLPrepare(m_stmtUpdate, callupdate, SQL_NTS);
}
void AODBC::ExecuteUpDatePrepare()
{
	SQLRETURN ret;
	SQLWCHAR ID[10] = { 0, };
	SQLWCHAR UpdatePW[10] = { 0, };
	wcout << L"��й�ȣ�� �����մϴ�." << endl;
	wcout << L"��й�ȣ ������ ID: ";
	wcin >> ID;
	wcout << L"������ ��й�ȣ : ";
	wcin >> UpdatePW;
	memcpy(id, ID, sizeof(id));
	memcpy(pw, UpdatePW, sizeof(pw));

	ret = SQLExecute(m_stmtUpdate);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
	{
		Check();
		return;
	}
	while (SQLMoreResults(m_stmtUpdate) != SQL_NO_DATA);
	SQLFreeStmt(m_stmtUpdate, SQL_CLOSE);
	SQLCloseCursor(m_stmtUpdate);

}

void AODBC::Release()
{
	SQLCloseCursor(m_hStmt);
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
	SQLDisconnect(m_hDbc);
}