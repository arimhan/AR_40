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
		cout << "\n= = = = = = = = = = = = =\t  �л� ���� ���� ���α׷�\t= = = = = = = = = = = = =\n" << endl;
		cout << "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n" << endl;
		printf("-> ����(0), ����(1), ��λ���(2), �ҷ�����(3), ���(4), ����(9) :  ");
		scanf_s("%d", &iNum);
		if (iNum == 9) break;

		switch (iNum)
		{
		case 0: //�л� ���� �Է�
		{
			//string name = " ";  int Kor = 0; int Eng = 0; int Mat = 0;
			cout << "�л� ������ �Է����ּ���!\n";
			cout << "�̸�: ";
			cin >> name;
			cout << "����: ";
			cin >> Kor;
			cout << "����: ";
			cin >> Eng;
			cout << "����: ";
			cin >> Mat;

			AStudent* st = new AStudent(name, Kor, Eng, Mat);
			manager.m_List.AddData(st);
			cout << "�Է� ������ ���� �Ϸ�!\n";
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