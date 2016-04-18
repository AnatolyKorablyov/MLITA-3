//В школу бальных танцев профессора Падеграса записались N учеников — мальчиков и
//
//девочек.Профессор построил их в один ряд, и хочет отобрать из них для первого занятия группу
//
//стоящих подряд учеников, в которой количество мальчиков и девочек одинаково.Сколько
//
//вариантов выбора есть у профессора ? Решить задачу с помощью рекуррентных соотношений.
//
//Ввод.В первой строке входного файла задано число N(1 ≤ N ≤ 10 6).Во второй строке задается
//
//описание построенного ряда из мальчиков и девочек — строка из N символов a и b(символ a
//
//	соответствует девочке, а символ b — мальчику).
//
//	Вывод.В единственной строке выходного файла должно содержаться количество вариантов
//
//	выбора требуемой группы.
//
//	Примеры
//
//	Ввод 1 Ввод 2
//
//	3 8
//
//	bab abbababa
//
//	Вывод 1 Вывод 2
//
//	2 13

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define halfmaxlen 1000000

int arrayCase[halfmaxlen * 2 + 1];

enum ERROR_CODE { ALL_IS_OK, CANT_OPEN_FILE, INCORRECT_QUANTITY_BOYS_AND_GIRLS, INCORRECT_ENTER};

ERROR_CODE GetInformationOfInputFile(int &quantityBoysAndGirls, string & orderBoysAndGirls)
{
	ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return ERROR_CODE::CANT_OPEN_FILE;
	}
	inputFile >> quantityBoysAndGirls;
	if (quantityBoysAndGirls >= 10000000 || quantityBoysAndGirls <= 1)
	{
		return ERROR_CODE::INCORRECT_QUANTITY_BOYS_AND_GIRLS;
	}
	inputFile >> orderBoysAndGirls;
	if (quantityBoysAndGirls != orderBoysAndGirls.length()) 
	{
		return ERROR_CODE::INCORRECT_ENTER;
	}
	return ERROR_CODE::ALL_IS_OK;
}

unsigned long long ProcessProgram(int const &quantityBoysAndGirls, string const & orderBoysAndGirls)
{
	unsigned long long result = 0;
	int findGirls = 0;
	arrayCase[halfmaxlen] = 1;
	for (int i = 0; i < quantityBoysAndGirls; ++i)
	{
		if (orderBoysAndGirls[i] == 'a')
		{
			findGirls++;
		}
		else
		{ 
			findGirls--;
		}
		result += arrayCase[halfmaxlen + findGirls];
		arrayCase[halfmaxlen + findGirls]++;
	}
	return result;
}

ERROR_CODE WriteResultInOutputFile(unsigned long long const & result)
{
	ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return ERROR_CODE::CANT_OPEN_FILE;
	}
	outputFile << result;
	return ERROR_CODE::ALL_IS_OK;
}

int main()
{
	int quantityBoysAndGirls;
	string orderBoysAndGirls;
	unsigned long long result;
	switch (GetInformationOfInputFile(quantityBoysAndGirls, orderBoysAndGirls))
	{
		case ERROR_CODE::ALL_IS_OK:
			result = ProcessProgram(quantityBoysAndGirls, orderBoysAndGirls);
			break;
		case ERROR_CODE::CANT_OPEN_FILE:
			cout << "Incorrect file name.\n";
			return EXIT_FAILURE;
		case ERROR_CODE::INCORRECT_QUANTITY_BOYS_AND_GIRLS:
			cout << "Incorrect quantity boys and girls.\n";
			return EXIT_FAILURE;
		case ERROR_CODE::INCORRECT_ENTER:
			cout << "Incorrect data";
			return EXIT_FAILURE;
	}

	switch (WriteResultInOutputFile(result))
	{
	case ERROR_CODE::ALL_IS_OK:
		cout << "SUCCESS";
		return EXIT_SUCCESS;
	case ERROR_CODE::CANT_OPEN_FILE:
		cout << "Incorrect file name.\n";
		return EXIT_FAILURE;
	}
	
}
