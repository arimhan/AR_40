#include <iostream>
using namespace std
//팩토리얼 https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=tipsware&logNo=
//이진트리 https://hongku.tistory.com/160
//함수포인터 https://blog.naver.com/tipsware/221286052738

int main()
{
	int iSum = 1;
	int iRet = 0;
	for (int i = 1; i < 5; i++)
	{
		iRet = iSum* i;
	}
	cout << iRet << endl;
	return 0;
}