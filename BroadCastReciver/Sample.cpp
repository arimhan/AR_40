#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
using namespace std;

void main()
{
	//Reciver = server
	//ipaddress�� inet_addr = INADDR_ANY (==0��)���� ó���Ѵ�.
	//�̷��� �ؾ� BroadCast�� sock�� ���� �� ip�ּҸ� 0���� ó���Ѵ�. => ��� ���� ����.
	//Recv�� ������ bind�� �ʿ��ϴ�. �ٵ� Reciver���� bind�� 1���� �־�� �Ѵ�. (2���� ų �� ����..)
	//������ ip���� üũ�ϱ� ������ .. port��ȣ�� �ٸ��� �����ϳ� �ٸ� ���α׷����� �ν��ؼ� ä��(���)�� �Ұ����ϴ�.
	//����� UDP�� ������ �׽�Ʈ �ϱ� ��ƴ�.
	
}