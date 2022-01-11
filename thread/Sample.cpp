#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <conio.h> //_kbhit();
#include "Packet.h"
#pragma comment (lib, "ws2_32.lib")


#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101 "127.0.0.1"

HANDLE				g_hConnectEvent;
HANDLE				g_hExecuteSemaphore;



int SendMsg(SOCKET Csock, char* msg, WORD type)
{
	// 1. 패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE; //규칙을 정해서 동일하게 처리해야함.
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg)); //txt 메모리 카피 처리
	char* pMsg = (char*)&packet;
	//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.

	int iSendSize = 0;
	do {
		// 2. 패킷 전송 : 운영체제는 sendbuffer(short byte), recvbuffer 내 크기가 정해져 있음.
		int iSendByte = send(Csock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int SendPacket(SOCKET Csock, char* msg, WORD type)
{
	// 1. 패킷 생성
	APacket aPacket(type);
	aPacket << 12 << "Arim" << (short)50 << msg;
	APacket aPacketTest(aPacket);
	AChatMsg recvdata;
	ZeroMemory(&recvdata, sizeof(recvdata));
	aPacketTest >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
	char* pData = (char*)&aPacket.m_uPacket;
	int iSendSize = 0;
	do {
		// 2. 패킷 전송 : 운영체제는 sendbuffer(short byte), recvbuffer 내 크기가 정해져 있음.
		int iSendByte = send(Csock, &pData[iSendSize], aPacket.m_uPacket.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) { return -1; }
		}
		iSendSize += iSendByte;
		//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.
	} while (iSendSize < aPacket.m_uPacket.ph.len);
	return iSendSize;
}
int RecvPacketHeader(SOCKET Csock, UPACKET& recvPacket)
{
	// 패킷 헤더 받음
	char szRecvBuffer[256] = { 0, };
	ZeroMemory(&recvPacket, sizeof(recvPacket));
	bool bRun = true;
	int iRecvSize = 0;
	do {
		int iRecvByte = recv(Csock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
		iRecvSize += iRecvByte;
		//위 문장으로 인해 실행부터 -1값 발생
		if (iRecvByte == 0)
		{
			closesocket(Csock);
			cout << "서버가 종료되었습니다." << endl; //서버 종료 시 처리
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR) // -1일때
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK) //Soket 에러가 nonblock상태가 아닐 경우 == 진짜 오류일 경우
			{
				//서버 종료 시 무한 루프로 출력됨. 10054
				cout << "비정상 서버 종료 Error " << iError << endl;
				return -1;
			}
			else { return 0; }
		}
	} while (iRecvSize < PACKET_HEADER_SIZE);
	memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
	return 1;
}
int RecvPacketData(SOCKET Csock, UPACKET& recvPacket)
{
	//데이터 받음
	int iRecvSize = 0;
	do {
		int iRecvByte = recv(Csock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
		iRecvSize += iRecvByte;
		if (iRecvByte == 0)
		{
			closesocket(Csock);
			cout << "서버가 종료되었습니다." << endl; //서버 종료 시 처리
			return -1;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK)
			{
				cout << "비정상 서버 종료" << endl;
				return -1;
			}
			else { return 0; }
		}
	} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
	return 1;
}
DWORD WINAPI SendThread(LPVOID lpThreadParameter) // sendthread 처리 후 반환. 1개체 1스레드 반환받음
{
	SOCKET Csock = (SOCKET)lpThreadParameter; //파라미터를 소켓으로 형변환
	char szBuffer[256] = { 0, };

	while (1)
	{
		DWORD dwRet = WaitForSingleObject(g_hConnectEvent, INFINITE);
		if (dwRet != WAIT_OBJECT_0) { break; }
		ZeroMemory(szBuffer, sizeof(char) * 256);
		fgets(szBuffer, 256, stdin); // 엔터 쳐야 반환함수

		if (strlen(szBuffer) == 0) //msg를 입력하지 않고 엔터만 친 경우 종료처리 한다.
		{
			cout << "\n정상 종료" << endl;
			break;
		}
		int iSendByte = SendPacket(Csock, szBuffer, PACKET_CHAT_MSG);
		if (iSendByte < 0)
		{
			cout << "비정상 서버 종료" << endl;
			break;
		}
	}
	return 0;
}
DWORD WINAPI RecvThread(LPVOID param) // sendthread 처리 후 반환. 1개체 1스레드 반환받음
{
	SOCKET Csock = (SOCKET)param; //파라미터를 소켓으로 형변환
	bool bRun = false;

	while (1)
	{
		//DWORD dwRet = WaitForSingleObject(g_hConnectEvent, 0);//INFINITE); 해당 함수가 호출될때까지 대기
		//if (dwRet == WAIT_TIMEOUT)
		//{
		//	break;
		//}
		DWORD dwRet = WaitForSingleObject(g_hConnectEvent, INFINITE);
		if (dwRet != WAIT_OBJECT_0) { break; }

		UPACKET packet;
		int iRet = RecvPacketHeader(Csock, packet);
		if (iRet < 0) continue;
		if (iRet == 1)
		{
			int iRet = RecvPacketData(Csock, packet);
			if (iRet < 0) break;
			if (iRet == 0) continue;

			APacket data;
			data.m_uPacket = packet;
			AChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(recvdata));
			data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
			cout << "\n" << "[" << recvdata.name<<"]" << recvdata.message;
		}
	}
	return 0;
}


void main()
{
	g_hConnectEvent = CreateEvent(NULL, TRUE, FALSE, NULL); //맨 마지막 L"Connet" 

	//동일 이름의 Event를 2개 이상 만들려고 하면 기본적으로 1개만 생성이 가능하기 때문에 오류가 발생함.
	//이벤트 이름 부여 시 작동함 (아래)
	//if (GetLastError() == ERROR_ALREADY_EXISTS)
	//{
	//	CloseHandle(g_hExecuteSemaphore);
	//	MessageBoxA(NULL, "인스턴트 중복실행중입니다", "경고", MB_OK);
	//	return;
	//}

	//Semaphore 는 동시에 여러개 생성 가능. 그러므로 이름을 넣어 count함.
	g_hExecuteSemaphore = CreateSemaphore(NULL, 3, 3, L"Execute");// NULL);

	if(WaitForSingleObject(g_hExecuteSemaphore, 0) == WAIT_TIMEOUT)
	{
		CloseHandle(g_hExecuteSemaphore);
		MessageBoxA(NULL, "3개까지만 실행 가능해요!", "경고", MB_OK);
		return;
	}
	//CreateSemaphoreW(
	//	_In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
	//	_In_ LONG lInitialCount,
	//	_In_ LONG lMaximumCount, //최대 갯수 카운팅
	//	_In_opt_ LPCWSTR lpName
	//);



	//CreateEventW(
	//	_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
	//	_In_ BOOL bManualReset, // => FALSE 자동 , TRUE 수동리셋
	//	_In_ BOOL bInitialState,
	//	_In_opt_ LPCWSTR lpName
	//);

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return; }
	SOCKET Csock = socket(AF_INET, SOCK_STREAM, 0);

	// 스레드 생성
	//  1) window api
	// ::바깥에 있는 함수 쓰겠다. 범위 해결자.
	DWORD ThreadId;
	HANDLE hThread = ::CreateThread( // 반환값이 핸들임
		0,
		0,
		SendThread, //반환 => 필수적으로 넘겨줄 값? 소켓
		(LPVOID)Csock, //data type (LPVOID)로 맞춰주기
		0, //서스펜디드. 일을 언제 시킬지? => 만들고 아직 진행하지 마~ 등을 세팅함.
		&ThreadId);  //스레드 아이디. 리턴을 시켜주겠다.

	DWORD ThreadIdRecv;
	HANDLE hThreadRecv = ::CreateThread( // 반환값이 핸들임
		0,
		0,
		RecvThread,
		(LPVOID)Csock,
		0,
		&ThreadIdRecv);

	Sleep(1000);

	SOCKADDR_IN CAddr;
	ZeroMemory(&CAddr, sizeof(CAddr));
	CAddr.sin_family = AF_INET;
	CAddr.sin_port = htons(PORT_NUM); // 서버 포트 번호
	CAddr.sin_addr.s_addr = inet_addr(ADRESS_NUM);
	int iRet = connect(Csock, (sockaddr*)&CAddr, sizeof(CAddr));
	if (iRet == SOCKET_ERROR) { return; }
	cout << "서버 접속 성공!" << endl;

	SetEvent(g_hConnectEvent); //Sedn , Recv 둘 중 누가 받는지 => 자동 리셋

	u_long on = 1;
	ioctlsocket(Csock, FIONBIO, &on);


	while (1)
	{
		Sleep(5);
		// return -1값일 경우 무한루프 발생
	}
	cout << "접속 종료" << endl;

	CloseHandle(hThread);
	closesocket(Csock);
	WSACleanup();

	CloseHandle(g_hConnectEvent);
	//_getch();
}