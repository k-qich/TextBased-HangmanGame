#include <limits>
#include "util.h"

using std::cin;
using std::cout;
using std::streamsize;
using std::string;
using std::numeric_limits;

namespace util
{
	void pause()
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Press ENTER to continue";
		while (cin.get() != '\n');
	}

	string createHiddenWord(const string str, const char c)
	{
		string ret;

		for (unsigned int i = 0; i < str.length(); ++i)
		{
			ret += c;
		}

		return ret;
	}
	std::string revealHiddenCharacters(const std::string str, const std::string h_str, const char c)
	{
		string ret = h_str;

		for (unsigned int i = 0; i < str.length(); ++i)
		{
			if (str[i] == c)
				ret[i] = c;
		}

		return ret;
	}
}

