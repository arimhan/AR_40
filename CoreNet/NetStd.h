#pragma once
#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <list>
#include <iostream>
#pragma comment (lib, "ws2_32.lib")
#ifdef _DEBUG
#pragma comment (lib, "CoreNet_d.lib")
#else
#pragma comment (lib, "CoreNet_r.lib")
#endif // DEBUG

using namespace std;