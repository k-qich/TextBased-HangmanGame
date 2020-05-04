#ifndef UTIL_H
#define UTIL_H
#include <iostream>

namespace util
{
	void pause();
	std::string createHiddenWord(const std::string str, const char c);
	std::string revealHiddenCharacters(const std::string str, const std::string h_str, const char c);
}
#endif
