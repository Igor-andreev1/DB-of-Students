
// Защита от ввода (попробовать сломать всё)
// Поправить отображение информации в printInfo (через if\switch curLine)
// Посмотреть, где можно использовать конструктор
// Добавить сортировку студентов (case 4)
// Добавить отображение успеваемости (инд. задание)


#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

const int SESSIONNUMBER = 2; // Кол-во сессий

const int SUBJECTNUMBER = 2; // Кол-во предметов


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
		cout << "\n\nВведите ФИО студента -> ";
		cin >> fullName.firstName;
		cin.ignore();
		cin >> fullName.secondName;
		cin.ignore();
		cin >> fullName.thirdName;
		cin.ignore();
		cout << endl;

		cout << "Введите дату рождения ->";
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

		for (int i = 0; i < SESSIONNUMBER; i++)
		{
			cout << "Введите для " << i + 1 << " сессии:\n";

			for (int j = 0; j < SUBJECTNUMBER; j++)
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

	int curLine; // Переменная для запоминания номера строки файла

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
	/// Записывает в файл данные о студенте, взятые из класса Student
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

		for (int i = 0; i < SESSIONNUMBER; i++)
		{
			fileWrite << "Сессия номер " << i + 1;
			fileWrite << endl;

			for (int j = 0; j < SUBJECTNUMBER; j++)
			{
				fileWrite << subjects[i][j].name << " Оценка - " << subjects[i][j].mark;
				fileWrite << endl;
			}
		}
	}

	/// <summary>
	/// Выводит в консоль данные из файла от startPos до endPos строки
	/// </summary>
	/// <param name="startPos"> начало вывода данных </param>
	/// <param name="endPos"> конец вывода данных </param>
	void printInfo(int startPos, int endPos)
	{
		openToRead();

		curLine = 0;

		if (fileRead.is_open())
		{
			fileRead.seekg(0, ios::beg);

			while (getline(fileRead, tLine))
			{

				if ((curLine >= startPos - 1) && (curLine < endPos))
				{

					cout << tLine << endl;

				}

				curLine++;
			}

			fileRead.close();
		}
		else
		{
			cout << "\n Файл закрыт для чтения!!!\n";
		}

	}

	/// <summary>
	/// Выводит на экран информацию о результатах выбранной сессии
	/// </summary>
	/// <param name="sessionNumber"> Номер сессии </param>
	void PrintSessionInfo(int sessionNumber)
	{
		string fullLine = "Сессия номер ";
		int tNumberLine;
	

		fullLine += to_string(sessionNumber); // Получаем строку типа:  Сессия номер x

		tNumberLine = searchData(fullLine); // Ищем номер строки в файле

		cout << "\nДанные по " << sessionNumber << " сесии:\n";

		printInfo(tNumberLine + 1, (tNumberLine + SUBJECTNUMBER)); 


	}

	/// <summary>
	/// Ищет в файле строку с введенным ФИО
	/// </summary>
	/// <param name="name1">  Имя  </param>
	/// <param name="name2">  Фамилия  </param>
	/// <param name="name3">  Отчество  </param>
	/// <returns>Возвращает целое число -  номер искомой строки, если найдено, в противном случае -1 </returns>
	int searchData(string name1, string name2, string name3)
	{

		openToRead();

		curLine = 0;

		string fullLine = name1 + ' ' + name2 + ' ' + name3; // Введенное ФИО с пробелами

		if (fileRead.is_open())
		{
			fileRead.seekg(0, ios::beg);

			while (getline(fileRead, tLine))
			{

				curLine++;

				if (tLine.find(fullLine) != string::npos)
				{
					fileRead.close();
					return curLine;
				}
			}
		}
		else
		{
			cout << "\nФайл закрыт для чтения!!!\n";
			return -1;
		}
	}

	/// <summary>
	/// Ищет в файле строку по введенной строке
	/// </summary>
	/// <param name="bookNumber"> Строка, которую нужно найти </param>
	/// <returns> Возвращает целое число - номер искомой строки, если найдено, в противном случае -1 </returns>
	int searchData(string fullLine)
	{
		openToRead();

		curLine = 0;

		if (fileRead.is_open())
		{
			fileRead.seekg(0, ios::beg);

			while (getline(fileRead, tLine))
			{

				curLine++;

				if (tLine.find(fullLine) != string::npos)
				{
					fileRead.close();
					return curLine;
				}
			}
		}
		else
		{
			cout << "\nФайл закрыт для чтения!!!\n";
			return -1;
		}
	}

	~FileManager()
	{

		if (!(fileWrite.is_open()))
		{
			fileWrite.close();
		}
		if (!(fileRead.is_open()))
		{
			fileRead.close();
		}

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
				int indicator; // Переменная проверки ввода

				cout << "\nВведите ФИО -> ";
				cin >> tFullName.firstName;
				cin.ignore();
				cin >> tFullName.secondName;
				cin.ignore();
				cin >> tFullName.thirdName;
				cout << endl;

				indicator = searchData(tFullName.firstName, tFullName.secondName, tFullName.thirdName); // Поиск строки с ФИО  нужного студента 

				if (indicator == -1)
				{
					cout << "\nТакой студент не был найден. Проверьте правильность ввода и повторите попытку\n";
					system("pause");
					goto A;
				}

				cout << "\nДанные о студенте:\n";

				printInfo(indicator, 8);

			B:
				cout << "\nВыберите номер сессии -> ";
				cin >> menu;
				cout << endl;

				if ((menu < 1) && (menu > SESSIONNUMBER))
				{
					cout << "\nОшибка ввода, повторите попытку\n";
					system("pause");
					system("cls");
					goto B;
				}

				PrintSessionInfo(menu);
			C:
				cout << "\n\nВыберите действие:\n";
				cout << "\n1. Выбрать другую сессию\n2. Вернуться на главный экран\n";
				cout << "Ваш выбор -> ";
				cin >> menu;
				cout << endl;

				if (menu == 1)
				{
					goto B;
				}
				else if (menu == 2)
				{
					system("cls");
					return 1;
				}
				else
				{
					cout << "\nОшибка ввода повторите попытку!!!\n";
					system("pause");
					goto C;
				}
			}
			case 2:
			{
				int indicator; // Переменная проверки ввода

				cout << "\nВведите номер зачётной книжки -> ";
				cin >> tRecordBookNumber;
				cout << endl;

				indicator = searchData(tRecordBookNumber);

				if (indicator == -1)
				{
					cout << "\nТакой номер не был найден. Проверьте правильность ввода и повторите попытку\n";
					system("pause");
					goto A;
				}

				cout << "\nДанные о студенте:\n";

				printInfo((indicator - 6), 8);
			D:
				cout << "\nВыберите номер сессии -> ";
				cin >> menu;
				cout << endl;

				if ((menu < 1) && (menu > SESSIONNUMBER))
				{
					cout << "\nОшибка ввода, повторите попытку\n";
					system("pause");
					system("cls");
					goto D;
				}

				PrintSessionInfo(menu);
			E:
				cout << "\n\nВыберите действие:\n";
				cout << "\n1. Выбрать другую сессию\n2. Вернуться на главный экран\n";
				cout << "Ваш выбор -> ";
				cin >> menu;
				cout << endl;

				if (menu == 1)
				{
					goto D;
				}
				else if (menu == 2)
				{
					system("cls");
					return 1;
				}
				else
				{
					cout << "\nОшибка ввода повторите попытку!!!\n";
					system("pause");
					goto E;
				}
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
/// Тело программы. Зацикливает выбор опций в объекте меню
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