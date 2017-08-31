#include "Input.h"
#include <fstream>
#include <string> 
#include <iostream>
#include <sstream>

using namespace std;

bool InputFile::Read(std::string f) {
	string line;
	stringstream info;
	ifstream file;
	file.open(f);

	if (!file) {
		_contents = " ";
		return false;
	}

	while (getline (file, line)) {
		cout << line << endl;
	}
	_contents = info.str();
	file.close();
	cin.get();
	return true;

}

string InputFile::GetContents() {

	return _contents;

}