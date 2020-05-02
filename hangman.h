#ifndef HM_HANGMAN_H
#define HM_HANGMAN_H
#include "library.h"

const int MAX_GUESSES = 6;

namespace hangman
{
	class Hangman
	{
		int guesses;

		int menu();
		void displayBanner();
		void displayRules();
		void drawHangman();
		void displayWord();
		
		bool guess(char c);

		public:
			Hangman();
			int run();
	};
}
#endif
