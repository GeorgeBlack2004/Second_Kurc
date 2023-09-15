#include "User.h"

User::User(string login, string password, bool isAdmin, bool access)
{
	this->login = login;
	this->isAdmin = isAdmin;
	this->password = password;
	this->access = access;
}

string User::getLogin() { return login; } 

void User::setLogin(string login) { this->login = login; }

void User::setPassword(string password) { this->password = password; }

string User::getPassword() { return password; }

bool User::checkPassword(string password) { return this->password == password; }

void User::setRole(bool isAdmin) { this->isAdmin = isAdmin; }

bool User::getRole() { return isAdmin; }

void User::setAccess(bool access) { this->access = access; }

bool User::getAccess() { return access; }