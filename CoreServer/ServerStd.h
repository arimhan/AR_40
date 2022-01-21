#pragma once
#include <winSock2.h>
#include <windows.h>
#include <WS2tcpip.h>	//inet_ntop
#include <list>
#include <map>			//callback func 사용
#include <functional>	//callback에서 function사용
#include <vector>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")

#ifdef _DEBUG
#pragma comment (lib, "CoreServer_d.lib")
#else
#pragma comment (lib, "CoreServer_r.lib")
#endif // DEBUG
using namespace std;