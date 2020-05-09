#include "wordlib.h"

using std::ostream;
using std::string;

namespace hangman
{
	Word::Word()
	{
		next = nullptr;
	}

	WordLib::WordLib()
	{
		lib = nullptr;
	}

	WordLib::~WordLib()
	{
		Word* curr = lib;
		Word* next = nullptr;

		while (curr != nullptr)
		{
			next = curr->next;
			delete curr;
			curr = next;
		}
	}

	// appends the word to end of linked list
	void WordLib::append(string str)
	{
		Word* curr = lib;
		Word* word = new Word;
		word->next = nullptr;
		word->word = str;

		// check if the linked list is empty
		if (curr == nullptr)
		{
			lib = word;
		}
		else
		{
			// o/w find the end of the linked list
			while (curr->next != nullptr)
			{
				curr = curr->next;
			}

			curr->next = word;
		}
	}

	// displays the entire linked list
	ostream& WordLib::display(ostream& os) const
	{
		Word* curr = lib;

		while (curr != nullptr)
		{
			os << "[" <<curr->word << "]";
			curr = curr->next;
		}

		return os;
	}
}