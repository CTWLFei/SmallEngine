#ifndef __UTILS_H__
#define __UTILS_H__
#include <string>
#include <vector>
using namespace std;

class Utils {
public:
	struct SystemPath {
		string RootPath;
		string ShaderPath;
		string TexturePath;
		string ModelPath;
	};
	static SystemPath SysPath;
	static SystemPath ExtractPath(string rootPath);
	static string loadResource(string fileName);
	static void SplitString(const string& s, vector<string>& v, const string& c);
private:
	Utils();
};

#endif