//
// Created by milos on 27/05/2022.
//

#include "Password.h"

#include <utility>


Password::Password(const string& line) {
	this->desc = "";
	this->password = "";
	this->category = "";
	int status = 0;
	for(char a : line) {
		if(a == ';') {
			status++;
			continue;
		}

		switch(status) {
			case 0:
				desc.push_back(a);
				break;
			case 1:
				password.push_back(a);
				break;
			case 2:
				category.push_back(a);
				break;
			case 3:
				login.push_back(a);
				break;
			case 4:
				url.push_back(a);
				break;
			default:
				cerr << "Something went wrong in creation of password..." << endl;
				break;
		}
	}

}

ostream &operator<<(ostream &os, const Password &p) {
	if(p.url.empty() && p.login.empty())
		os  << p.desc + " " + p.password + " " + p.category;
	else
		os  << p.desc + " " + p.password + " " + p.category + " " + p.login + " " + p.url;
	return os;
}


bool Password::operator<(const Password& p) {
	/*if(p.desc.length() < this->desc.length())
		return false;*/
	if(this->desc.length() < p.desc.length())
		return true;
	else
		return false;
}



bool Password::operator>(const Password& p) {
	if(this->desc.length() < p.desc.length())
		return false;
	else
		return true;
}

bool Password::operator==(const Password &p) {
	if(this->password == p.password)
		return true;
	else
		return false;
}

string Password::getPasswordString() {
	if(this->login.empty() && this->url.empty())
		return string(this->desc + ';' + this->password + ';' + this->category);
	else if(!this->login.empty() && this->url.empty())
		return string(this->desc + ';' + this->password + ';' + this->category + ';' + this->login);
	else if(this->login.empty() && !this->url.empty())
		return string(this->desc + ';' + this->password + ';' + this->category + ';' + this->url);
	else
		return string(this->desc + ';' + this->password + ';' + this->category + ';' + this->login + ';' + this->url);
}

string Password::getDesc() {
	return this->desc;
}

string Password::getCategory() {
	return this->category;
}

void Password::setMarkedForDelete() {
	this->markedForDelete = true;
}

void Password::setDesc(string edit) {
	this->desc = std::move(edit);
}

void Password::setPassword(string edit) {
	this->password = std::move(edit);
}

void Password::setCategory(string edit) {
	this->category = std::move(edit);
}

void Password::setLogin(string edit) {
	this->login = std::move(edit);
}

void Password::setURL(string edit) {
	this->url = std::move(edit);
}
