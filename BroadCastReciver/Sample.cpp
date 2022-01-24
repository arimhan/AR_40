#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
using namespace std;

void main()
{
	//Reciver = server
	//ipaddress인 inet_addr = INADDR_ANY (==0값)으로 처리한다.
	//이렇게 해야 BroadCast용 sock에 접속 시 ip주소를 0으로 처리한다. => 모두 접속 가능.
	//Recv할 때에는 bind가 필요하다. 근데 Reciver에서 bind가 1개만 있어야 한다. (2개를 킬 수 없다..)
	//이유는 ip마다 체크하기 때문에 .. port번호가 다르면 가능하나 다른 프로그램으로 인식해서 채팅(통신)이 불가능하다.
	//결론은 UDP는 스스로 테스트 하기 어렵다.
	
}