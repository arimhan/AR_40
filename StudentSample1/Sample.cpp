#include "StudentManager.h"

//* ~b는 바이너리로 출력

void main()
{
	AStudentManager manager;
	int iNum = 0;
	while (iNum < 99)
	{
		//int iNum = 0;
		printf("\n-> 생성(0), 저장(1), 모두삭제(2), 불러오기(3), 출력(4), 종료(9) :  ");
		//정렬, 검색, 수정 기능 추가 필요

		scanf_s("%d", &iNum);
		if (iNum == 9) break;

		switch (iNum)
		{
		case 0:
		{
			manager.Create();
			cout << "1개 data 생성 완료" << endl;
			iNum = 1;
		}break;
		case 1:
		{
			manager.SaveFile();
			cout << "현재 목록 저장 완료" << endl;
		}break;
		case 2:
		{
			manager.DeleteAll();
			cout << "현재 목록 모두 삭제 완료" << endl;
		}break;
		case 3:
		{
			manager.DeleteAll();
			manager.Load();
			cout << "Student.txt 파일 불러오기 완료" << endl;
		}break;
		case 4:
		{
			cout << manager;
			//manager.Draw();
		}break;
		}
	}
}
