#include <limits>
#include <string>
#include "hangman.h"
#include "util.h"

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::ostream;
using std::streamsize;
using std::string;

using namespace util;

namespace hangman
{
	Hangman::Hangman()
	{
		library.read(FILENAME);
	}

	// displays a menu that players can choose from
	int Hangman::menu()
	{
		int choice;

		cout << endl;
		if (library.getNumWords() < 1)
			cout << "***** NO WORDS AVAILABLE *****" << endl;
		cout << "  1. How to Play" << endl;
		cout << "  2. Add Word" << endl;
		cout << "  3. 1-player" << endl;
		cout << "  4. Quit\n" << endl;
		cout << "  Selection: ";

		while (!(cin >> choice) || (choice < 1 || choice > 5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "  Selection: ";
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return choice;
	}

	// draws the hangman game banner
	void Hangman::displayBanner() const
	{
		cout << "***************************************************************" << endl;
		cout << "*  __________________________________________________________  *" << endl;
		cout << "* |                                                          | *" << endl;
		cout << "* |----------------------------------------------------------| *" << endl;
		cout << "* |      _    _                                              | *" << endl;
		cout << "* |     | |  | |                                             | *" << endl;
		cout << "* |     | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __       | *" << endl;
		cout << "* |     |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\      | *" << endl;
		cout << "* |     | |  | | (_| | | | | (_| | | | | | | (_| | | | |     | *" << endl;
		cout << "* |     |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|     | *" << endl;
		cout << "* |                          __/ |                           | *" << endl;
		cout << "* |                         |___/                            | *" << endl;
		cout << "* |----------------------------------------------------------| *" << endl;
		cout << "* |__________________________________________________________| *" << endl;
		cout << "*                                                              *" << endl;
		cout << "****************************************************************" << endl;
	}

	// displays the rules of the game
	void Hangman::displayRules() const
	{
		cout << "  Objective: Guess the hidden word correctly before the stickman is hanged!" << endl;
		cout << "\n  Players may guess a single character at a time or the entire word if they think they know what the word is." << endl;
		cout << "  Each incorrect guess will reduce the number of available guesses that depends on the selected difficulty. 6(Normal), 3(Hard)" << endl;
		cout << "  A player loses when they run out of guesses and the stickman is fully hanged." << endl;
	}

	// adds a new word to the library
	void Hangman::addWord()
	{
		string word;
		cout << "  Enter a word: ";
		getline(cin, word);
		word = toUpperStr(word);
		library.append(word);
		library.write(FILENAME, word);
	}

	// plays the single player mode
	void Hangman::playSinglePlayer()
	{
		string player_guess;
		int pos;
		int invalid_guesses = 0;
		string::size_type correct_guesses = 0;
		bool valid_guess;

		cout << "\n*************** Singleplayer Mode ***************\n" << endl;

		while (invalid_guesses < MAX_GUESSES && correct_guesses < o_word.length())
		{
			valid_guess = false;

			// display game visuals
			drawHangman(invalid_guesses);
			drawWordDisplay();
			drawCharacterBank();

			cout << "Enter a character: ";

			// validate player input
			while (!valid_guess)
			{
				getline(cin, player_guess);

				// check if the player has already guessed the character
				pos = ch_bank.find(toupper(player_guess[0]));
				if (pos != string::npos)
				{
					ch_bank.replace(pos, 1, "#");
					valid_guess = true;

					// check if character is in the word
					pos = o_word.find(toupper(player_guess[0]));
					if (pos != string::npos)
					{
						correct_guesses += revealHiddenCharacters(o_word, h_word, toupper(player_guess[0]));
					}
					else
					{
						invalid_guesses++;
					}
				}
				else
				{
					cout << "You've already guessed that character. Enter a character: ";
				}
			}
		}

		drawHangman(invalid_guesses);
		drawWordDisplay();
		drawCharacterBank();

		correct_guesses == o_word.length() ? (cout << "***** WINNER *****\n") : (cout << "***** BETTER LUCK NEXT TIME *****\nAnswer: " << o_word << "\n");
		pause();
	}

	// draws the hangman based on the number of incorrect guesses the player has made
	void Hangman::drawHangman(int guesses) const
	{
		int count;

		cout << "       _______" << endl;

		if (guesses < 1)
		{
			for (int i = 0; i < 9; ++i)
			{
				cout << "      |" << endl;
			}
		}
		else
		{
			if (guesses >= 1)
			{
				cout << "      |	      |" << endl;
				cout << "      |	      |" << endl;
				cout << "      |      ()" << endl;
			}

			if (guesses >= 4)
			{
				cout << "      |      /|\\" << endl;
			}
			else if (guesses >= 3)
			{
				cout << "      |      /|" << endl;
			}
			else if (guesses >= 2)
			{
				cout << "      |       |" << endl;
			}

			if (guesses >= 6)
			{
				cout << "      |      / \\" << endl;
			}
			else if (guesses >= 5)
			{
				cout << "      |      /" << endl;
			}
			
			if (guesses == 1)
			{
				count = 6;
			}
			else if (guesses > 1 && guesses < 5)
			{
				count = 5;
			}
			else
			{
				count = 4;
			}

			for (int i = 0; i < count; ++i)
			{
				cout << "      |" << endl;
			}
		}

		cout << "  ----------------------" << endl;
	}

	// displays the word the player is trying to guess
	void Hangman::drawWordDisplay() const
	{
		cout << "\n  ";
		for (string::size_type i = 0; i < o_word.length(); ++i)
		{
			cout << h_word[i];
			cout << " ";
		}

		cout << endl << endl;
	}

	// displays the available characters the player can guess from
	void Hangman::drawCharacterBank() const
	{
		cout << "[--------- Available Characters ---------]\n" << endl;

		for (string::size_type i = 0; i < ch_bank.length(); ++i)
		{
			if (i > 0 && (i % 7) == 0)
			{
				cout << "\n" << endl;
			}

			cout << "  ";
			cout << ch_bank[i];
			cout << " ";
		}

		cout << "\n\n[----------------------------------------]\n" << endl;
	}

	// resets game variables
	void Hangman::reset(const string word)
	{
		ch_bank = CHARACTER_BANK;
		o_word = word;
		h_word = createHiddenWord(o_word, '_');
	}

	int Hangman::run()
	{
		int choice;
		bool running = true;
		bool replay = true;
		displayBanner();

		while (running)
		{
			switch (choice = menu())
			{
			case 1:
				displayRules();
				cout << "\n  ";
				pause();
				break;
			case 2:
				cout << endl;
				addWord();
				break;
			case 3:
				while (replay && library.getNumWords() > 0)
				{
					reset(library.getWord());
					playSinglePlayer();
					cout << "Play again? Y/N:";
					replay = yesOrNoPrompt("Y/N, retry: ");
				}
				break;
			case 4:
				running = false;
				library.storelib(FILENAME);
				break;
			default:
				running = false;
			}
		}

		return 0;
	}
}


