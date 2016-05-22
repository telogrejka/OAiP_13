#pragma once
#include "Route.h"
#include "stdafx.h"

void ShowMenu(); //����� �������� ����.
int GetRowsCount(FILE * file); //������� ���������� ����� � ��������� �����.
void OpenFile(); //�������� �����.
Route ParseRoute(char*); //������� ������ � ������� ���������.
void Print();	//����� ���� �������.
void PrintHeader();	//����� ����� �������.
void PrintLine(); //����� �����.
bool isFileLoaded(); //�������� �������� �� ���� � ������ ���������� �� ������.
void fflushstdin(); //������� ������ �������� ������.
int EnterCarsCount(); //���� � ���������� ���������� �����.
float EnterRouteLength(); //���� � ���������� ����� ��������.
char * EnterNumber(); //���� � ���������� ������ ��������.
void Add();		//���������� ������.
void Edit();	//������������� ������.
void Sort();	//���������� ������� �� ���������� ����.
void RemoveRange(); //�������� �������, ������� �� ���������.
void SaveFile(); //���������� �����.
void Exit();	//����� �� ���������.
void CreateTestFile(); //�������� ��������� �����.
void WriteRecord(Route * route); //���������� � ���� ����� ������.
void EditNumber(int index); //�������������� ������ ��������.
void EditCarsCount(int index);  //�������������� ���������� ������ ���������� �� ��������.
void EditRouteLength(int index); //�������������� ����� ��������.
void SortByCarsCount();	//���������� ������� �� ���������� ������ ���������� �� ��������.
void SortByRouteLength(); //���������� ������� �� ����� ��������.
int �ompareByCarsCount(const void*, const void*); //������� ��� ��������� ���� ��������� ��������� �� ���-�� �����.
int �ompareByRouteLength(const void*, const void*); //������� ��� ��������� ���� ��������� ��������� �� ����� ��������.
