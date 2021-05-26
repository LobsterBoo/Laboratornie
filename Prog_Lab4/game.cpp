#include <iostream>
#include <ctime> // ���������� ��� �������
#include "game.h"

using namespace std;

bool BotFirstTurn = 0;
short Drow = 0;  // ����������-������� ��� �����, ���� ��������� �������� 9, �� ���� ������������� ������ 

Game initGame(char PlayerChar)
{
	srand(time(NULL)); // ����������� ��� ����������� �������

	Game game;  // ������� ���� � ������ Game
	game.status = PLAY; 
	
	game.userChar = PlayerChar;

	PlayerChar == 'x' ? game.botChar = '0' : game.botChar = 'x'; // ��� �������� �������� �� ������ ������

	for (char i = 0; i < 3; i++) 
		for (char j = 0; j < 3; j++)
			game.board[i][j] = ' '; // ������� �����

	(rand() % 2) ? game.isUserTurn = false : game.isUserTurn = true; // ������ ��� ������ ��������, � ������ 50%
	(game.isUserTurn == false) ? BotFirstTurn = 0  : BotFirstTurn = 1 ; // ����������, ����������� ��� ������� ���� ���� � �����

	return game;
}

void updateDisplay(const Game game)
{
	system("cls"); // ����� ������� ���� ����� ������� ������� �����

	std::cout << "\ta\tb\tc" <<                                                                        //	a	b	c
		"\n\n1\t" << game.board[0][0] << "\t" << game.board[0][1] << "\t" << game.board[0][2] <<       // 1	x	0	0
		"\n\n2\t" << game.board[1][0] << "\t" << game.board[1][1] << "\t" << game.board[1][2] <<       // 2	0	x	0
		"\n\n3\t" << game.board[2][0] << "\t" << game.board[2][1] << "\t" << game.board[2][2] << "\n"; // 3	0	0	x

	return;
}

void botTurn(Game* game)
{
	Drow++;
	short a = 0, b = 0, c = 0; // ���������� ��� �������� 

	if (BotFirstTurn) // ������ ��� ���� � �����
	{ 
		game->board[1][1] = game->botChar;
		BotFirstTurn = 0;
		return;
	}


	// ��������� �������� ���������
	for (int i = 0; i < 3; i++) 
	{  
		if (game->board[i][i] == game->userChar) a++;  // ���������� a ������� ���������� �������� ������

		if (game->board[i][i] == ' ')
		{
			b++; // b ������� ������ ������
			c = i; // c ����������� ����� ������ ������
		}
	}
	if ((b == 1) && (a == 2)) // ���� �� ��������� ���� ���� ������ ����� � ��� ��������� �������, �� ��� �������� ���� ����
	{
		game->board[c][c] = game->botChar; 
		return;
	}

	a = 0; // �������� ����� ������� ���������
	b = 0;

	for (int i = 0; i < 3; i++) // ��������� �������������� ��������� ��� �� �������
	{ 
		if (game->board[i][2-i] == game->userChar) a++; // ��������� i �� ������, ���� "�����������" ������ � �������

		if (game->board[i][2-i] == ' ')
		{
			b++;
			c = i;
		}
	}
	if ((b == 1) && (a == 2))
	{
		game->board[c][2-c] = game->botChar;
		return;
	}

	// C������ � ������
	for (int i = 0; i < 3; i++)
	{
		a = 0;
		b = 0;
		c = 0;
		short d = 0;

		for (int j = 0; j < 3; j++) // ������� ������� 
		{

			if (game->board[j][i] == ' ') c=j; //������� ���� �� � ������� ������ � ���������� ��� �����
			if (game->board[j][i] == game->userChar)
			{
				b++; //������� ���������������� ��������
			}
			if ((b == 2) && (c != 0)) // ���� ���� 2 ������� ������ � ������, �� �����
			{
				game->board[c][i] = game->botChar;
				return;
			}

			if (game->board[i][j] == game->userChar) 
			{
				a++; //������� ���������������� ��������
			}
			if (game->board[i][j] == ' ') d = j;
			if ((a == 2) && (d != 0))
			{
				game->board[i][d] = game->botChar;
				return;
			}
		}
	}

	do // ���� ��� �� ����� ���� ������ �� ���������, �� ��� ����������� ��������� �������
	{
		a = rand() % 3;
		b = rand() % 3;

		if (game->board[a][b] == ' ')
		{
			game->board[a][b] = game->botChar;
			return;
		}

	} while (true);

}

void userTurn(Game* game)
{
	Drow++;
	cout << "Players turn, please enter cell position (a 1): ";

	while (true) // ����������� ����, ������� ��������� ������ ����� ������� ���� �� ������
	{

		char letter;
		short numeral;

		cin >> letter >> numeral;
			
		switch ((char)letter) // ������ ����� �� ����������, ��� ��������� � ������� 
		{
		case 'a': letter = 0;
			break;
		case 'b': letter = 1;
			break;
		case 'c': letter = 2;
			break;
		default:
			cout << "Incorrect letter entered!\n";
			continue;
		}

		switch ((short)numeral) // �������� ������� �� ���������� ����, �.�. ��������� � ������� ���� � 0.
		{
		case 1:
		case 2: 
		case 3:
			numeral--;
			break;
		default:
			cout << "Number entered incorrectly!\n";
			continue;
		}

		if (game->board[numeral][letter] == ' ') // ���� ����� ������ �� ������ ����, �� ������ ��� 
		{
			game->board[numeral][letter] = game->userChar;
			return;
		}
		else std::cout << "Occupied place!\n";
	}
}

bool updateGame(Game* game)
{
	// ����� ������ �������� � ������� � ������
	for (int i = 0; i < 3; i++) 
	{ 
		if ( ( game->board[i][0] == 'x') || (game->board[i][0] == '0') ) // ���� ������ ������ � �������/������ �� ������
		{																 // �� �������� ���/� ���������
			if ((game->board[0][i] == game->board[1][i]) && (game->board[1][i] == game->board[2][i]) && (game->board[0][i] != ' ') ) // ���� ��� ������� ����� ����� �����
			{
				if (game->board[0][i] == game->userChar) game->status = USER_WIN; // �� �������, ��� ��� �� ������, � ������ ������ � ����������
				else game->status = BOT_WIN;
				Drow = 0;
				return true;
			}

			if ( (game->board[i][0] == game->board[i][1]) && (game->board[i][1] == game->board[i][2]) && (game->board[0][i] != ' ') )
			{
				if (game->board[i][0] == game->userChar) game->status = USER_WIN; 
				else game->status = BOT_WIN; 
				Drow = 0;
				return true;
			}
		
		}
	}

	if ((game->board[1][1] == 'x') || (game->board[1][1] == '0') ) // ���� �������� ���� �� ������, �� ������ ��������� ��� ���������
	{ 
		if ((game->board[0][0] == game->board[1][1]) && (game->board[0][0] == game->board[2][2])) 
		{
			if (game->board[1][1] == game->userChar) game->status = USER_WIN;
			else game->status = BOT_WIN;
			Drow = 0;
			return true;
		}

		if ((game->board[0][2] == game->board[1][1]) && (game->board[2][0] == game->board[1][1]))
		{
			if (game->board[1][1] == game->userChar) game->status = USER_WIN;
			else game->status = BOT_WIN;
			Drow = 0;
			return true;
		}
	}

	if (Drow == 9)
	{
		game->status = NOT_WIN;
		Drow = 0; // �������� �� ������, ���� ����� ������� ������� ��� ���.
		return true;
	}

	game->isUserTurn = !game->isUserTurn; // �������� ���
	return false;
}