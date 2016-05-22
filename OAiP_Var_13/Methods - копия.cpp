#include "stdafx.h"
#include "Methods.h"
#include "Route.h"
#define BUFFER_SIZE 256

FILE * file; //��������� �� ����.
struct Route *routeArray;	//��������� �� ������ �������.
unsigned int recordCount = 0;	//���������� �������.
char path[BUFFER_SIZE];	//���� � �����.
bool isLoaded = false;	//�������� �� ����.
bool isFileEdited = false; //�������������� �� ����.
const short tableWidth = 73; //������ �������.

void ShowMenu()
{
	system("cls");
	puts("��������� ���������\n");
	puts("1. ��������� ����");
	puts("2. �������� ������ � �����");
	puts("3. �������� ���� �������");
	puts("4. ��������� ����");
	puts("5. ������������� ��������� ������");
	puts("6. ���������� ������� �� ��������� ����");
	puts("7. �������� ���������, ������� �� ����������");
	puts("8. �����");
}

int GetRowsCount(FILE *file)
{
	int count = 0;
	char ch;
	while (!feof(file))
	{
		ch = fgetc(file);
		if (ch == '\n')
		{
			count++;
		}
	}
	rewind(file);
	return count;
}

void OpenFile()
{
	puts("���� � �����:");
	scanf("%s", &path);
	
	if (file = fopen(path, "r"))
	{
		//������� ���������� ����� � ����
		recordCount = GetRowsCount(file);
		//�������������� ������ ��������
		routeArray = new Route[recordCount];
		printf("���� '%s' ��������! ���������� �������: %u.\n", path, recordCount);
		isLoaded = true;

		//������ ������ ����� � ���������
		char fcontent[BUFFER_SIZE];
		char* line;
		int i = 0;
		while (fgets(fcontent, BUFFER_SIZE, file))
		{
			line = strdup(fcontent);
			routeArray[i] = ParseRoute(line);
			free(line);
			i++;
		}
		Print();
	}
	else
	{
		printf("�� ������� ��������� ���� '%s'.\n", path);
		getch();
		isLoaded = false;
	}
}

Route ParseRoute(char *line)
{
	Route route;
	const char* tok;

	tok = strtok(line, ";");
	strcpy(route.Number, tok);
	
	tok = strtok(NULL, ";\n");
	route.CarsCount = atoi(tok);

	tok = strtok(NULL, ";\n");
	route.RouteLength = atof(tok);

	return route;
}

void Print()
{
	if (!isFileLoaded()) return;
	PrintHeader();
	for (int i = 0; i < recordCount; i++)
	{
		printf("|%s\t\t\t", routeArray[i].Number);
		printf("|%u\t\t\t", routeArray[i].CarsCount);
		printf("|%f\t\t|\n", routeArray[i].RouteLength);
		PrintLine();
	}
	getch();
}

void PrintHeader()
{
	PrintLine();
	printf("|����� ��������\t\t|������ ����������\t|����� ��������(��)\t|\n");
	PrintLine();
}

void PrintLine()
{
	short i = tableWidth;
	while (i--)
		printf("-");
	printf("\n");
}

bool isFileLoaded()
{
	if (!isLoaded)
	{
		puts("���� �� ��������.");
		getch();
		return false;
	}
	if (routeArray == NULL)
	{
		puts("������ ������� ����.");
		getch();
		return false;
	}
	else
	{
		return true;
	}
}


void addRecord(Route *route)
{
	//������� ������ ���������� �� ������ �������� ������ �������� 1
	struct Route *temp = new Route[recordCount+1];
	//�������� � ���� ���������� �������� �������
	memcpy(temp, routeArray, (recordCount) * sizeof(Route));
	//�������� ����� ������ � �����
	memcpy(&temp[recordCount], route, sizeof(Route));
	//����������� ������ �������� �������
	free(routeArray);
	//������������� �������� ������� ��������� �� �����
	routeArray = temp;
	//����������� ������� ����� ������� �� 1 
	recordCount++;
	//�������� ��� ������ �������
	isFileEdited = true;
	printf("������ ���������! ���������� �������: %u\n", recordCount);
	Print();
}

void fflushstdin()
{
	int c;
	while ((c = fgetc(stdin)) != EOF && c != '\n');
}

int EnterCarsCount()
{
	printf("������ ����������: ");
	unsigned int carsCount;
	fflushstdin();
	if (scanf("%d", &carsCount) != 1)
	{
		puts("������ ������� ������� ������.");
		return EnterCarsCount();
	}
	else
	{
		return carsCount;
	}
}

float EnterRouteLength()
{
	printf("����� ��������(��): ");
	float routeLength = 0.0;
	fflushstdin();
	if (scanf("%f", &routeLength) != 1)
	{
		puts("������ ������� ������� ������.");
		return EnterRouteLength();
	}
	else
	{
		return routeLength;
	}
}

char* EnterNumber()
{
	char Number[BUFFER_SIZE];
	printf("����� ��������: ");
	scanf("%10s", &Number);
	return Number;
}

void Add()
{
	if (!isFileLoaded()) return;
	system("cls");
	puts("���������� ������.\n");
	Route route;
	strcpy(route.Number, EnterNumber());
	route.CarsCount = EnterCarsCount();
	route.RouteLength = EnterRouteLength();
	addRecord(&route);
}

void Edit()
{
	if (!isFileLoaded()) return;
	system("cls");
	puts("�������������� ������.\n");
	printf("������� ������ ������ (�� 0 �� %u): ", recordCount - 1);
	unsigned int index = 0;
	scanf("%u", &index);
	if (index > recordCount - 1)
	{
		puts("������! ��������� ������ ��������� �� ��������� �������.");
		getch();
		return;
	}
	puts("�������� ���� ��� ��������������:");
	puts(" 1. ����� ��������");
	puts(" 2. ������ ����������");
	puts(" 3. ����� ��������");
	char field = getch();
	switch (field)
	{
		case '1':
			EditNumber(index);
			break;
		case '2':
			EditCarsCount(index);
			break;
		case '3':
			EditRouteLength(index);
			break;
		default:
			break;
	}
}

void Sort()
{
	if (!isFileLoaded()) return;
	system("cls");
	puts("���������� ������� �� ��������� ����.\n");
	puts("�������� ����, �� �������� ���� ������������� ������:");
	puts(" 1. ���������� ������ ���������� �� �������");
	puts(" 2. ����� ��������");
	char field = getch();
	switch (field)
	{
		case '1':
			SortByCarsCount();
			break;
		case '2':
			SortByRouteLength();
			break;
		default:
			break;
	}
}

void RemoveRange()
{
	if (!isFileLoaded()) return;
	system("cls");
	puts("�������� ������� ������� �� ���������.\n");
	printf("������ ������ (�� 0 �� %u): ", recordCount - 1);
	unsigned int index = 0;
	scanf("%u", &index);
	if (index > recordCount - 1)
	{
		puts("������! ��������� ������ ��������� �� ��������� �������.");
		getch();
		return;
	}
	printf("��������! ����� ������� ��� ������ ������� � %u-�. ����������? y/n\n", index);
	char choise = getch();
	switch (choise)
	{
		case 'y':
		{
			//������� ������� ������� ����� ��������
			recordCount = recordCount - (recordCount - index);
			//������� ������ � ����� ����������� �������
			struct Route *temp = new Route[recordCount];
			memcpy(temp, routeArray, recordCount * sizeof(Route));
			free(routeArray);
			//����������� �������� ������� ��������� �� �����
			routeArray = temp;

			puts("������ �������!");
			isFileEdited = true;
			Print();
			break;
		}
		default:
		{
			puts("��������.");
			getch();
			break;
		}
	}
}

void SaveFile()
{
	if (!isFileLoaded()) return;
	if (file = fopen(path, "w"))
	{
		for (int i = 0; i < recordCount; i++)
		{
			WriteRecord(&routeArray[i]);
		}
		fclose(file);
		isFileEdited = false;
		printf("���� '%s' ��������.\n", path);
		getch();
	}
	else
	{
		printf("������ ���������� ����� '%s'.\n");
		getch();
		return;
	}
}

void Exit()
{
	if (isFileEdited)
	{
		puts("���� ��� �������. ���������? y/n");
		char answer = getch();
		if (answer == 'y')
		{
			SaveFile();
		}
	}
	exit(0);
}

void CreateTestFile()
{
	struct Route route1 = { "18A" , 8, 6.2 };
	struct Route route2 = { "11" , 5, 7.15 };
	struct Route route3 = { "15�" , 2, 9.8 };
	struct Route route4 = { "32" , 4, 8.48 };
	struct Route route5 = { "50" , 11, 10.6 };

	file = fopen("brest.txt", "w");
	if (file != NULL) 
	{
		WriteRecord(&route1);
		WriteRecord(&route2);
		WriteRecord(&route3);
		WriteRecord(&route4);
		WriteRecord(&route5);
		fclose(file);
	}
}

void WriteRecord(struct Route *route)
{
	fprintf(file, "%s;%u;%f;\n", route->Number, route->CarsCount, route->RouteLength);
}

void EditNumber(int index)
{
	strcpy(routeArray[index].Number, EnterNumber());
	puts("����� �������� �������!");
	isFileEdited = true;
	Print();
}

void EditCarsCount(int index)
{
	routeArray[index].CarsCount = EnterCarsCount();
	puts("���������� ����� �������� ��������!");
	isFileEdited = true;
	Print();
}

void EditRouteLength(int index)
{
	routeArray[index].RouteLength = EnterRouteLength();
	puts("����� �������� ��������!");
	isFileEdited = true;
	Print();
}

int �ompareByCarsCount(const void *elem1, const void *elem2)
{
	Route *first = (Route*)elem1;
	Route *second = (Route*)elem2;
	if (first->CarsCount < second->CarsCount)
		return -1;
	else if (first->CarsCount > second->CarsCount)
		return 1;
	else
		return 0;
}

int �ompareByRouteLength(const void *elem1, const void *elem2)
{
	Route *first = (Route*)elem1;
	Route *second = (Route*)elem2;
	if (first->RouteLength < second->RouteLength)
		return -1;
	else if (first->RouteLength > second->RouteLength)
		return 1;
	else
		return 0;
}

void SortByCarsCount()
{
	qsort(routeArray, recordCount, sizeof(Route), �ompareByCarsCount);
	isFileEdited = true;
	puts("�������������� �� ���������� �����!");
	Print();
}

void SortByRouteLength()
{
	qsort(routeArray, recordCount, sizeof(Route), �ompareByRouteLength);
	isFileEdited = true;
	puts("�������������� �� ����� ��������!");
	Print();
}