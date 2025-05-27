
// 1) Вывести на экран список студентов группы, которая содержит максимальное (в пределах потока) кол-во хорошистов и отличников *
// 2) Вывести на экран в порядке возрастания номера групп, в которых процент троечников и двоечников превышает заданное с клавиатуры значение
// 3) Вывести перечень всех фамилий студентов потока, группированный по размеру стипендии *
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <windows.h>
int room = 0;
const int maxStudents = 30; //Кол-во студентов, что можно ввести.

using namespace std;



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
	int spended;
};

void createStudents(student students[], int& ch) {
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
			if (choice == 2) {
				exit = true;
				system("cls");
			}
			else if (choice == 1) {
				exit = false;
				system("cls");
			}
			else {
				cout << "Error" << endl;
			}
		}
		else {
			exit = true;
		}
		room++;
	}
}

int parseGroup(const string& input) {
	string numStr;
	for (char c : input) {
		if (isdigit(c)) {
			numStr += c;
		}
	}
	if (numStr.empty()) return 0; // или выбросить исключение
	return stoi(numStr);
}

void addTextfile(student students[]) {
	ifstream file("adddata.txt");
	if (!file.is_open()) {
		cerr << "Ошибка открытия файла!" << endl;
		return;
	}

	string lines[7]; // Увеличили размер до 7 строк на студента
	int lineCounter = 0;

	while (getline(file, lines[lineCounter % 7])) { // Изменили на 7
		lineCounter++;

		if (lineCounter % 7 == 0) { // Проверяем каждые 7 строк
			if (room >= maxStudents) {
				cerr << "Достигнут лимит студентов!" << endl;
				break;
			}

			student& s = students[room];

			// Заполнение данных
			s.fullName = lines[0];
			s.gender = lines[1];

			try {
				s.group = parseGroup(lines[2]);
			}
			catch (...) {
				cerr << "Ошибка формата группы: " << lines[2] << endl;
				continue;
			}

			try {
				s.id = stoi(lines[3]);
			}
			catch (...) {
				cerr << "Ошибка ID в строке: " << lines[3] << endl;
				continue;
			}

			// Оценки за экзамены
			istringstream iss_exam(lines[4]);
			for (int i = 0; i < 3; i++) {
				if (!(iss_exam >> s.studGrades.exam[i])) {
					cerr << "Ошибка оценок экзамена" << endl;
					break;
				}
			}

			// Оценки за тесты
			istringstream iss_test(lines[5]);
			for (int i = 0; i < 5; i++) {
				if (!(iss_test >> s.studGrades.test[i])) {
					cerr << "Ошибка оценок теста" << endl;
					break;
				}
			}

			// Добавляем стипендию
			try {
				s.spended = stoi(lines[6]);
			}
			catch (...) {
				cerr << "Ошибка стипендии в строке: " << lines[6] << endl;
				continue;
			}

			room++;
		}
	}

	if (lineCounter % 7 != 0) {
		cerr << "Файл содержит неполные данные!" << endl;
	}

	file.close();
}



void data(student students[], int number) {
	for (int i = number; i < room; i++) {
		cout << "\tСтудент" << i + 1 << endl;
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
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	for (short i = 0; i < room; i++)
	{
		if (arr[i] != arr[i + 1])
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
		if (students[i].group != numG && i == room - 1)
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
	cout << "Студенты-отличники" << endl;
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
		file << "\nСтепендия:\t";
		for (short i = 0; i < room; i++) {
			file << students[i].spended << "\t\t";
		}
		file << endl;
		file.close();
	}
	else {
		cout << "error" << endl;
	}
}

void stependiaStudent(student students[]) {
	int uniqueStipends[maxStudents];
	int stipendCount = 0;
	// Собираем уникальные размеры стипендий
	for (short i = 0; i < room; i++) {
		bool exists = false;
		for (short j = 0; j < stipendCount; j++) {
			if (students[i].spended == uniqueStipends[j]) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			uniqueStipends[stipendCount++] = students[i].spended;
		}
	}
	// Сортируем размеры стипендий по убыванию
	for (short i = 0; i < stipendCount - 1; i++) {
		for (short j = 0; j < stipendCount - i - 1; j++) {
			if (uniqueStipends[j] < uniqueStipends[j + 1]) {
				swap(uniqueStipends[j], uniqueStipends[j + 1]);
			}
		}
	}
	// Выводим студентов, группируя по стипендии
	for (short i = 0; i < stipendCount; i++) {
		int currentStipend = uniqueStipends[i];
		cout << "Степендию в размере " << currentStipend << " получают:" << endl;

		for (short j = 0; j < room; j++) {
			if (students[j].spended == currentStipend) {
				cout << " - " << students[j].fullName << endl;
			}
		}
		cout << endl;
	}
}



void printStudentsInGroup(student students[], int group) {
	cout << "\nСтуденты группы " << group << ":\n";
	for (int i = 0; i < room; i++) {
		if (students[i].group == group) {
			cout << students[i].fullName << " (ID: " << students[i].id << ")\n";
			cout << "Оценки за экзамены: ";
			for (int j = 0; j < 3; j++) cout << students[i].studGrades.exam[j] << " ";
			cout << "\nОценки за тесты: ";
			for (int j = 0; j < 5; j++) cout << students[i].studGrades.test[j] << " ";
			cout << "\nСтипендия: " << students[i].spended << "\n\n";
		}
	}
}

void findGroupsWithThreshold(student students[], bool findThrees, float threshold) {
	// Максимальный возможный номер группы
	const int MAX_GROUP = 10000; // Можно увеличить при необходимости
	int totalCount[MAX_GROUP] = { 0 };
	int lowGradeCount[MAX_GROUP] = { 0 };
	bool groupExists[MAX_GROUP] = { false };

	// Собираем статистику по группам
	for (int i = 0; i < room; i++) {
		int group = students[i].group;
		if (group >= MAX_GROUP) continue; // На всякий случай

		groupExists[group] = true;
		totalCount[group]++;

		// Проверяем, есть ли низкие оценки
		bool hasLowGrade = false;

		// Проверяем экзамены
		for (int j = 0; j < 3; j++) {
			if ((findThrees && students[i].studGrades.exam[j] == 3) ||
				(!findThrees && students[i].studGrades.exam[j] == 2)) {
				hasLowGrade = true;
				break;
			}
		}

		// Если еще не нашли, проверяем тесты
		if (!hasLowGrade) {
			for (int j = 0; j < 5; j++) {
				if ((findThrees && students[i].studGrades.test[j] == 3) ||
					(!findThrees && students[i].studGrades.test[j] == 2)) {
					hasLowGrade = true;
					break;
				}
			}
		}

		if (hasLowGrade) {
			lowGradeCount[group]++;
		}
	}

	// Выводим результаты
	cout << "Группы с процентом " << (findThrees ? "троечников" : "двоечников")
		<< " выше " << threshold << "%:\n";
	bool foundAny = false;

	for (int group = 0; group < MAX_GROUP; group++) {
		if (groupExists[group] && totalCount[group] > 0) {
			float percentage = (static_cast<float>(lowGradeCount[group]) / totalCount[group]) * 100;
			if (percentage > threshold) {
				cout << "Группа " << group << ": " << percentage << "% "
					<< (findThrees ? "троечников" : "двоечников") << "\n";
				printStudentsInGroup(students, group);
				foundAny = true;
			}
		}
	}

	if (!foundAny) {
		cout << "Групп с процентом " << (findThrees ? "троечников" : "двоечников")
			<< " выше " << threshold << "% не найдено.\n";
	}
}

void popuskiStudent(student students[]) {
	short choice;
	cout << "\tВыберите пункт\n[1] Процент двоечников\n[2] Процент троечников\n";
	cin >> choice;

	float threshold;
	cout << "Введите процентный порог: ";
	cin >> threshold;

	switch (choice) {
	case 1:
		system("cls");
		findGroupsWithThreshold(students, false, threshold);
		break;
	case 2:
		system("cls");
		findGroupsWithThreshold(students, true, threshold);
		break;
	default:
		system("cls");
		cout << "Ошибка ввода";
		system("pause");
		break;
	}
}
int main() {
	struct student students[maxStudents];
	setlocale(LC_ALL, "RU");
	system("chcp 65001");
	// SetConsoleCP(1251);
	// SetConsoleOutputCP(1251);
	while (true)
	{
		cout << "\n[1]Ввод студента." << endl;
		cout << "[2]Внесение изменений в список." << endl;
		cout << "[3]Отображает все данные студента." << endl;
		cout << "[4]Показать информацию обо всех студентах в группе N." << endl;
		cout << "[5]Отображение самых успешных студентов со средним показателем с самым высоким рейтингом за последнюю сессию." << endl;
		cout << "[6]Отображая количество учеников мужского и женского пола." << endl;
		cout << "[7]Отображение данных о студентах - хорошистов и отличников;" << endl;
		cout << "[8]Вывести информацию о студентах по группам - зависящий от степендии" << endl;
		cout << "[9]Процент" << endl;
		cout << "[10]Ввод студента из файла" << endl;
		cout << "[11]Вывод данных в текстовый файл" << endl;
		// cout << "[10]IDZ#1" << endl;
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:system("cls");  createStudents(students, choice); break;
		case 2:
			system("cls");
			cout << "Какой номер студента вы хотите изменить или удалить?" << endl;
			int num;
			cin >> num;
			num--;
			system("cls");
			if (num >= 0 && num < room)
			{
				cout << "Выберите действие: " << endl;
				cout << "1. Изменить студента" << endl;
				cout << "2. Удалить студента" << endl;
				int action;
				cin >> action;
				if (action == 1)
				{
					int buf = room;
					room = num;
					createStudents(students, choice);
					room = buf;
				}
				else if (action == 2) {
					cout << "Вы уверены, что хотите удалить студента " << students[num].fullName << "? [1-Да, 2-Нет]" << endl;
					int confirm;
					cin >> confirm;
					if (confirm == 1) {
						for (short j = num; j < room - 1; j++) {
							students[j] = students[j + 1];
						}
						room--;
						cout << "Студент " << students[num].fullName << " удален." << endl;
					}
					else {
						cout << "Удаление отменено." << endl;
					}
				}
				break;
			}

		case 3: system("cls"); data(students, 0); break;
		case 4: system("cls"); sortGroup(students); break;
		case 5:system("cls"); topStudents(students); break;
		case 6: system("cls"); numManAndWoman(students); break;
		case 7: system("cls"); grants(students); break;
		case 8: system("cls"); stependiaStudent(students); break;
		case 9: system("cls"); popuskiStudent(students); break;
		case 10: system("cls"); addTextfile(students); break;
		case 11: system("cls"); textFile(students); break;
		default: system("cls"); cout << "error" << endl; break;
		}
	}
}