#include <iostream>
#include "libbmp.h"

using namespace std;
char Massage[10000]; // Полученый текст будем хронить в большом массиве

// Намер текущего бита и байта будем хронить в глобальных переменных
short current_byte = 0;
short current_bit = 7;  

bool is_end = false;

void add_new_bit(char); // Функция, извлекающая новый бит информации из картинки


int main()
{
	BmpImg image;
	image.read("pic14.bmp");

	// Мой ключ: 00g 00b 00r 10g 10b 10r 01g 01b
	// Движемся слева в право, сверху в низ
	for (int y = 0; y <= image.get_height() - 1; y++) 
	{
		for (int x = 0; x <= image.get_width() - 1; x++)
		{
			short bit_green = image.green_at(x, y) & 0b1; // Получаем информацию из каждого цвета
			short bit_blue = image.blue_at(x, y) & 0b1;
			short bit_red = image.red_at(x, y) & 0b1;

			add_new_bit( (char)bit_green ); // При вызове функций кастуем число в чар
			add_new_bit( (char)bit_blue );
			add_new_bit( (char)bit_red );

			if (is_end) break; // Выходим из цикла, если встречаем конец текста
		}
		if (is_end) break;
	}
	cout << Massage<<"\n";
}

void add_new_bit(char bit)
{
	if (is_end)
		return;

	bit = bit << current_bit;
	Massage[current_byte] = Massage[current_byte] | bit;
	current_bit--;

	if (current_bit < 0)
	{
		if (Massage[current_byte] == '\0')
			is_end = true;

		current_bit = 7;
		current_byte++;
	}
}