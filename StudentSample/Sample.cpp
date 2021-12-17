#include "StudentManager.h"


void main()
{

	AStudentManager manager;
	int iNum = 0;
	while(iNum < 99)
	{
		manager.m_List.Init();
		string name = " ";  int Kor = 0; int Eng = 0; int Mat = 0;
		cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n" << endl;
		cout << "\n= = = = = = = = = = = = =\t  학생 성적 관리 프로그램\t= = = = = = = = = = = = =\n" << endl;
		cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n" << endl;
		printf("-> 생성(0), 저장(1), 모두삭제(2), 불러오기(3), 출력(4), 종료(9) :  ");
		scanf_s("%d", &iNum);
		if (iNum == 9) break;

		switch (iNum)
		{
		case 0: //학생 정보 입력
		{
			//string name = " ";  int Kor = 0; int Eng = 0; int Mat = 0;
			cout << "학생 정보를 입력해주세요!\n";
			cout << "이름: ";
			cin >> name;
			cout << "국어: ";
			cin >> Kor;
			cout << "영어: ";
			cin >> Eng;
			cout << "수학: ";
			cin >> Mat;

			AStudent* st = new AStudent(name, Kor, Eng, Mat);
			manager.m_List.AddData(st);
			cout << "입력 데이터 생성 완료!\n";
			int iNum = 1;
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
		case 5: //샘플 생성
		{
			manager.Create();
			cout << "샘플 학생 데이터 생성 완료!\n";
		}break;
		}
	}
	cout << "error : sample main";
}