#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "User.h"
#include "md5.h"
using namespace std;

class Auto
{
	vector<User> users;
	User currentUser = User("", "", 0, 0);
public:
	Auto(std::string FILE_USERS) {
		this->users_file = FILE_USERS;
	}
	void start();
	void entrance();
	void registration(bool byadmin);
	void firstrun();
	void load_users();
	void save_users();
	User* get_user_by_login(string login);
private:
	std::string users_file;
};