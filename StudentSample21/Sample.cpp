#include "StudentManager.h"


void main()
{
	AStudentManager manager;
	int iNum = 0;
	while(iNum < 99)
	{
		int iNum = 0;
		printf("==============================  Main Menu  ========================\n");
		printf("-> ����(0), ����(1), ��λ���(2), �ҷ�����(3), ���(4), ����(9) :  ");
		scanf_s("%d", &iNum); //cin >> iNum; 
		if (iNum == 9) break;

		switch (iNum)
		{
			case 0:
			{
				manager.Create();
				cout << "������ ���� �Ϸ�!\n";
			}break;
			case 1:
			{
				manager.FileSave();
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
				manager.Load();
				cout << "������ �ε� �Ϸ�!\n";
			}break;
			case 4:
			{
				std::cout << manager;
			}break;
		}
	}
	cout << "mainerror";
}