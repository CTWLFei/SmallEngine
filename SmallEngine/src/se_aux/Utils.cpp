#include <se_aux/Utils.h>
#include <fstream>

Utils::SystemPath Utils::SysPath;

Utils::SystemPath Utils::ExtractPath(string rootPath)
{
	string specificSolutionPath = rootPath.substr(0, rootPath.find_last_of('\\'));
	string solutionPath = specificSolutionPath.substr(0, specificSolutionPath.find_last_of('\\'));
	SysPath.RootPath = solutionPath.substr(0, solutionPath.find_last_of('\\')) + "\\SmallEngine";
	SysPath.ShaderPath = SysPath.RootPath + "\\shader\\";
	SysPath.TexturePath = SysPath.RootPath + "\\textures\\";
	SysPath.ModelPath = SysPath.RootPath + "\\models\\";
	return SysPath;
}

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

void Utils::SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}