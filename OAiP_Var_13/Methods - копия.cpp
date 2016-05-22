#include "stdafx.h"
#include "Methods.h"
#include "Route.h"
#define BUFFER_SIZE 256

FILE * file; //Указатель на файл.
struct Route *routeArray;	//Указатель на массив записей.
unsigned int recordCount = 0;	//Количество записей.
char path[BUFFER_SIZE];	//Путь к файлу.
bool isLoaded = false;	//Загружен ли файл.
bool isFileEdited = false; //Редактировался ли файл.
const short tableWidth = 73; //Ширина таблицы.

void ShowMenu()
{
	system("cls");
	puts("Городской транспорт\n");
	puts("1. Загрузить файл");
	puts("2. Добавить запись в конец");
	puts("3. Просмотр всех записей");
	puts("4. Сохранить файл");
	puts("5. Корректировка выбранной записи");
	puts("6. Сортировка записей по числовому полю");
	puts("7. Удаление элементов, начиная от выбранного");
	puts("8. Выход");
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
	puts("Путь к файлу:");
	scanf("%s", &path);
	
	if (file = fopen(path, "r"))
	{
		//Считаем количество строк в фале
		recordCount = GetRowsCount(file);
		//Инициализируем массив структур
		routeArray = new Route[recordCount];
		printf("Файл '%s' загружен! Количество записей: %u.\n", path, recordCount);
		isLoaded = true;

		//Парсим строки файла в структуры
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
		printf("Не удалось загрузить файл '%s'.\n", path);
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
	printf("|Номер маршрута\t\t|Единиц транспорта\t|Длина маршрута(км)\t|\n");
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
		puts("Файл не загружен.");
		getch();
		return false;
	}
	if (routeArray == NULL)
	{
		puts("Массив записей пуст.");
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
	//Создаем массив указателей на записи размером больше текущего 1
	struct Route *temp = new Route[recordCount+1];
	//Копируем в него содержимое текущего массива
	memcpy(temp, routeArray, (recordCount) * sizeof(Route));
	//Копируем новую запись в конец
	memcpy(&temp[recordCount], route, sizeof(Route));
	//Освобождаем память тукещего массива
	free(routeArray);
	//Устанавливаем текущему массиву указатель на новый
	routeArray = temp;
	//Увеличиваем счетчик числа записей на 1 
	recordCount++;
	//Помечаем что массив изменен
	isFileEdited = true;
	printf("Запись добавлена! Количество записей: %u\n", recordCount);
	Print();
}

void fflushstdin()
{
	int c;
	while ((c = fgetc(stdin)) != EOF && c != '\n');
}

int EnterCarsCount()
{
	printf("Единиц транспорта: ");
	unsigned int carsCount;
	fflushstdin();
	if (scanf("%d", &carsCount) != 1)
	{
		puts("Ошибка формата входных данных.");
		return EnterCarsCount();
	}
	else
	{
		return carsCount;
	}
}

float EnterRouteLength()
{
	printf("Длина маршрута(км): ");
	float routeLength = 0.0;
	fflushstdin();
	if (scanf("%f", &routeLength) != 1)
	{
		puts("Ошибка формата входных данных.");
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
	printf("Номер маршрута: ");
	scanf("%10s", &Number);
	return Number;
}

void Add()
{
	if (!isFileLoaded()) return;
	system("cls");
	puts("Добавление записи.\n");
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
	puts("Редактирование записи.\n");
	printf("Введите индекс записи (от 0 до %u): ", recordCount - 1);
	unsigned int index = 0;
	scanf("%u", &index);
	if (index > recordCount - 1)
	{
		puts("Ошибка! Указанный индекс находится за границами массива.");
		getch();
		return;
	}
	puts("Выберите поле для редактирования:");
	puts(" 1. Номер маршрута");
	puts(" 2. Единиц транспорта");
	puts(" 3. Длина маршрута");
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
	puts("Сортировка массива по числовому полю.\n");
	puts("Выберите поле, по которому надо отсортировать массив:");
	puts(" 1. Количество единиц транспорта на маршуте");
	puts(" 2. Длина маршрута");
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
	puts("Удаление записей начиная от выбранной.\n");
	printf("Индекс записи (от 0 до %u): ", recordCount - 1);
	unsigned int index = 0;
	scanf("%u", &index);
	if (index > recordCount - 1)
	{
		puts("Ошибка! Указанный индекс находится за границами массива.");
		getch();
		return;
	}
	printf("Внимание! Будут удалены все записи начиная с %u-й. Продолжить? y/n\n", index);
	char choise = getch();
	switch (choise)
	{
		case 'y':
		{
			//Считаем сколько записей нужно оставить
			recordCount = recordCount - (recordCount - index);
			//Создаем массив с новым количеством записей
			struct Route *temp = new Route[recordCount];
			memcpy(temp, routeArray, recordCount * sizeof(Route));
			free(routeArray);
			//Присваиваем текущему массиву указатель на новый
			routeArray = temp;

			puts("Записи удалены!");
			isFileEdited = true;
			Print();
			break;
		}
		default:
		{
			puts("Отменено.");
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
		printf("Файл '%s' сохранен.\n", path);
		getch();
	}
	else
	{
		printf("Ошибка сохранения файла '%s'.\n");
		getch();
		return;
	}
}

void Exit()
{
	if (isFileEdited)
	{
		puts("Файл был изменен. Сохранить? y/n");
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
	struct Route route3 = { "15Б" , 2, 9.8 };
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
	puts("Номер маршрута изменен!");
	isFileEdited = true;
	Print();
}

void EditCarsCount(int index)
{
	routeArray[index].CarsCount = EnterCarsCount();
	puts("Количество машин маршрута изменено!");
	isFileEdited = true;
	Print();
}

void EditRouteLength(int index)
{
	routeArray[index].RouteLength = EnterRouteLength();
	puts("Длина маршрута изменена!");
	isFileEdited = true;
	Print();
}

int СompareByCarsCount(const void *elem1, const void *elem2)
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

int СompareByRouteLength(const void *elem1, const void *elem2)
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
	qsort(routeArray, recordCount, sizeof(Route), СompareByCarsCount);
	isFileEdited = true;
	puts("Отсортированно по количеству машин!");
	Print();
}

void SortByRouteLength()
{
	qsort(routeArray, recordCount, sizeof(Route), СompareByRouteLength);
	isFileEdited = true;
	puts("Отсортированно по длине маршрута!");
	Print();
}