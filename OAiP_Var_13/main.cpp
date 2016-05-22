#include "stdafx.h"
#include "main.h"
#include "Methods.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		//CreateTestFile();
		ShowMenu();
		char choice = getchar();
		switch (choice)
		{
			case '1':
				OpenFile();
				break;
			case '2':
				Add();
				break;
			case '3':
				Print();
				break;
			case '4':
				SaveFile();
				break;
			case '5':
				Edit();
				break;
			case '6':
				Sort();
				break;
			case '7':
				RemoveRange();
				break;
			case '8':
				Exit();
				break;
			default:
				break;
		}
	}
    return 0;
}