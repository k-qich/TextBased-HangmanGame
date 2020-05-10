#include <limits>
#include <string>
#include "util.h"

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::streamsize;
using std::string;
using std::numeric_limits;

namespace util
{
	void pause()
	{
		cout << "***** Press ENTER to continue *****";
		while (cin.get() != '\n');
	}

	bool yesOrNoPrompt(const char* err_msg, istream& is, ostream& os)
	{
		string choice;
		getline(is, choice);

		while (choice.length() != 1 || !((choice[0] == 'Y' || choice[0] == 'y') || (choice[0] == 'N' || choice[0] == 'n')))
		{
			os << err_msg;
			getline(is, choice);
		}

		return (choice[0] == 'Y' || choice[0] == 'y');
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

	string::size_type revealHiddenCharacters(const string str, string &h_str, const char c)
	{
		string::size_type num_revealed = 0;

		for (unsigned int i = 0; i < str.length(); ++i)
		{
			if (str[i] == c)
			{
				h_str[i] = c;
				num_revealed++;
			}
		}

		return num_revealed;
	}

	string toUpperStr(const string str)
	{
		string ustr;

		for (unsigned int i = 0; i < str.length(); ++i)
		{
			ustr += toupper(str[i]);
		}

		return ustr;
	}
}

