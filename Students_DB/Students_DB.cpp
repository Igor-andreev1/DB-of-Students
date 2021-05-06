
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
	ofstream fileWrite;
	ifstream fileRead;

	int curLine = 0;

	string tLine; // Временная перменная для записи строки из файла

public:

	/// <summary>
	/// Создает БД студентов открытую на запись, и проверяет успешность открытия
	/// </summary>
	void openToWrite()
	{
		fileWrite.open("StudentsData.txt");

		if (!(fileWrite.is_open()))
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
	/// Открывает файл для чтения и проверяет успешность открытия
	/// </summary>
	void openToRead()
	{
		fileRead.open("StudentsData.txt");

		if (!(fileRead.is_open()))
		{
			cout << "\nФайл не был открыт для чтения !!!\n";
			system("pause");
		} // Проверка на открытие файла

	}

	/// <summary>
	/// Записывает в файл данные о студенте из класса Student
	/// </summary>
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

	void printInfo(int startPos, int endPos)
	{
		curLine = 0;

		cout << "\nДанные о студенте:\n";

		while (getline(fileRead, tLine))
		{
			if (startPos == 1)
			{
				if (curLine < endPos)
				{
					cout << tLine;
					cout << endl;
				}
			}
			else
			{
				if ((curLine >= startPos) && (curLine < endPos))
				{
					cout << tLine;
					cout << endl;
				}
			}
			
			curLine++;
		}
	}

	/// <summary>
	/// Ищет в файле строку с введенным ФИО
	/// </summary>
	/// <param name="name1">  Имя  </param>
	/// <param name="name2">  Фамилия  </param>
	/// <param name="name3">  Отчество  </param>
	/// <returns>Возвращает целое число -  номер строки с необходимой информацией</returns>
	int searchData(string name1, string name2, string name3)
	{

		openToRead();

		string fullLine = name1 + ' ' + name2 + ' ' + name3; // Введенное ФИО с пробелами

		while (getline(fileRead, tLine)) 
		{ 
			curLine++;
			if (tLine.find(fullLine) != string::npos) 
			{
				return curLine;
			}
		}

	}

	/// <summary>
	/// Функция посика номера зачётной книжки в файле
	/// </summary>
	/// <param name="bookNumber"> Номер зачётной книжки</param>
	void searchData(string bookNumber)
	{

	}

	~FileManager()
	{
		fileWrite.close();
		fileRead.close();
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
			openToWrite();
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

				printInfo(searchData(tFullName.firstName, tFullName.secondName, tFullName.thirdName) , 8 ); // Поиск строки с ФИО  нужного студента и отображение информации о нём
				system("pause");
				system("cls");
				return 1;

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