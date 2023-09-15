#include <iostream>
#include "Autorization.h"
#include "Utilits.h"
#include <Windows.h>

std::string FILE_USERS = "Users.txt";

int main()
{
	Auto autorization(FILE_USERS);
	setlocale(LC_ALL, "RUS");
	autorization.start();
	accentPrint("Удачи!");
	exit(0);
}