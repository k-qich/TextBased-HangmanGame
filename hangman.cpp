#include <limits>
#include "hangman.h"
#include "library.h"
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
		reset("Hangman");
	}

	int Hangman::menu()
	{
		int choice;

		cout << endl;
		cout << "  1. How to Play" << endl;
		cout << "  2. Add Word" << endl;
		cout << "  3. 1-player" << endl;
		cout << "  4. 2-player" << endl;
		cout << "  5. Quit\n" << endl;
		cout << "  Selection: ";

		while (!(cin >> choice) || (choice < 1 || choice > 5))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "  Selection: ";
		}

		return choice;
	}

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

	void Hangman::displayRules() const
	{
		cout << "  Objective: Guess the hidden word correctly before the stickman is hanged!" << endl;
		cout << "\n  Players may guess a single character at a time or the entire word if they think they know what the word is." << endl;
		cout << "  Each incorrect guess will reduce the number of available guesses that depends on the selected difficulty. 6(Normal), 3(Hard)" << endl;
		cout << "  A player loses when they run out of guesses and the stickman is fully hanged." << endl;
	}

	void Hangman::playSinglePlayer()
	{
		string player_guess;
		bool valid_guess;
		unsigned int corr_guesses = 0;
		int inv_guesses = 0;
		int pos;

		cout << "\n*************** Singleplayer Mode ***************\n" << endl;

		while (inv_guesses < MAX_GUESSES && corr_guesses < o_word.length())
		{
			valid_guess = false;

			// display game visuals
			drawHangman(inv_guesses);
			drawWordDisplay();
			drawCharacterBank();

			// prompt player to guess a character or the entire word
			cout << "Enter a character or a word: ";
			
			// validate player input
			while (!valid_guess)
			{
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, player_guess);

				if (player_guess.length() == 1)
				{
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
							h_word = revealHiddenCharacters(o_word, h_word, player_guess[0]);
							corr_guesses++;
						}
						else
						{
							inv_guesses++;
						}
					}
					else
					{
						cout << "You've already guessed that character. Enter a character: ";
					}
				}
				else
				{
					// check if player's guess matches the full word					
					player_guess.compare(o_word) == 0 ? corr_guesses++ : inv_guesses++;
					valid_guess = true;
				}
			}
		}

		corr_guesses == o_word.length() ? (cout << "***** WINNER *****\n") : (cout << "***** BETTER LUCK NEXT TIME *****\n");
	}

	void Hangman::drawHangman(int guesses) const
	{
		cout << "       _______" << endl;

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

		for (int i = 0; i < (9 - guesses); ++i)
		{
			cout << "      |" << endl;
		}

		cout << "  ----------------------" << endl;
	}

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
		bool replay = false;
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
				break;
			case 3:
				while (replay)
				{
					playSinglePlayer();
					// prompt yes/no
					reset("Hangman");
				}
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				break;
			}
		}

		return 0;
	}
}


