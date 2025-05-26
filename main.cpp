
// 1) Вывести на экран список студентов группы, которая содержит максимальное (в пределах потока) кол-во хорошистов и отличников *
// 2) Вывести на экран в порядке возрастания номера групп, в которых процент троечников и двоечников превышает заданное с клавиатуры значение
// 3) Вывести перечень всех фамилий студентов потока, группированный по размеру стипендии
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <windows.h>
int room = 0;
const int maxStudents = 30; //Кол-во студентов, что можно ввести.

using namespace std;

struct addInfoStudents
{
	string nonresident;
	int finance;
};

struct grades
{
	int exam[3];
	int test[5];
};

struct student
{
	string fullName;
	string gender;
	int group;
	int id;
	grades studGrades;
	addInfoStudents addInfo;
	int spended;
};

void createStudents(student students[], int &ch) {
    bool exit = false;
    while (!exit && room < maxStudents) {
        cout << "\tСтудент " << room + 1 << endl;
        cout << "Полное имя: ";
        cin.ignore();
        getline(cin, students[room].fullName);
        cout << endl;
        cout << "Пол: ";
        getline(cin, students[room].gender);
        cout << endl;
        cout << "Номер группы: ";
        cin >> students[room].group;
        cout << endl;
        cout << "Номер в списке группы: ";
        cin >> students[room].id;
        cout << endl;
        cin.ignore();
		cout << "Оценки за экзамен: ";
		for (short i = 0; i < 3; i++) {
			cin >> students[room].studGrades.exam[i];
		}
		cout << "Оценки за тест: ";
		for (short i = 0; i < 5; i++) {
			cin >> students[room].studGrades.test[i];
		}
    	cout << "Размер степендии: ";
    	cin >> students[room].spended;
        cout << endl;

        if (ch == 1) {
            cout << "\nВвести еще студент? [1-Да, 2-Нет]\n";
            int choice;
            cin >> choice;
            if (choice == 1) {
                exit = true;
                system("cls");
            }
            else if (choice == 2) {
                exit = false;
                system("cls");
            }
            else {
                cout << "Error" << endl;
            }
        } else {
            exit = true;
        }
        room++;
    }
}

void addTextfile(student students[]) {
	ifstream file("adddata.txt");
	string datafile;

	while(getline(file, datafile)) {
		istringstream iss(datafile);

		string fullName;
		string gender;
		short group;
		short id;
		short  examGrades1, examGrades2, examGrades3,
		testGrades1, testGrades2, testGrades3, testGrades4, testGrades5;
		short spended;

		if(iss >> fullName >> gender >> group >> id >> examGrades1 >> examGrades2 >> examGrades3 >>
		testGrades1 >>testGrades2 >> testGrades3 >> testGrades4 >> testGrades5) {
			students[room].fullName = fullName;
			students[room].gender = gender;
			students[room].group = group;
			students[room].id = id;
			students[room].studGrades.exam[0] = examGrades1;
			students[room].studGrades.exam[1] = examGrades2;
			students[room].studGrades.exam[2] = examGrades3;
			students[room].studGrades.test[0] = testGrades1;
			students[room].studGrades.test[1] = testGrades2;
			students[room].studGrades.test[2] = testGrades3;
			students[room].studGrades.test[3] = testGrades4;
			students[room].studGrades.test[4] = testGrades5;
			room++;
		}
		else {
			cerr << "Ошибка формата в строке: " << datafile << endl;
			system("pause"); return;
		}
	}
	file.close();
}

void data(student students[], int number) {
	for (int i = number; i < room; i++) {
		cout << "\tСтуден " << i + 1 << endl;
		cout << "Полное имя: " << students[i].fullName << endl;
		cout << "Пол(мужской, женский): " << students[i].gender << endl;
		cout << "Номер группы: " << students[i].group << endl;
		cout << "Номер в списках группы: " << students[i].id << endl;
		cout << "Оценки за экзамен: ";
		for (short j = 0; j < 3; j++) {
			cout << students[i].studGrades.exam[j] << " ";
		}
		cout << "\nОценки за тест: ";
		for (short j = 0; j < 5; j++) {
			cout << students[i].studGrades.test[j] << " ";
		}
		cout << endl;
		cout << "Степендия: " << students[i].spended << endl;
	}
	cout << endl;
}

void sortGroup(student students[]) {
	cout << "В списке есть студенты групп: ";
	int arr[maxStudents];
	for (short i = 0; i < room; i++)
	{
		arr[i] = students[i].group;
	}
	for (short i = 0; i < room - 1; i++)
	{
		for (short j = 0; j < room - i - 1; j++)
		{
			if (arr[j] > arr[j+1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	for (short i = 0; i < room; i++)
	{
		if (arr[i] != arr[i+1])
		{
			cout << arr[i] << ", ";
		}
	}
	cout << endl;
	cout << "Какую группу студентов вы хотите найти?\n" << endl;
	int numG; cin >> numG;
	//bool presStud = false;

	for (short i = 0; i < room; i++)
	{
		if (students[i].group == numG)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
		if ( students[i].group != numG && i == room - 1)
		{
			cout << "Номер группы не найден." << endl;
		}
	}
}

void topStudents(student students[]) {
	cout << "Сколько студентов вывести?" << endl;
	int topStud; //Кол-во лучших студентов, что выведет программа
	cin >> topStud;
	if (topStud >= 0 && topStud <= room)
	{
		double sred[maxStudents];
		int serialNum[maxStudents];
		for (short i = 0; i < room; i++)
		{
			double sum = 0;
			for (short j = 0; j < 5; j++)
			{
				sum += students[i].studGrades.test[j];
			}
			for (short j = 0; j < 3; j++)
			{
				sum += students[i].studGrades.exam[j];
			}
			sred[i] = sum / 8;
			serialNum[i] = i;
		}
		for (short i = 0; i < room; i++)
		{
			for (short j = 0; j < room - 1; j++)
			{
				if (sred[j] < sred[j + 1])
				{
					swap(sred[j], sred[j + 1]);
					swap(serialNum[j], serialNum[j + 1]);
				}
			}
		}
		cout << "\tТоп " << topStud << " лучших студнтов.\n" << endl;
		for (short i = 0; i < topStud; i++)
		{
			int buf = serialNum[i];
			cout << "Студен\n" << serialNum[i] + 1 << " Имя: " << students[buf].fullName << endl;
			cout << "Средний балл " << sred[i] << endl;
			cout << "Оценки ";
			for (short j = 0; j < 3; j++) {
				cout << students[buf].studGrades.exam[j] << " ";
			}
			cout << "\nОценки за экзамен: ";
			for (short j = 0; j < 5; j++) {
				cout << students[buf].studGrades.test[j] << " ";
			}
			cout << endl << endl;
		}
	}
	else {
		cout << "error" << endl;
	}
}

void numManAndWoman(student students[]) {
	short numMen = 0, numWomen = 0;
	for (short i = 0; i < room; i++)
	{
		if (students[i].gender == "Мужской" || students[i].gender == "мужской")
		{
			numMen++;
		}
		if (students[i].gender == "Женский" || students[i].gender == "женский")
		{
			numWomen++;
		}
	}
	cout << "Кол-во мужчины: " << numMen << endl;
	cout << "Кол-во женщины: " << numWomen << endl;
}

void grants(student students[]) {
	cout << "Студенты не получают стипендию.\n" << endl;
	for (short i = 0; i < room; i++)
	{
		short badMarks = 0;
		for (short j = 0; j < 3; j++)
		{
			if (students[i].studGrades.exam[j] <= 3)
			{
				badMarks++;
			}
		}
		for (short j = 0; j < 5; j++)
		{
			if (students[i].studGrades.test[j] <= 3)
			{
				badMarks++;
			}
		}
		if (badMarks == 8)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}
	cout << "Студенты, которые получили только «хорошо» и «отлично»." << endl;
	for (short i = 0; i < room; i++)
	{
		short buf = 0;
		short goodMarks = 0;
		for (short j = 0; j < 3; j++)
		{
			if (students[i].studGrades.exam[j] == 5)
			{
				buf++;
			}
			if (students[i].studGrades.exam[j] >= 4)
			{
				goodMarks++;
			}
		}
		for (short j = 0; j < 5; j++)
		{
			if (students[i].studGrades.test[j] == 5)
			{
				buf++;
			}
			if (students[i].studGrades.test[j] >= 4)
			{
				goodMarks++;
			}
		}
		if (goodMarks == 8 && buf != 8)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}
	cout <<"Студенты-отличники" << endl;
	for (short i = 0; i < room; i++)
	{
		short bestMarks = 0;
		for (short j = 0; j < 3; j++)
		{
			if (students[i].studGrades.exam[j] == 5)
			{
				bestMarks++;
			}
		}
		for (short j = 0; j < 5; j++)
		{
			if (students[i].studGrades.test[j] == 5)
			{
				bestMarks++;
			}
		}
		if (bestMarks == 8)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}

}

void numInList(student students[]) {
	cout << "Введите номер студента в список." << endl;
	short num; cin >> num;
	for (short i = 0; i < room; i++)
	{
		if (students[i].id == num)
		{
			int buf = room;
			room = i + 1;
			data(students, i);
			room = buf;
		}
	}
}

void textFile(student students[]) {
	ofstream file("data.txt");
	if (file.is_open()) {
		file << "\tCтуденты:\n";
		for (short i = 0; i < room; i++) {
			file << "Студент: " << i + 1 << "\t";
		}
		file << "\nИмя:\t";
		for (short i = 0; i < room; i++) {
			file << students[i].fullName << "\t\t";
		}
		file << "\nПол:\t\t";
		for (short i = 0; i < room; i++) {
			file << students[i].gender << "\t\t";
		}
		file << "\nНомер группы:\t";
		for (short i = 0; i < room; i++) {
			file << students[i].group << "\t\t";
		}
		file << "\nНомер:\t\t";
		for (short i = 0; i < room; i++) {
			file << students[i].id << "\t\t";
		}
		file << "\nОценки за экзамен:\t";
		for (short i = 0; i < room; i++) {
			for (short j = 0; j < 3; j++) {
				file << students[i].studGrades.exam[j] << " ";
			}
			file << "\t\t";
		}
		file << "\nОценки за тест:\t";
		for (short i = 0; i < room; i++) {
			for (short j = 0; j < 5; j++) {
				file << students[i].studGrades.test[j] << " ";
			}
			file << "\t";
		}
		file <<"\nСтепендия:\t";
		for (short i = 0; i < room; i++) {
			file <<students[i].spended <<"\t\t";
		}
		file << endl;
		file.close();
	}
	else {
		cout << "error" << endl;
	}
}

// void dormitory(student students[]) {
// 	cout << "\tВведите дополнительную информацию о студенте" << endl;
// 	cout << "Студент - иностранный студент? [Да/Нет]" << endl;
// 	cout << "Семейный доход." << endl;
// 	for (short i = 0; i < room; i++) {
// 		cout << "Студент " << i + 1 << endl;
// 		cin >> students[i].addInfo.nonresident;
// 		cin >> students[i].addInfo.finance;
// 	}
// 	short income = 10000; //Мин. доход
// 	for (short i = 0; i < room; i++)
// 	{
// 		if ((students[i].addInfo.nonresident == "Да" || students[i].addInfo.nonresident == "да") && students[i].addInfo.finance <= income)
// 		{
// 			int buf = room;
// 			room = i + 1;
// 			students[i].addInfo.nonresident;
// 			students[i].addInfo.finance;
// 			cout << endl;
// 			data(students, i);
// 			room = buf;
// 		}
// 	}
// }

int main() {
	struct student students[maxStudents];
	setlocale(LC_ALL, "RU");
	system("chcp 65001");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true)
	{
		cout << "\n[1]Ввод студента." << endl;
		cout << "[2]Внесение изменений в список." << endl;
		cout << "[3]Отображает все данные студента." << endl;
		cout << "[4]Показать информацию обо всех студентах в группе N." << endl;
		cout << "[5]Отображение самых успешных студентов со средним показателем с самым высоким рейтингом за последнюю сессию." << endl;
		cout << "[6]Отображая количество учеников мужского и женского пола." << endl;
		cout << "[7]Отображение данных о студентах - хорошистов и отличников;" << endl;
		cout << "[8]Отображение данных о студентах, у которых есть номер в списке. - k" << endl;
		cout << "[9]Ввод студента из файла" << endl;
		cout << "[10]Вывод данных в текстовый файл" << endl;
		// cout << "[10]IDZ#1" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:system("cls");  createStudents(students, choice); break;
		case 2:
			system("cls");
			cout << "Какой номер студента вы хотите изменить?" << endl;
			int num;
			cin >> num;
			num--;
			system("cls");
			if (num >= 0 && num < maxStudents)
			{
				int buf = room;
				room = num;
				createStudents(students, choice);
				room = buf;
			}
			else {
				cout << "error" << endl;
			}
			break;
		case 3: system("cls"); data(students, 0); break;
		case 4: system("cls"); sortGroup(students); break;
		case 5:system("cls"); topStudents(students); break;
		case 6: system("cls"); numManAndWoman(students); break;
		case 7: system("cls"); grants(students); break;
		case 8: system("cls"); numInList(students); break;
		case 9: system("cls"); addTextfile(students); break;
		case 10: system("cls"); textFile(students); break;

		//case 10: system("cls"); dormitory(students); break;
		default: system("cls"); cout << "error" << endl; break;
		}
	}
}




