<p align="center">  МИНИСТЕРСТВО НАУКИ И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙСКОЙ ФЕДЕРАЦИИ<br/>
Федеральное государственное автономное образовательное учреждение высшего образования
 <br/>
 "КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  <br/>
  ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ <br/>
    Кафедра компьютерной инженерии и моделирования<br/></p>

<br/>

### <p align="center">Отчёт по лабораторной работе №4 <br/> по дисциплине "Программирование"</p>

<br/>

<p align="center">студентки 1 курса группы ПИ-б-о-191(2)
Щегловой Софии <br/>
направления подготовки 09.03.04 "Программная инженерия"

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>


<br/>

<p align="center">Симферополь, 2020</p>

**Цель работы:** **1.**   Закрепить навыки работы с перечислениями;
**2.**  Закрепить навыки работы с структурами;
**3.**  Освоить методы составления многофайловых программ.

​<p align="center">**Ход работы**</p>

**1.** Создала  файл game.cpp, содержащий реализацию основных функций игры.

**2.** Создала заголовочный файл game.h . Он необходим для связи главного и вспомогательного файлов. Добавила защиту от повторного включения файла.*;

**3.** Написала файл main.cpp, реализующий игру «Иксики-нолики» используя функции описанные в вспомогательном файле.

![Конец игры](1.png)

   **Код main.cpp**:

   ```c++
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

  	```

**Код game.h**:

   ```c++
#pragma once //защита от повторного включения файла

/* Состояния игры */
enum Status {
	PLAY,            // Игра продолжается
	USER_WIN,        // Игрок победил
	BOT_WIN,         // Бот победил
	NOT_WIN          // Ничья. Победителя нет, но и на поле нет свободной ячейки
};

struct Game {
	char board[3][3];  // Игровое поле
	bool isUserTurn;  // Чей ход. Если пользователя, то isUserTurn = true
	char userChar;    // Символ которым играет пользователь
	char botChar;     // Символ которым играет бот
	Status status;
};



/**
* Выполняет следующие действия:
*  1. Очищает игровое поле заполняя его пробелами
*  2. Случайным образом определяет чей ход
*  3. Устанавливает символ для Игрока (Задаётся параметром userChar)
*  4. Устанавливает символ для бота
*  5. Возвращает заполненную структуру
*/
Game initGame(char userChar);


/**
* Выполняет следующие действия:
*  1. Очищает экран
*  2. Отображает содержимое игрового поля.
*/
void updateDisplay(const Game game);



/**
* Выполняет ход бота. В выбранную ячейку устанавливается символ которым играет бот.
* Бот должен определять строку, столбец или диагональ в которой у игрока больше всего иксиков/ноликов и ставить туда свой символ.
* Если на поле ещё нет меток, бот должен ставить свой знак в центр. В остальных случаях бот ходит рандомно.
*/
void botTurn(Game* game);



/**
* Функция отвечает за ход игрока. Если игрок вводит не допустимые
* значения, ругнуться и попросить ввести заново
*/
void userTurn(Game* game);



/**
* Функция определяет как изменилось состояние игры после последнего хода.
* Функция сохраняет новое состояние игры в структуре game и передаёт ход другому
* игроку.
* Функция возвращает true, если есть победитель или ничья, иначе false.
*/
bool updateGame(Game* game);
  	```
  
  **Код game.cpp**:

   ```c++
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

  	```


**Вывод:** В процессе выполнения лабораторной работы я получила практические навыки в создании многофайловой программы и закрепила навыки работы с перечислениями и структурами.