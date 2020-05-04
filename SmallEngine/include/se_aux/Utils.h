#ifndef __UTILS_H__
#define __UTILS_H__
#include <string>

using namespace std;

class Utils {
public:
	static string loadResource(string fileName);
private:
	Utils();
};

#endif