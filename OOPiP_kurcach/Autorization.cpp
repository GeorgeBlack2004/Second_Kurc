#include <iostream>
#include "Autorization.h"
#include "Utilits.h"


void Auto::start()
{
	load_users();
	int n = -1;
	while (n != 0)
	{
		accentPrint("Добро пожаловать!!!");
		cout << "\t1) Войти\n"
			"\t2) Регистрация\n";
		Print("");
		cout << "\t0) - выйти из приложения\n";
		protection(0, 2, n);
		if (n == 1)
			entrance();
		else if (n == 2)
			registration(0);
	}
	save_users();
}

void Auto::firstrun()
{
	accentPrint("Первый запуск");
	cout << "Вы впервые запустили программу.\n"
		"Сейчас пройдет процедура регистрации учетной записи администратора.\n\n"
		"Введите логин администратора: ";
	std::string login; cin >> login;
	cout << "Введите пароль администратора: ";
	std::string password; password = hiddenInput();
	users = { User(login, md5(password), true, true) };
}

void Auto::save_users()
{
	ofstream fout(users_file);
	fout << users.size() << endl;
	for (auto user : users) {
		fout << user.getLogin() << " " << user.getPassword() << " "
			<< user.getRole() << " " << user.getAccess() << endl;
	}
	fout.close();
}

User* Auto::get_user_by_login(string login) 
{
	User* result = nullptr;
	for (auto& user : users) {
		if (user.getLogin() == login) {
			result = &user;
		}
	}
	return result;
}

void Auto::entrance()
{
	accentPrint("Вход");
	cout << "Введите ваш логин: ";
	std::string login; User* loginUser = nullptr;
	while (loginUser == nullptr) {
		cin >> login;
		loginUser = get_user_by_login(login);
		if (loginUser == nullptr) {
			cout << "Такого пользователя не существует. Попробуйте ещё раз: ";
		}
	}
	int tries = 0; std::string password;
	cout << "Введите ваш пароль: ";
	while (!loginUser->checkPassword(md5(password))) {
		if (tries == 3) {
			error("Три попытки неверного ввода. Аккаунт заблокирован.");
			loginUser->setAccess(false);
			save_users();
			exit(0);
		}
		password = hiddenInput();
		if (!loginUser->checkPassword(md5(password))) {
			cout << "Пароль неверный. Осталось " << 2 - tries << " попытки: ";
			tries++;
		}
	}
	if (!loginUser->getAccess()) {
		error("Ваш аккаунт заблокирован. Обратитесь к администратору.");
	}
	currentUser = *loginUser;
}

void Auto::registration(bool byAdmin) //Регистрация 
{
	accentPrint("Регистрация");
	cout << "Введите логин: ";
	bool alreadyExists = true;
	std::string login;
	while (alreadyExists) {
		cin >> login;
		alreadyExists = get_user_by_login(login) != nullptr;
		if (alreadyExists) {
			cout << "Пользователь с таким логином уже существует." << endl
				<< "Попробуйте ещё раз: ";
		}
	}
	std::string password = "1", password2 = "2";
	while (password != password2) {
		cout << "Введите пароль: ";
		password = hiddenInput();
		cout << "Подтвердите пароль: ";
		password2 = hiddenInput();
		if (password != password2) {
			cout << "Пароли не совпадают. Попробуйте ещё раз." << endl;
		}
	}
	cout << "Поздравляем. Аккаунт зарегистрирован." << endl;
	users.emplace_back(login, md5(password), 0, 1);
	system("pause");
}

void Auto::load_users() 
{
	ifstream fin(users_file);
	if (!fin.is_open()) {
		firstrun();
		return;
	}
	int count; fin >> count;
	for (int i = 0; i < count; i++) {
		std::string login, password;
		bool isAdmin, access;
		fin >> login >> password >> isAdmin >> access;
		if (fin.fail()) {
			error("Файл с данными пользователей повреждён. Прочесть не удалось.");
			exit(1);
		}
		users.emplace_back(login, password, isAdmin, access);
	}
	fin.close();
}