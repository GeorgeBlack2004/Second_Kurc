#pragma once

#include <vector>
#include <string>

using namespace std;

class User {
private:
	bool isAdmin, access;
	string login, password;
public:
	User(string login, string password, bool isAdmin, bool access);
	string getLogin();
	void setLogin(string login);
	void setPassword(string password);
	string getPassword();
	void setRole(bool isAdmin);
	bool getRole();
	void setAccess(bool access);
	bool getAccess();
	bool checkPassword(string password);
};