#ifndef HM_HANGMAN_H
#define HM_HANGMAN_H
#include <iostream>
#include "wordlib.h"

const int MAX_GUESSES = 6;
const std::string CHARACTER_BANK = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string FILENAME = "words.txt";

namespace hangman
{
	class Hangman
	{
		std::string o_word;
		std::string h_word;
		std::string ch_bank;
		WordLib library;

		int menu();
		void displayBanner() const;
		void displayRules() const;
		void addWord();
		void playSinglePlayer();

		void drawHangman(int guesses) const;
		void drawWordDisplay() const;
		void drawCharacterBank() const;
		void reset(const std::string word);

		public:
			Hangman();
			int run();
	};
}
#endif
