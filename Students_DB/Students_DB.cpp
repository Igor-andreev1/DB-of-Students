
#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

const int sessionCount = 2; // Кол-во сессий

const int subjectsCount = 2; // Кол-во предметов

int studentsCount = 0;


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

	/// <summary>
	/// Записывает данные о студенте, считываемые с клавиатуры
	/// </summary>
	void addStudentData()
	{

		studentsCount++;

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

};


/// <summary>
/// Создаёт файл, выполняет необходимые действия с ним и закрывает при разрушении
/// </summary>
class FileManager : public Student
{
	ofstream file;

public:

	/// <summary>
	/// Создает БД студентов открытую на запись и чтение, и проверяет успешность открытия
	/// </summary>
	void createFile()
	{
		file.open("StudentsData.txt");

		if (!(file.is_open()))
		{
			cout << "\nФайл не был создан!!!\n";
		} // Проверка на открытие файла
		else
		{
			cout << "\nФайл успешно создан!\n\n";
		}

		system("pause");
	}

	/// <summary>
	/// Записывает в файл данные о студенте из класса Student
	/// </summary>
	void writeInFile()
	{
		addStudentData();

		file << fullName.firstName << ' ' << fullName.secondName << ' ' << fullName.thirdName;
		file << endl;

		file << birthData.day << '.' << birthData.month << '.' << birthData.year;
		file << endl;

		file << startYear;
		file << endl;

		file << faculty;
		file << endl;

		file << department;
		file << endl;

		file << group;
		file << endl;

		file << recordBookNumber;
		file << endl;

		file << sex;
		file << endl;

		for (int i = 0; i < sessionCount; i++)
		{
			file << i + 1;
			file << endl;

			for (int j = 0; j < subjectsCount; j++)
			{
				file << subjects[i][j].name;
				file << endl;
				file << subjects[i][j].mark;
				file << endl;
			}
		}
	}

	void searchData(string name1, string name2, string name3)
	{

	}

	void searchData(string bookNumber)
	{

	}

	~FileManager()
	{
		file.close();
	}
};

/// <summary>
/// Отвечает за управление БД
/// </summary>
class MenuPattern : public FileManager
{
	string tRecordBookNumber; // Переменная поиска по зачётке
	FullNameTemplate tFullName; // Переменная поиска по ФИО

	int menu; // Переменная выбора опции

public:

	/// <summary>
	/// Создаёт консольный интерфейс меню
	/// </summary>
	/// <returns>Возвращает 1 до тех пор пока пользователь не решит выйти</returns>
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
		A:
			system("cls");
			cout << "\nВыберите дейтсвие:\n";
			cout << "\n1. Поиск по ФИО\n2. Поиск по номеру зачётной книжки\n";
			cout << "Ваш выбор -> ";
			cin >> menu;
			cout << endl;

			switch (menu)
			{
			case 1:
			{
				cout << "\nВведите ФИО -> ";
				cin >> tFullName.firstName;
				cin.ignore();
				cin >> tFullName.secondName;
				cin.ignore();
				cin >> tFullName.thirdName;
				cout << endl;
				searchData(tFullName.firstName, tFullName.secondName, tFullName.thirdName);

			}
			case 2:
			{
				cout << "\nВведите номер зачётной книжки -> ";
				cin >> tRecordBookNumber;
				cout << endl;
				searchData(tRecordBookNumber);
			}
			default:
			{
				cout << "\nОшибка ввода повторите попытку!!!\n";
				system("pause");
				goto A;
			}
			}
		}
		case 4:
		{

		}
		case 5:
		{
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

};

/// <summary>
/// Тело программы. Зацикливает выбор опций в  объекте меню
/// </summary>
/// <returns>Возвращает 0 при успешном завершении</returns>
int main()
{

	int indicator = 1;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MenuPattern Menu;

	while (indicator != 0)
	{

		indicator = Menu.startMenu();

	}

	return 0;
}