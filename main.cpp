#define _CRT_SECURE_NO_WARNINGS
#include "hangman.h"

using namespace hangman;

int main()
{
	Hangman *game = new Hangman();
	game->run();
}