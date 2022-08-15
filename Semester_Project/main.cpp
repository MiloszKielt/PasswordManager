#include <iostream>
#include <fstream>
#include <filesystem>
#include "Manager.h"

using namespace std;
namespace fs = std::filesystem;



/**
 * function listing all .txt files available in execution directory
 */
void listFiles();
/**
 * function for checking whether a file is in a directory
 * @param dir directory in which we are searching
 * @param fname name of file that we search for
 * @return bool value depending on whether we found the file or not
 */
bool checkFileInPath(fs::path* dir, const string& fname);

/**
 * Functions for encryption and decryption of files
 * @param file file which we want to encrypt/decrypt
 * @param passwrd Main password used for encryption/decryption
 */
void encrypt(const fs::path* file, const string & passwrd);
void decrypt(const fs::path* file, const string & passwrd);

/**
 * Function filling content of vector using lines from file
 * @param file file from which we get the content
 * @param passwords vector to which we save the content
 */
void fillPasswordData(const fs::path* file, vector<string>* passwords);

/**
 * function that acquires key value needed to decrypt the file
 * @param passwrd password used for decrypting (password entered by the user)
 * @return key value of entered password
 */
char getKeyValue(const string & passwrd);

/**
 * Function updating the state of passwords after all operations are done in manager
 * @param manager the manager in which we did the operations
 * @param file file to which we update the state
 * @param passwords vector of passwords to which we further assign passwords from the manager
 */
void updatePasswords(Manager* manager, const fs::path* file, vector<string> * passwords);

/**
 * checks if file is empty
 * @param filePath file to be checked
 * @return true if file is empty, false otherwise
 */
bool checkFileEmpty(const fs::path* filePath);



int main() {
	vector<string> passwords;
	string passwrd;
	string fname;


	cout << "Please choose a file or input absolute path" << endl;
	cout << "List of available files:" << endl;
	listFiles();
	getline(cin,fname);

	std::filesystem::path filePath = fs::current_path().parent_path();
	if(checkFileInPath(&filePath,fname)) {
		filePath /= fname;
	}
	std::filesystem::path myPath(fname);
	fstream f(filePath);

	if(f.good()) {
		if(checkFileEmpty(&filePath)) {
			cout << "this file is empty, provide new master password to initialize it:\n";
			getline(cin,passwrd);
			passwords.push_back("MAIN;" + passwrd + ";MAIN");
		} else {
			cout << "File opened, provide password" << endl;
			getline(cin, passwrd);
			decrypt(&filePath, passwrd);
		}
	} else {
		cout << "Wrong, file does not exist" << endl;
	}
	fillPasswordData(&filePath,&passwords);
	Manager passwordManager(passwords);
	updatePasswords(&passwordManager,&filePath, &passwords);
	encrypt(&filePath,passwrd);
	return 0;
}

void updatePasswords(Manager* manager, const fs::path* file, vector<string>* passwords) {
	*passwords = (*manager).getPasswords();

	ofstream out(*file);
	out.clear();
	for(const string& s : *passwords) {
		cout << s << endl;
		out << s << '\n';
	}
}

void fillPasswordData(const fs::path* file, vector<string>* passwords) {
	ifstream fin(*file);

	if(fin.good()) {
		string content;
		while (getline(fin, content,'\n')) {
			(*passwords).insert((*passwords).end(),content);
		}

	}
}


bool checkFileInPath(fs::path* dir, const string& fname) {
	for(auto const& file : fs::directory_iterator(*dir)) {
		if(file.path().filename() == fname)
			return true;
	}
	return false;
}

void listFiles() {
	std::filesystem::path mainDir = std::filesystem::current_path().parent_path();
	for(auto const& file : std::filesystem::directory_iterator(mainDir)){
		if(file.is_regular_file() && file.path().extension() == ".txt")
			std::cout<<file.path().filename()<<"\n";
	}
}


char getKeyValue(const string & passwrd) {
	int key = 0;
	for(char c : passwrd) {
		key += c;
	}
	return char(key%25);
}

void encrypt(const fs::path* file, const string & passwrd) {
	char key = getKeyValue(passwrd);

	fstream fin;
	fstream fout;

	fin.open(*file);
	fout.open(*file);
	char c;
	while(fin >> noskipws >> c) {
		if(c != '\n')
			c = char(c - key + 33);
		fout << c;

	}

}

void decrypt(const fs::path* file, const string & passwrd) {
	char key = getKeyValue(passwrd);
//	fstream fin(file, std::ios::in);
//	fstream fout(file, std::ios::out);
	fstream fin;
	fstream fout;

	fin.open(*file);
	fout.open(*file);
	char c;

	while(fin >> noskipws >> c) {
		if(c != '\n')
			c = char(c + key - 33);
		fout << c;
	}
}

bool checkFileEmpty(const fs::path* filePath) {
	int charCounter = 0;
	char c;
	ifstream fin(*filePath);
	while(fin >> noskipws >> c) {
		charCounter++;
		if(charCounter > 0)
			return false;
	}
	return true;
}
