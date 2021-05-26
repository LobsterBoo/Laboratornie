МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ  
Федеральное государственное автономное образовательное учреждение высшего образования  
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"  
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ  
Кафедра компьютерной инженерии и моделирования
<br/><br/>

### Отчёт по лабораторной работе №5<br/> по дисциплине "Программирование"
<br/>

студента 1 курса группы ПИ-б-о-191(2) 
Щегловой Софии
направления подготовки 09.03.04 "Программная инженерия"  
<br/>

<table>
<tr><td>Научный руководитель<br/> старший преподаватель кафедры<br/> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br/><br/>

Симферополь, 2020

## Лабораторная работа №5
Работа с текстовыми файлами\
\
**Цель:** 
1. Научиться работать с текстовыми файлами;
2. Закрепить навыки работы со структурами.
\
**Ход работы:**\
**1\.** [Скачиваем](https://github.com/rebeccabilbro/titanic/tree/master/data)  файл train.csv, с информацией  о пассажирах Титаника.\
**2\.** Создаем структуру Passenger, содержащею  необходимые полня для чтения записей из файла train.csv.\
**3\.** Создаем свою программу, способную считать и переформатировать  данные из файла train.csv.
**4\.** Сохраняем результат обработки данных в новый [текстовый файл](/answer.txt) результаты подсчета некоторых характеристик.\
Рассчитанные характеристики:
                
| Характеристика  | Результат |
| ------------- | ------------- |
| Общее кол-во выживших | 342  |
| Кол-во выживших пассажиров 1 класса  | 136  |
| Кол-во выживших пассажиров 2 класса  | 87  |
| Кол-во выживших пассажиров 3 класса  | 119  |
| Кол-во выживших женщин  | 233  |
| Кол-во выживших мужчин  | 109  |
| Средний возраст мужчин  | 27.2366  |
|Средний возраст женщин  | 28.8376  |
| Средний возраст пассажиров  | 28.3241  |
|Штат, в котором село больше всего пассажиров | Southampton  |
                
Список id несовершеннолетних пассажиров: 8, 10, 11, 15, 17, 23, 25, 40, 44, 51, 59, 60, 64, 69, 72, 79, 85, 87, 112, 115, 120, 126, 139, 148, 157, 164, 165, 166, 172, 173, 183, 184, 185, 194, 206, 209, 221, 234, 238, 262, 267, 279, 283, 298, 306, 308, 330, 334, 341, 349, 353, 375, 382, 387, 390, 408, 420, 434, 436, 446, 447, 449, 470, 480, 481, 490, 501, 505, 531, 533, 536, 542, 543, 550, 551, 575, 619, 635, 643, 645, 684, 687, 690, 692, 721, 722, 732, 747, 751, 752, 756, 765, 778, 781, 782, 788, 789, 792, 803, 804, 814, 820, 825, 828, 831, 832, 842, 845, 851, 853, 854, 870, 876.\

Код программы:
```c++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int Last; // Глобальная переменная для звязи main и функции прочтения

enum Sex
{
	Female,
	Male
};

struct Passenger // Cтруктура пассажира
{
	int Id;
	bool Is_survived;
	int Class;
	string Name;
	Sex sex;
	double Age;
	int SibSp;
	int Parch;
	string Ticket;
	float Fare;
	string Cabin;
	char Embarked;
};

int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

string staite(int Embarked_C_counter, int Embarked_Q_counter, int Embarked_S_counter)
{
	short c_em_max = (max(Embarked_C_counter, max(Embarked_Q_counter, Embarked_S_counter))); // Cчитаем большее кол-во из 3х штатов
	if (c_em_max == Embarked_C_counter)
		return "Cherbourg\n";
	else if (c_em_max == Embarked_S_counter)
		return "Southampton\n";
	else if (c_em_max == Embarked_Q_counter)
		return "Queenstown\n";
}

string read(string String, std::string del) // Функция для прочтения строки 
{
	int start = Last;
	int end = String.find(del, start);

	Last = end + del.size();

	return String.substr(start, end - start);
}


float default_age(string age) // Функция, заменяющая отсутствующий возраст на -1
{
	if (age != "") return stod(age);

	return -1;
}

int main()
{
	setlocale(LC_ALL, "rus");
	vector<Passenger> passengers;
	ifstream fin("train.csv");
	string String;


	getline(fin, String, '\r'); // \r задаем как разделитель
	while (getline(fin, String, '\r'))
	{
		Last = 0;
		Passenger passenger;

		passenger.Id = stoi(read(String, ","));
		passenger.Is_survived = stoi(read(String, ","));
		passenger.Class = stoi(read(String, ",\""));
		passenger.Name = read(String, "\",");
		passenger.sex = read(String, ",") == "male" ? Male : Female;
		passenger.Age = default_age(read(String, ","));
		passenger.SibSp = stoi(read(String, ","));
		passenger.Parch = stoi(read(String, ","));
		passenger.Ticket = read(String, ",");
		passenger.Fare = stod(read(String, ","));
		passenger.Cabin = read(String, ",");
		passenger.Embarked = read(String, " ")[0];


		passengers.push_back(passenger);
	}

	// Создаем переменные для подсчета
	int survivor_counter = 0;
	int survivor_1class_counter = 0;
	int survivor_2class_counter = 0;
	int survivor_3class_counter = 0;
	int survivor_woman_counter = 0;
	int survivor_man_counter = 0;
	int man_counter = 0; // Число людей, для подсчета среднего возраста
	int woman_counter = 0;
	int Embarked_S_counter = 0; // Счетчик пассажиров из штата
	int Embarked_C_counter = 0; 
	int Embarked_Q_counter = 0;

	double age_man = 0, age_woman = 0;

	vector<short> children_id; // id детей будем записывать в вектор


	for (int i = 0; i < passengers.size(); i++)
	{
		// Для начала проверим, есть ли возраст у пассажира и не является ли он ребенком
		if ((passengers[i].Age != -1) && (passengers[i].Age < 18)) children_id.push_back(passengers[i].Id); 

		// Потом определяем штат посадки
		if (passengers[i].Embarked == 'C') Embarked_C_counter++; //Cherbourg
			else if (passengers[i].Embarked == 'S') Embarked_S_counter++; //Southampton 
			else if (passengers[i].Embarked == 'Q') Embarked_Q_counter; //Queenstown

		if (passengers[i].Is_survived) // Если пассажир выжил
		{
			survivor_counter++; // увеличиваем счетчик выживших

			if (passengers[i].Class == 1) survivor_1class_counter++; // И счетчик выживших из определенного класса
			else if (passengers[i].Class == 2) survivor_2class_counter++;
			else if (passengers[i].Class == 3) survivor_3class_counter++;

			if (passengers[i].sex == Female) survivor_woman_counter++;
			else survivor_man_counter++;

			if (passengers[i].Age >= 0) // если возраст есть
			{

				if (passengers[i].sex == Female)
				{
					age_woman += passengers[i].Age;
					woman_counter++;
				}
				else
				{
					age_man += passengers[i].Age;
					man_counter++;
				}
			}
		}
	}

	// Начинаем записывать ответ
	ofstream fout("answer.txt");

	fout << "Общее кол-во выживших: " << survivor_counter << '\n';
	fout << "Кол-во выживших из 1 класса: " << survivor_1class_counter << '\n';
	fout << "Кол-во выживших из 2 класса: " << survivor_2class_counter << '\n';
	fout << "Кол-во выживших из 3 класса: " << survivor_3class_counter << '\n';
	fout << "Кол-во выживших женщин: " << survivor_woman_counter << '\n';
	fout << "Кол-во выживших мужчин: " << survivor_man_counter << '\n';
	fout << "Средний возраст мужчин: " << age_man / man_counter << '\n';
	fout << "Средний возраст женщин: " << age_woman / woman_counter << '\n';
	fout << "Средний возраст пассажиров: " << (age_man + age_woman) / (man_counter + woman_counter) << '\n';
	fout << "Штат, в котором село больше всего пассажиров: " << staite(Embarked_C_counter, Embarked_Q_counter, Embarked_S_counter);
	fout << "Список идентификаторов несовершеннолетних пассажиров: ";
	for (short i = 0; i < children_id.size(); i++) fout << children_id[i] << ", ";

	fout.close();
	fin.close(); // Закрываем файлы
}
```

\
**Вывод:** В процессе выполнения этой лабораторной работы я научилась получать и записывать информацию из текстовых файлов и закрепила на практике навыки работы со структурами.