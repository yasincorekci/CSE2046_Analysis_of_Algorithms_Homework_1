
#ifndef __UTIL_H
#define __UTIL_H

#include <string>

class Util {
public:
	static std::string readFile(const std::string& filename);
	static bool writeFile(const std::string& filename, const std::string& content);
	static std::string createRandomHtml();
};

#endif
