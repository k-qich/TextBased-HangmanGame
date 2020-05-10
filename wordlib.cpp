#include <fstream>
#include "wordlib.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
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
		num_words = 0;
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

	int WordLib::getNumWords()
	{
		return num_words;
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

		++num_words;
	}

	// reads all words from the given file into the library
	int WordLib::read(const std::string filename)
	{
		int num_read = 0;
		string word;

		ifstream file(filename);
		if (file)
		{
			// read and insert each word into the library
			while (file)
			{
				file >> word;
				if (file)
				{
					append(word);
					++num_read;
				}
			}
		}

		file.close();

		return num_read;
	}

	// appends the given word to the end of the file
	void WordLib::write(const std::string filename, std::string word)
	{
		ofstream file(filename, fstream::app);
		file << word;
		file.close();
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