#pragma once
#include "Route.h"
#include "stdafx.h"

void ShowMenu(); //Вывод главного меню.
int GetRowsCount(FILE * file); //Подсчет количества строк в текстовом файле.
void OpenFile(); //Открытие файла.
Route ParseRoute(char*); //Парсинг строки в элемент структуры.
void Print();	//Вывод всех записей.
void PrintHeader();	//Вывод шапки таблицы.
void PrintLine(); //Вывод линии.
bool isFileLoaded(); //Проверка загружен ли файл в массив указателей на записи.
void fflushstdin(); //Очистка буфера входного потока.
int EnterCarsCount(); //Ввод с клавиатуры количества машин.
float EnterRouteLength(); //Ввод с клавиатуры длины маршрута.
char * EnterNumber(); //Ввод с клавиатуры номера маршрута.
void Add();		//Добавление записи.
void Edit();	//Корректировка записи.
void Sort();	//Сортировка записей по выбранному полю.
void RemoveRange(); //Удаление записей, начиная от выбранной.
void SaveFile(); //Сохранение файла.
void Exit();	//Выход из программы.
void CreateTestFile(); //Создание тестового файла.
void WriteRecord(Route * route); //Добавление в файл одной записи.
void EditNumber(int index); //Редактирование номера маршрута.
void EditCarsCount(int index);  //Редактирование количества единиц транспорта на маршруте.
void EditRouteLength(int index); //Редактирование длины маршрута.
void SortByCarsCount();	//Сортировка массива по количеству единиц транспорта на маршруте.
void SortByRouteLength(); //Сортировка массива по длине маршрута.
int СompareByCarsCount(const void*, const void*); //Функция для сравнения двух элементов структуры по кол-ву машин.
int СompareByRouteLength(const void*, const void*); //Функция для сравнения двух элементов структуры по длине маршрута.
