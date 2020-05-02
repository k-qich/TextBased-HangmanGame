#include <ios>
#include <iostream>
#include <limits>
#include "hangman.h"

using std::ostream;
using std::streamsize;
using std::numeric_limits;
using std::cin;
using std::cout;
using std::endl;

namespace hangman
{
	Hangman::Hangman()
	{
		guesses = 6;
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

	void Hangman::displayBanner()
	{
		cout << "***************************************************************" << endl;
		cout << "*  __________________________________________________________  *" << endl;
		cout << "* |                                                          | *" << endl;
		cout << "* |----------------------------------------------------------| *" << endl;
		cout << "* |      _    _                                              | *" << endl;
		cout << "* |     | |  | |                                             | *" << endl;
		cout << "* |     | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __       | *" << endl;
		cout << "* |     |  __  |\/ _` | '_ \\ \/ _` | '_ ` _ \\ \/ _` | '_ \\      | *" << endl;
		cout << "* |     | |  | | (_| | | | | (_| | | | | | | (_| | | | |     | *" << endl;
		cout << "* |     |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|     | *" << endl;
		cout << "* |                          __/ |                           | *" << endl;
		cout << "* |                         |___/                            | *" << endl;
		cout << "* |----------------------------------------------------------| *" << endl;
		cout << "* |__________________________________________________________| *" << endl;
		cout << "*                                                              *" << endl;
		cout << "****************************************************************" << endl;
	}

	void Hangman::displayRules()
	{
		cout << "  Objective: Guess the hidden word correctly before the stickman is hanged!" << endl;
		cout << "\n  Players may guess a single character at a time or the entire word if they think they know what the word is." << endl;
		cout << "  Each incorrect guess will reduce the number of available guesses that depends on the selected difficulty. 6(Easy), 4(Normal), 3(Hard)" << endl;
		cout << "  A player loses when they run out of guesses and the stickman is fully hanged." << endl;
	}

	void Hangman::drawHangman()
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
			cout << "      |      \/|\\" << endl;
		}
		else if (guesses >= 3)
		{
			cout << "      |      \/|" << endl;
		}
		else if (guesses >= 2)
		{
			cout << "      |       |" << endl;
		}

		if (guesses >= 6)
		{
			cout << "      |      \/ \\" << endl;
		}
		else if (guesses >= 5)
		{
			cout << "      |      \/" << endl;
		}

		for (int i = 0; i < (9 - guesses); ++i)
		{
			cout << "      |" << endl;
		}

		cout << "  ----------------------" << endl;
	}

	void Hangman::displayWord()
	{
		
	}

	int Hangman::run()
	{
		int choice;
		displayBanner();

		switch (choice = menu())
		{
			case 1:
				displayRules();
				break;
			case 2:
				break;
			case 3:
				cout << "\n  *******************************************" << endl;
				drawHangman();
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				break;
		}

		return 0;
	}
}


