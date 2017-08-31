#pragma once
#include <string>

class InputFile {

private:
	std::string _contents;

public:
	bool Read(std::string filename);
	std::string GetContents();

};