
#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

const int sessionCount = 2; // Кол-во сессий

const int subjectsCount = 2; // Кол-во предметов

struct BirthDataTemplate
{
	int day;
	int month;
	int year;
};

struct SubjectTemplate
{
	int session;
	string name;
	int mark;
};

struct FullNameTemplate
{
	string firstName;
	string secondName;
	string thirdName;
};

/// <summary>
/// Хранит в себе все необходимые данные о студенте
/// </summary>
class Student
{

	friend class FileManager;

	FullNameTemplate fullName;
	BirthDataTemplate birthData;
	int startYear;
	string faculty;
	string department;
	string group;
	string recordBookNumber;
	char sex;
	SubjectTemplate subjects[9][10];

public:

	void addStudentData()
	{
		cout << "\n\nВведите ФИО студента -> ";
		cin >> fullName.firstName;
		cin.ignore();
		cin >> fullName.secondName;
		cin.ignore();
		cin >> fullName.thirdName;
		cin.ignore();
		cout << endl;

		cout << "\nВведите дату рождения ->";
		cin >> birthData.day;
		cin.ignore();
		cin >> birthData.month;
		cin.ignore();
		cin >> birthData.year;
		cout << endl;

		cout << "Введите год поступления -> ";
		cin >> startYear;
		cout << endl;

		cout << "Введите факультет -> ";
		cin >> faculty;
		cout << endl;

		cout << "Введите кафедру -> ";
		cin >> department;
		cout << endl;

		cout << "Введите группу -> ";
		cin >> group;
		cout << endl;

		cout << "Введите номер зачётной книжки -> ";
		cin >> recordBookNumber;
		cout << endl;

		cout << "Введите пол (одна буква, м/ж) -> ";
		cin >> sex;
		cout << endl;

		for (int i = 0; i < sessionCount; i++)
		{
			cout << "Введите для " << i + 1 << " сессии:\n";

			for (int j = 0; j < subjectsCount; j++)
			{
				cout << "Название предмета -> ";
				cin >> subjects[i][j].name;
				cout << endl;

				cout << "Оценку -> ";
				cin >> subjects[i][j].mark;
				cout << endl;
			}
		}

	}

	Student()
	{
		cout << "\nСоздание объекта класса Student\n";
	}

	~Student()
	{
		cout << "\nУдаление объекта класса Student\n";
	}

};

/// <summary>
/// Создаёт файл и выполняет необходимые действия с ним
/// </summary>
class FileManager : public Student
{
	ofstream fileWrite;
	ifstream fileRead;

public:

	void createFile()
	{
		fileWrite.open("StudentsData.txt");
		fileRead.open("StudentsData.txt");
	}

	void deleteFile()
	{
		fileWrite.close();
		fileRead.close();
	}

	void writeInFile()
	{
		addStudentData();

		fileWrite << fullName.firstName << ' ' << fullName.secondName << ' ' << fullName.thirdName;
		fileWrite << endl;

		fileWrite << birthData.day << '.' << birthData.month << '.' << birthData.year;
		fileWrite << endl;

		fileWrite << startYear;
		fileWrite << endl;

		fileWrite << faculty;
		fileWrite << endl;

		fileWrite << department;
		fileWrite << endl;

		fileWrite << group;
		fileWrite << endl;

		fileWrite << recordBookNumber;
		fileWrite << endl;

		fileWrite << sex;
		fileWrite << endl;

		for (int i = 0; i < sessionCount; i++)
		{
			fileWrite << i + 1;
			fileWrite << endl;

			for (int j = 0; j < subjectsCount; j++)
			{
				fileWrite << subjects[i][j].name;
				fileWrite << endl;
				fileWrite << subjects[i][j].mark;
				fileWrite << endl;
			}
		}
	}

	FileManager()
	{
		cout << "\nСоздаём объект класса FileManager\n";
	}

	~FileManager()
	{
		cout << "\nУдаление объекта класса FileManager\n";
	}
};

/// <summary>
/// Класс меню. Отвечает за выбор пользователем опций
/// </summary>
class MenuPattern : public FileManager
{

	int menu; // Переменная выбора опции

public:

	int startMenu()
	{
		menu = 0;
		cout << "\nВыберите действие:\n";
		cout << "\n1. Создать базу данных студентов\n2. Записать данные студента в базу данных\n3. Узнать данные студента\n4. Сортировать студентов по успеваемости\n5. Выйти из программы\n";
		cout << "Ваш выбор -> ";
		cin >> menu;
		cout << endl;
		switch (menu)
		{
		case 1:
		{
			createFile();
			cout << "\nФайл успешно создан!!!\n\n";
			system("pause");
			system("cls");
			return 1;
		}
		case 2:
		{
			writeInFile();
			cout << endl;
			system("pause");
			system("cls");
			return 1;
		}
		case 3:
		{

		}
		case 4:
		{

		}
		case 5:
		{
			deleteFile();
			system("cls");
			return 0;
		}
		default:
		{
			cout << "\nОшибка ввода!!!!\n";
			system("pause");
			system("cls");
			return 1;
		}
		}
	}

	MenuPattern()
	{
		cout << "\nСоздание объекта класса Menu\n";
		menu = 0;
	}

	~MenuPattern()
	{
		cout << "\nУдаление объекта Menu\n";
	}

};

int main()
{

	int bugFinder = 1;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MenuPattern Menu;

	while (bugFinder != 0)
	{

		bugFinder = Menu.startMenu();

	}

}