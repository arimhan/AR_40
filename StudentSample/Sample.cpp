#include "StudentManager.h"

enum Jop { Create, Save, Delete, Load, Draw, Quit,
};


void main()
{

	AStudentManager manager;
	int iNum = 0;
	while(iNum < 99)
	{
		cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n" << endl;
		cout << "\n= = = = = = = = = = = = = = =\t\t�л� ���� ���� ���α׷�\t\t= = = = = = = = = = = = = = =\n" << endl;
		cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n" << endl;
		printf("-> ����(0), ����(1), ��λ���(2), �ҷ�����(3), ���(4), ����(9) :  ");
		scanf_s("%d", &iNum);
		if (iNum == 9) break;

		switch (iNum)
		{
		case 0: //�л� ���� �Է�
		{
			string name = " ";  int Kor = 0; int Eng = 0; int Mat = 0;
			cout << "�л� ������ �Է����ּ���!\n";
			cout << "�̸�: \n";
			cin >> name;
			cout << "����: \n";
			cin >> Kor;
			cout << "����: \n";
			cin >> Eng;
			cout << "����: \n";
			cin >> Mat;

			AStudent* st = new AStudent(name, Kor, Eng, Mat);
			manager.m_List.AddData(st);
			int iNum = 1;
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
		case 5: //���� ����
		{
			manager.Create();
			cout << "���� �л� ������ ���� �Ϸ�!\n";
		}break;
		}
	}
	cout << "error : sample main";
}