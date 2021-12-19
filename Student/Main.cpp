#include "Student.h"

void main()
{
	AStudent manager;
	int iNum = 0;
	while (iNum < 99)
	{
		//int iNum = 0;
		printf("\n-> Create(0), Save(1), DeleteAll(2), Load(3), Draw(4), Exit(9) :  ");
		//정렬, 검색, 수정 기능 추가 필요

		scanf_s("%d", &iNum);
		if (iNum == 9) break;

		switch (iNum)
		{
		case 0:
		{
			manager.Create();
			iNum = 1;
		}break;
		case 1:
		{	
			manager.SaveFile();
		}break;
		case 2:
		{
			manager.DeleteAll();
		}break;
		case 3:
		{
			manager.DeleteAll();
			manager.Load();
		}break;
		case 4:
		{
			manager.Draw();
		}break;
		}
	}
	printf("error1"); //그럴 일은 없지만
}