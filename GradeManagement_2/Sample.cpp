#include "StudentManager.h"

void main()
{
	AStudentManager manager;
	bool m_bRun = true;
	int iNum = 0;

	while(m_bRun)
	{
		cout << "==============================  Main Menu  ========================\n";
		cout << "-> ����(0), ����(1), ��λ���(2), �ҷ�����(3), ���(4), ����(9) :  ";
		string name = " ";  int GA = 0; int GD = 0; int GP = 0;
		cin >> iNum;

		if (iNum == 9) break;
		switch (iNum)
		{
		case 0:
		{
			cout << "�л� �̸� :  ";
			cin >> name;
			cout << "���Ӿ�Ű����: " << " ";
			cin >> GA;
			cout << "���ӵ�����: " << " ";
			cin >> GD;
			cout << "�������α׷���: " << " ";
			cin >> GP;
			AStudent* result = new AStudent(name, GA, GD, GP);

			//manager.Create();
			cout << "�Է��Ͻ� �����͸� �����Ͽ����ϴ�!\n\n";
			
			iNum = 1;
		}break;
		case 1:
		{
			manager.FileSave("Student.txt");
			cout << "������ ���� �Ϸ�!\n";
		}break;
		case 2:
		{
			manager.DeleteAll();
			cout << "������ ���� �Ϸ�!\n";
		}break;
		case 3:
		{
			manager.DeleteAll();
			manager.Load("Student.txt");
			cout << "������ �ε� �Ϸ�!\n";
		}break;
		case 4:
		{
			cout << manager;
		}break;
		}
	}
	cout << "error : sample main";
}
