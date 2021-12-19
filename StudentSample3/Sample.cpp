#include "StudentManager.h"
#include "windows.h"
enum menu { Sample =0, Save, DeleteAll, Load, Draw,};

void main()
{

	AStudentManager manager;
	int iNum = 0;
	while(iNum < 77)
	{
		Sleep(1000);
		system("cls");

		cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =" << endl;
		cout << "= = = = = = = = = = = = = = = = =\t학생 성적 관리 프로그램\t      = = = = = = = = = = = = = = =" << endl;
		cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n" << endl;
		cout << "\t-> 샘플생성(0), 저장(1), 삭제(2), 불러오기(3), 출력(4), 종료(77) :  ";
		scanf_s("%d", &iNum);
		if (iNum == 77) break;

		switch (iNum)
		{
		case Sample:
		{
			manager.Create();
			cout << "\t샘플 데이터 생성 완료!\n";
			iNum = 1;
		}break;
		case Save:
		{
			manager.FileSave("Student.txt");
			cout << "\t현재 데이터 저장 완료!\n";
		}break;
		case DeleteAll:
		{
			manager.DeleteAll();
			cout << "\t현재 모든 데이터 삭제 완료!\n";
		}break;
		case Load:
		{
			manager.DeleteAll();
			manager.Load("Student.txt");
			cout << "\tTXT 파일 불러오기 완료!\n";
		}break;
		case Draw:
		{
			cout << manager << "\n\n";
			system("pause");
		}break;
		}
	}
	cout << "error : sample main";
}