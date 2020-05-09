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

		public:
			WordLib();
			~WordLib();
			void append(std::string str);
			std::ostream& display(std::ostream& os = std::cout) const;
	};
}
#endif
