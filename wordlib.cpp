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

	// returns the number of words in the library
	int WordLib::getNumWords()
	{
		return num_words;
	}

	// returns the first word in the library if it is not empty
	// returns the empty string if it is
	string WordLib::getWord()
	{
		string word = "";
		Word* temp = lib;

		// find and return the first word in the linked list
		if (lib != nullptr)
		{
			word = temp->word;
			lib = temp->next;
			delete temp;
			--num_words;
		}

		return word;
	}

	// appends the word to end of the library
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

	// removes the word from the library if it exists
	// returns a boolean that indicates whether the operation was succesful
	bool WordLib::remove(std::string str)
	{
		int is_found;
		Word* curr = lib;
		Word* prev;

		if(curr == nullptr)
		{
			// library is empty
			is_found = false;
		}
		else if (curr->word == str)
		{
			// remove the head node
			is_found = true;
			curr = lib->next;
			delete lib;
			lib = curr;
			--num_words;
		}
		else
		{
			prev = lib;
			curr = lib->next;
			is_found = false;

			// search through the linked list for the word
			while (curr != nullptr)
			{
				if (curr->word == str)
				{
					is_found = true;
					prev->next = curr->next;
					delete curr;
					curr = nullptr;
					--num_words;
				}
				else
				{
					curr = curr->next;
					prev = prev->next;
				}
			}
		}

		return is_found;
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

	// writes the entire library to the file
	void WordLib::storelib(const std::string filename)
	{
		Word* curr = lib;
		ofstream file(filename);
		
		while (curr != nullptr)
		{
			file << curr->word << '\n';
			curr = curr->next;
		}

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