#include <iostream>
#include <ctime> // Подключаем для рандома
#include "game.h"

using namespace std;

bool BotFirstTurn = 0;
short Drow = 0;  // Переменная-счетчик для ходов, если принимает значение 9, то игра заканчивается ничьей 

Game initGame(char PlayerChar)
{
	srand(time(NULL)); // Прописываем для обеспечения рандома

	Game game;  // Создаем игру с именем Game
	game.status = PLAY; 
	
	game.userChar = PlayerChar;

	PlayerChar == 'x' ? game.botChar = '0' : game.botChar = 'x'; // Бот получает отличный от игрока символ

	for (char i = 0; i < 3; i++) 
		for (char j = 0; j < 3; j++)
			game.board[i][j] = ' '; // Очищаем доску

	(rand() % 2) ? game.isUserTurn = false : game.isUserTurn = true; // Первый ход доется рандомно, с шансом 50%
	(game.isUserTurn == false) ? BotFirstTurn = 0  : BotFirstTurn = 1 ; // Переменная, необходимая для первого хода бота в центр

	return game;
}

void updateDisplay(const Game game)
{
	system("cls"); // После каждого хода стоит стереть прошлую доску

	std::cout << "\ta\tb\tc" <<                                                                        //	a	b	c
		"\n\n1\t" << game.board[0][0] << "\t" << game.board[0][1] << "\t" << game.board[0][2] <<       // 1	x	0	0
		"\n\n2\t" << game.board[1][0] << "\t" << game.board[1][1] << "\t" << game.board[1][2] <<       // 2	0	x	0
		"\n\n3\t" << game.board[2][0] << "\t" << game.board[2][1] << "\t" << game.board[2][2] << "\n"; // 3	0	0	x

	return;
}

void botTurn(Game* game)
{
	Drow++;
	short a = 0, b = 0, c = 0; // Переменные для подсчета 

	if (BotFirstTurn) // Первый ход бота в центр
	{ 
		game->board[1][1] = game->botChar;
		BotFirstTurn = 0;
		return;
	}


	// Проверяем основную диагональ
	for (int i = 0; i < 3; i++) 
	{  
		if (game->board[i][i] == game->userChar) a++;  // Переменная a считает количество символов игрока

		if (game->board[i][i] == ' ')
		{
			b++; // b считает пустые клетки
			c = i; // c запониманет адрес пустой ячейки
		}
	}
	if ((b == 1) && (a == 2)) // Если на диагонали есть одно пустое место и два вражеских символа, то бот поставит туда свой
	{
		game->board[c][c] = game->botChar; 
		return;
	}

	a = 0; // обнуляем после прошлых подсчетов
	b = 0;

	for (int i = 0; i < 3; i++) // Проверяем второстепенную диагональ тем же методом
	{ 
		if (game->board[i][2-i] == game->userChar) a++; // Вычетамем i из двойки, чтоб "перевернуть" индекс в массиве

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

	// Cтолбцы и строки
	for (int i = 0; i < 3; i++)
	{
		a = 0;
		b = 0;
		c = 0;
		short d = 0;

		for (int j = 0; j < 3; j++) // Сначала столбцы 
		{

			if (game->board[j][i] == ' ') c=j; //Смотрим есть ли в столбце пробел и запоминаем его адрес
			if (game->board[j][i] == game->userChar)
			{
				b++; //Счетчик пользовательских символов
			}
			if ((b == 2) && (c != 0)) // Если есть 2 символа игрока и пробел, то ходим
			{
				game->board[c][i] = game->botChar;
				return;
			}

			if (game->board[i][j] == game->userChar) 
			{
				a++; //Счетчик пользовательских символов
			}
			if (game->board[i][j] == ' ') d = j;
			if ((a == 2) && (d != 0))
			{
				game->board[i][d] = game->botChar;
				return;
			}
		}
	}

	do // Если бот не нашел куда ходить по алгоритму, то ход совершается случайным образом
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

	while (true) // Бесконечный цикл, который прервется только после верного хода от игрока
	{

		char letter;
		short numeral;

		cin >> letter >> numeral;
			
		switch ((char)letter) // Меняем буквы на переменные, для адресации в массиве 
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

		switch ((short)numeral) // Вычетаем еденицу из полученных цивр, т.к. нумерация в массиве идес с 0.
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

		if (game->board[numeral][letter] == ' ') // Если игрок указал на пустое поле, то делаем ход 
		{
			game->board[numeral][letter] = game->userChar;
			return;
		}
		else std::cout << "Occupied place!\n";
	}
}

bool updateGame(Game* game)
{
	// Одним циклом проверим и столбцы и строки
	for (int i = 0; i < 3; i++) 
	{ 
		if ( ( game->board[i][0] == 'x') || (game->board[i][0] == '0') ) // Если первая клетка в столбце/строке не пустая
		{																 // То проверим его/её полностью
			if ((game->board[0][i] == game->board[1][i]) && (game->board[1][i] == game->board[2][i]) && (game->board[0][i] != ' ') ) // если все символы равны между собой
			{
				if (game->board[0][i] == game->userChar) game->status = USER_WIN; // То смотрим, что это за символ, и делаем выводы о победителе
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

	if ((game->board[1][1] == 'x') || (game->board[1][1] == '0') ) // Если середина поля не пустая, то просто проверяем обе диагонали
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
		Drow = 0; // Зануляем на случай, если игрок захочет сыграть еще раз.
		return true;
	}

	game->isUserTurn = !game->isUserTurn; // Передаем ход
	return false;
}