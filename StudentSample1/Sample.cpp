#include "StudentManager.h"

//* ~b�� ���̳ʸ��� ���

void main()
{
	AStudentManager manager;
	int iNum = 0;
	while (iNum < 99)
	{
		//int iNum = 0;
		printf("\n-> ����(0), ����(1), ��λ���(2), �ҷ�����(3), ���(4), ����(9) :  ");
		//����, �˻�, ���� ��� �߰� �ʿ�

		scanf_s("%d", &iNum);
		if (iNum == 9) break;

		switch (iNum)
		{
		case 0:
		{
			manager.Create();
			cout << "1�� data ���� �Ϸ�" << endl;
			iNum = 1;
		}break;
		case 1:
		{
			manager.SaveFile();
			cout << "���� ��� ���� �Ϸ�" << endl;
		}break;
		case 2:
		{
			manager.DeleteAll();
			cout << "���� ��� ��� ���� �Ϸ�" << endl;
		}break;
		case 3:
		{
			manager.DeleteAll();
			manager.Load();
			cout << "Student.txt ���� �ҷ����� �Ϸ�" << endl;
		}break;
		case 4:
		{
			cout << manager;
			//manager.Draw();
		}break;
		}
	}
}
