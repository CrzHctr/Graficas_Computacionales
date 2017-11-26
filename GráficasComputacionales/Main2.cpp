#include "InputFile.h"
#include <iostream>
#include <string>

using namespace std;

int main2(int argc, const char * argv[]) {

	string filename = "Prueba.txt";
	InputFile myFile;
	myFile.Read(filename);
	string contents = myFile.GetContents();
	cout << "Contents: " << contents << std::endl;
	return 0;
}