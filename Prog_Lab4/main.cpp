#include <iostream>
#include "game.h"

using namespace std;

void game(char);
void select();
void PlayAgain();


int main()
{
	select();
	return 0;
}

void select()
{
	char PlayerChar = 0;

	do
	{
		system("cls");
		cout << "Select x or 0: ";
		cin >> PlayerChar;
	} while (PlayerChar != 'x' && PlayerChar != '0');

	game(PlayerChar);
}

void game(char PlayerChar)
{

	Game game = initGame(PlayerChar); // Инициализируем игру
	
	while (true)
	{
		if (!updateGame(&game))
		{
			updateDisplay(game);
			if (game.isUserTurn)
				userTurn(&game);
			else
				botTurn(&game);
			updateDisplay(game);
		}
		else
		{
			switch (game.status)
			{
			case BOT_WIN: cout << "You lose.\n";
				break;
			case USER_WIN: cout << "You win!\n";
				break;
			case NOT_WIN: cout << "Drow.\n";
				break;
			default: cout << "err";
				return;
			}

			PlayAgain();
			return;
		}
	}
}

void PlayAgain()
{
	cout << "0 - end game, 1 - play again.";
	bool PlayAgain;
	cin >> PlayAgain;
	if (PlayAgain) select();
	else return;
}