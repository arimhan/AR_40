#include "StudentManager.h"

void main()
{
	//AStudent* data1 = new AMiddleStudent;
	//*data1 << 1 << 4 << 5.4f;

	//AMiddleStudent* pA = new AMiddleStudent;
	//AHighStudent* pB = new AHighStudent;
	//ACollegeStudent * pC = new ACollegeStudent;
	//AStudent* data[3] = { 0, };
	//data[0] = pA;
	//data[1] = pB;
	//data[2] = pC;

	//for (int i = 0; i < 3; i++)
	//{
	//	data[i]->Show();
	//}
	//for (int i = 0; i < 3; i++)
	//{
	//	delete data[i];
	//}

	AStudentManager manager;
	int iNum = 0;
	while(iNum < 99)
	{
		printf("==============================  Main Menu  ========================\n");
		printf("-> 생성(0), 저장(1), 모두삭제(2), 불러오기(3), 출력(4), 종료(9) :  ");
		scanf_s("%d", &iNum);
		if (iNum == 9) break;

		switch (iNum)
		{
		case 0:
		{
			manager.Create();
			cout << "데이터 생성 완료!\n";
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