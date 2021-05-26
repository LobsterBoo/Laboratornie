МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №3<br/> по дисциплине "Программирование"
<br/>

студентки 1 курса группы ПИ-б-о-191(2)  
Cофии Щегловой
направления подготовки 09.03.04 "Программная инженерия"  
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2019

## Лабораторная работа №3
Дешифровка текста из изображения\
\
**Цель:** 
1. Закрепить навыки разработки программ использующих операторы цикла.
2. Закрепить навыки разработки программ использующих массивы.
3. Освоить методы подключения сторонних библиотек.
\
**Ход работы:**\
**1\.** В лабораторной работе мне необходимо было работать с изображениями в формате bmp. Для этого необходимо скачать библиотеку с [github](https://github.com/marc-q/libbmp).\
**2\.** После создания нового проекта, к нему необходимо добавить файл libbmp.cpp, расположенный в скаченной нами библиотеке.\
**3\.** Я скачала картинку, соответствующую номеру моего варианта (мой номер 29, но так как картинок всего 15, я взяла 14ю).\
![Картинка 14го варианта](pic14.bmp)\
*рис.1: Картинка моего варианта*\
Для работы с картинкой нам необходим ключ, благодаря которому мы поймем направление движения по пикселям. Мой ключ: 00g 00b 00r 10g 10b 10r 01g 01b.
Исходя из него, я поняла, что мне необходимо двигаться слева на право, сверху в низ. 
**4\.** Для получения текста из картинки я написала следующий код:
```c++
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
```
**5\.** После запуска программы мы видим ответ в консоли:\
![Результат работы программы](scrinshots/1.PNG)\
*Результат работы программы*\
В консоли написано следующие: \
Franklin Pierce (November 23, 1804 Ц October 8, 1869) was the 14th president of the United States (1853Ц1857), a northern Democrat who saw the abolitionist movement as a fundamental threat to the unity of the nation. He alienated anti-slavery groups by championing and signing the KansasЦNebraska Act and enforcing the Fugitive Slave Act, yet he failed to stem conflict between North and South, setting the stage for Southern secession and the American Civil War.
Pierce was born in New Hampshire, and served in the U.S. House of Representatives and the Senate until he resigned from the Senate in 1842. His private law practice was a success, and he was appointed New Hampshire's U.S. Attorney in 1845. He took part in the MexicanЦAmerican War as a brigadier general in the Army. He was seen by Democrats as a compromise candidate uniting northern and southern interests and was nominated as the party's candidate for president on the 49th ballot at the 1852 Democratic National Convention. He and running mate William R. King easily defeated the Whig Party ticket of Winfield Scott and William A. Graham in the 1852 presidential election.
As president, Pierce simultaneously attempted to enforce neutral standards for civil service while also satisfying the diverse elements of the Democratic Party with patronage, an effort which largely failed and turned many in his party against him. He was a Young America expansionist who signed the Gadsden Purchase of land from Mexico and led a failed attempt to acquire Cuba from Spain. He signed trade treaties with Britain and Japan, while his Cabinet reformed their departments and improved accountability, but these successes were overshadowed by political strife during his presidency. His popularity declined sharply in the Northern states after he supported the KansasЦNebraska Act, which nullified the Missouri Compromise, while many whites in the South continued to support him. Passage of the act led to violent conflict over the expansion of slavery in the American West. Pierce's administration was further damaged when several of his diplomats issued the Ostend Manifesto calling for the annexation of Cuba, a document which was roundly criticized. He fully expected to be renominated by the Democrats in the 1856 presidential election, but was abandoned by his party and his bid failed. His reputation in the North suffered further during the American Civil War as he became a vocal critic of President Abraham Lincoln.
Pierce was popular and outgoing, but his family life was a grim affair, with his wife Jane suffering from illness and depression for much of her life.[1] All of their children died young, their last son being gruesomely killed in a train accident while the family was traveling shortly before Pierce's inauguration. He was a heavy drinker for much of his life, and he died of cirrhosis of the liver in 1869. Historians and scholars generally rank Pierce as one of the worst and least memorable U.S. Presidents.
\
**Вывод:** в процессе выполнения данной лабораторной работы я научилась подключать к проекту файлы из сторонних скаченных библиотек, работать с рисунками формата bpm и декодировать информацию из пикселей изображения.
