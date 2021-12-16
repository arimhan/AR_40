#include "StudentManager.h"

void main()
{
	AStudentManager manager;
	bool m_bRun = true;
	int iNum = 0;

	while(m_bRun)
	{
		cout << "==============================  Main Menu  ========================\n";
		cout << "-> 생성(0), 저장(1), 모두삭제(2), 불러오기(3), 출력(4), 종료(9) :  ";
		string name = " ";  int GA = 0; int GD = 0; int GP = 0;
		cin >> iNum;

		if (iNum == 9) break;
		switch (iNum)
		{
		case 0:
		{
			cout << "학생 이름 :  ";
			cin >> name;
			cout << "게임아키텍쳐: " << " ";
			cin >> GA;
			cout << "게임디자인: " << " ";
			cin >> GD;
			cout << "게임프로그래밍: " << " ";
			cin >> GP;
			AStudent* result = new AStudent(name, GA, GD, GP);

			//manager.Create();
			cout << "입력하신 데이터를 저장하였습니다!\n\n";
			
			iNum = 1;
		}break;
		case 1:
		{
			manager.FileSave("Student.txt");
			cout << "데이터 저장 완료!\n";
		}break;
		case 2:
		{
			manager.DeleteAll();
			cout << "데이터 삭제 완료!\n";
		}break;
		case 3:
		{
			manager.DeleteAll();
			manager.Load("Student.txt");
			cout << "데이터 로드 완료!\n";
		}break;
		case 4:
		{
			cout << manager;
		}break;
		}
	}
	cout << "error : sample main";
}
