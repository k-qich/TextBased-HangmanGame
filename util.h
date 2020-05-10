#ifndef UTIL_H
#define UTIL_H
#include <iostream>

namespace util
{
	void pause();
	bool yesOrNoPrompt(const char* err_msg, std::istream& is = std::cin, std::ostream& os = std::cout);
	std::string createHiddenWord(const std::string str, const char c);
	std::string::size_type revealHiddenCharacters(const std::string str, std::string &h_str, const char c);
	std::string toUpperStr(const std::string str);
}
#endif
