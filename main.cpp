#define _CRT_SECURE_NO_WARNINGS
#include "hangman.h"
#include "wordlib.h"

using namespace hangman;
using namespace std;

int main()
{
	Hangman *game = new Hangman();
	game->run();

	return 0;
}