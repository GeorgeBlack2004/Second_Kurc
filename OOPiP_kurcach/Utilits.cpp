#include "Utilits.h"

#include <Windows.h>
#include <conio.h>
#include <string>
#include <iostream>

int getConsoleWidth() {
	HANDLE hWndConsole = GetStdHandle(-12);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo);
	return consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
}

void accentPrint(std::string text) //========
{
	using namespace std;
	system("cls");
	cout << " ====== " << text << " ";
	for (int i = 11 + text.size(); i < getConsoleWidth(); i++)
		cout << '=';
	cout << endl;
}

void Print(std::string text) //========
{
	using namespace std;
	cout << " ======" << text;
	for (int i = 9 + text.size(); i < getConsoleWidth(); i++)
		cout << '=';
	cout << endl;
}

int protection(int a, int b, int& n)
{
	std::cin >> n;
	while (true)
	{
		while ((!std::cin) || (std::cin.get() != '\n'))
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "Некорректное значение. Повторите ввод!" << std::endl;
			std::cin >> n;
		}
		if (n >= a && n <= b) break;
		std::cout << "Возникла ошибка! Повторите ввод." << std::endl;
		std::cin >> n;
	}
	return n;
}

void error(std::string text)// Ошибка
{
	using namespace std;
	accentPrint("Ошибка");
	cout << endl << text << endl << endl;
	system("pause");
}

std::string hiddenInput() {
	using namespace std;
	string result; char ch;
	while (true) {
		ch = _getch();
		if (ch == '\r') break;
		if (ch == '\b') {
			if (result != "") {
				cout << "\b \b";
				result.pop_back();
			}
			continue;
		}
		result += ch;
		cout << '*';
	}
	cout << "\n";
	return result;
}