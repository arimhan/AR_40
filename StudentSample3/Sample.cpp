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
		cout << "= = = = = = = = = = = = = = = = =\t�л� ���� ���� ���α׷�\t      = = = = = = = = = = = = = = =" << endl;
		cout << "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n" << endl;
		cout << "\t-> ���û���(0), ����(1), ����(2), �ҷ�����(3), ���(4), ����(77) :  ";
		scanf_s("%d", &iNum);
		if (iNum == 77) break;

		switch (iNum)
		{
		case Sample:
		{
			manager.Create();
			cout << "\t���� ������ ���� �Ϸ�!\n";
			iNum = 1;
		}break;
		case Save:
		{
			manager.FileSave("Student.txt");
			cout << "\t���� ������ ���� �Ϸ�!\n";
		}break;
		case DeleteAll:
		{
			manager.DeleteAll();
			cout << "\t���� ��� ������ ���� �Ϸ�!\n";
		}break;
		case Load:
		{
			manager.DeleteAll();
			manager.Load("Student.txt");
			cout << "\tTXT ���� �ҷ����� �Ϸ�!\n";
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