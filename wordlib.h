#ifndef HM_WORDLIB_H
#define HM_WORDLIB_H
#include <iostream>

const int MIN_SIZE = 2;

namespace hangman
{
	class Word
	{
		std::string word;
		Word* next;

		public:
			Word();
			friend class WordLib;
	};

	class WordLib
	{
		Word* lib;
		int num_words;

		public:
			WordLib();
			~WordLib();
			int getNumWords();
			std::string getWord();
			void append(std::string str);
			bool remove(std::string str);
			int read(const std::string filename);
			void write(const std::string filename, std::string word);
			void storelib(const std::string filename);
			std::ostream& display(std::ostream& os = std::cout) const;
	};
}
#endif
