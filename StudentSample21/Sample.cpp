#include "StudentManager.h"

int iNum = 0;
void main()
{
	AStudentManager manager;
	int iNum = 0;
	while(iNum < 99)
	{
		printf("==============================  Main Menu  ========================\n");
		printf("-> 생성(0), 저장(1), 모두삭제(2), 불러오기(3), 출력(4), 종료(9) :  ");
		cin >> iNum; // scanf_s("%d", &iNum);
		if (iNum == 99) break;

		switch (iNum)
		{
		case 0:
		{
			manager.Create();
			cout << "데이터 생성 완료!\n";
		}break;
		case 1:
		{
			manager.FileSave();
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
			manager.Load();
			cout << "데이터 로드 완료!\n";
		}break;
		case 4:
		{
			cout << manager;
		}break;
		}
	}
	cout << "mainerror";
}