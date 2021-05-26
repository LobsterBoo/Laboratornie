#include <conio.h>
#include <iostream>
#include <math.h>
using namespace std;
#define PI 3.141592654
#define true 1
#define false 0
int main()
{
	setlocale(LC_ALL, "rus");
	float a,
		b,
		x,
		y,
		e,
		valid;
	system("cls");
	printf("Введите значение параметра a: ");
	scanf_s("%f", &a);
	printf("Введите значение параметра b: ");
	scanf_s("%f", &b);
	printf("Введите значение аргумента x: ");
	scanf_s("%f", &x);
	valid = true;
	if (x <= a)
	{
		y = pow((pow(cos(x), 3) + 0, 9 * tan(x)), 2.3);
	}
	else if (x < b)
	{
		y = exp(x) / (sqrt(sinh(x)) + 8, 9 * x + 9);
	}
	else
	{
		if (x > 0)
			y = fabs((log(x) + cos(pow(x, 2.1)) - 1, 2 * x)) * pow(x, 4.6);
		else
			valid = false;
	}
	if (valid)
		printf("Значение функции y=%e\n", y);
	else
		printf("Недопустимое значение аргумента");
	printf("Нажмите любую клавишу...");
	_getch();
	return 0;
}