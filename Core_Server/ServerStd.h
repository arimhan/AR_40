#pragma once
#include <winSock2.h>
#include <windows.h>
#include <WS2tcpip.h>	//inet_ntop
#include <list>
#include <map>			//callback func »ç¿ë
#include <vector>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")

#ifdef _DEBUG
#pragma comment (lib, "Core_Server_d.lib")
#else
#pragma comment (lib, "Core_Server_r.lib")
#endif // DEBUG
using namespace std;