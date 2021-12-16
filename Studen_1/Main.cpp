//#include <string>
#include "Student.h"

template <class A>
void RunMain()
{
	bool m_bRun = true;
	int iNum = 0;
	ALinkedList<A> manager;

	while (m_bRun)
	{
		cout << "==============================  Main Menu  ========================\n";
		cout << "-> 생성(0), 저장(1), 모두삭제(2), 불러오기(3), 출력(4), 종료(9) :  ";
		string name = " ";  int GA = 0; int GD = 0; int GP = 0;
		cin >> iNum;
		if (iNum > 0, iNum < 10) //범위 강제 지정
		{
			if (iNum == 9) break;
			switch (iNum)
			{
			case 0:
			{
				// 하단 점수 예외처리 한꺼번에 하기 (소수점 입력하면 무한출력 오류발생)
				cout << "학생 이름 :  ";
				cin >> name;

				if (name.length() < 4)//(strcmp(str1, >= 48 && name <= 64)) 아스키코드로 비교확인
				{
					cout << "잘못된 이름입니다.\n\n";
					break;
				}
				
				cout << "게임아키텍쳐: " << " ";
				cin >> GA;
				cout << "게임디자인: " << " ";
				cin >> GD;
				cout << "게임프로그래밍: " << " ";
				cin >> GP;
				AStudent* result = new AStudent(name, GA, GD, GP);

				manager.AddData(result);
				cout << "입력하신 데이터를 저장하였습니다!\n\n";
				iNum = 1;
			}break;
			case 1:
			{
				//manager.FileSave("Student.txt");
				cout << "데이터 저장 완료!\n";
			}break;
			case 2:
			{
				//manager.DeleteAll();
				cout << "데이터 삭제 완료!\n";
			}break;
			case 3:
			{
				//manager.DeleteAll();
				//manager.Load("Student.txt");
				cout << "데이터 로드 완료!\n";
			}break;
			case 4:
			{
				cout << "test";
				//cout << manager;
			}break;
			}
		}
		cout << "error : sample main";
	}
}

int main()
{
	RunMain();
}

