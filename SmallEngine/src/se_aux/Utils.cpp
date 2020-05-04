#include <se_aux/Utils.h>
#include <fstream>

string Utils::loadResource(string fileName)
{
	string result;
	ifstream readFile(fileName);
	if (readFile.is_open()) {
		string s;
		while (getline(readFile, s)) {
			result += s;
		}
	}
	readFile.close();
	return result;
}