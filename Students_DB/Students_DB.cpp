
// Проверить вводы данных
// Добавить полное описание
// 
// Иcпользовать виртуальные функции
// Иcпользовать перегрузка операторов

// Сделать блок-схему
// Подготовить отчёт

#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <cstdio>

using namespace std;

const int SESSIONNUMBER = 2; // Кол-во сессий

const int SUBJECTNUMBER = 2; //  Макс. Кол-во предметов

const int DECREMENT = SESSIONNUMBER * (SUBJECTNUMBER + 1) + 8; // Обозначает кол-во строк отводимых для 1 студента

const int THIS_YEAR = 2021;

int mode = 0;

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
	SubjectTemplate subjects[SESSIONNUMBER][SUBJECTNUMBER];

	string subjectNames[SUBJECTNUMBER];

	int subjectsCount = 0;

	vector<string> booksData; // Вектор для хранения номеров зачётных книжек (необходим для проверки уникальности)

public:

	static int studentCount; // Счётчик студентов

	/// <summary>
	/// Записывает данные о студенте, считываемые с клавиатуры и заносит данные об их успеваемости по сесииям в массив векторов
	/// </summary>
	void addStudentData()
	{

		studentCount++; // Добавление нового студента

		check1:

		cout << "\n\nВведите ФИО студента (через пробел) -> ";
		cin >> fullName.firstName;
		cin.ignore();
		cin >> fullName.secondName;
		cin.ignore();
		cin >> fullName.thirdName;
		cin.ignore();
		cout << endl;

		if (nameValidation() == -1)
		{
			goto check1;
		}

		check2:

		cout << "Введите дату рождения (хх.хх.хххх) ->";
		cin >> birthData.day;
		cin.ignore();
		cin >> birthData.month;
		cin.ignore();
		cin >> birthData.year;
		cout << endl;

		if (birthDateValidation() == -1)
		{
			goto check2;
		}

		check3:

		cout << "Введите год поступления -> ";
		cin >> startYear;
		cout << endl;

		if (startYear < birthData.year)
		{
			cout << "\nВозможно вы ошиблись при вводе пожалуйста повторите попытку!!!\n";
			system("pause");
			cout << endl;
			goto check3;
		}

		cout << "Введите факультет -> ";
		cin >> faculty;
		cout << endl;

		cout << "Введите кафедру -> ";
		cin >> department;
		cout << endl;

		cout << "Введите группу -> ";
		cin >> group;
		cout << endl;

		check4:

		cout << "Введите номер зачётной книжки -> ";
		cin >> recordBookNumber;
		cout << endl;

		if (recordBookValidation() == -1)
		{
			goto check4;
		}

		check5:

		cout << "Введите пол (одна буква, м/ж, без нажатия enter) -> ";
		sex = _getch();

		if ((sex != 'м') && (sex != 'ж'))
		{
			cout << "\nНерпавильный ввод, пожалуйста повторите попытку\n";
			system("pause");
			goto check5;
		}

		cout << endl;
		cout << endl;

		for (int i = 0; i < SESSIONNUMBER; i++)
		{
			cout << "Для " << i + 1 << " сессии:\n";

			subjectsCount = 0;

			for (int j = 0; j < SUBJECTNUMBER; j++)
			{
				if (addSudjects(i, j) == 0)
				{
					for (int k = j; k < SUBJECTNUMBER; k++)
					{
						subjects[i][j].name = " ";
						subjects[i][j].mark = 0;
					}

					break;
				}

				subjectsCount++;
			}

			for (int k = 0; k < SUBJECTNUMBER; k++)
			{
				subjectNames[k] = " ";
			}
		}

	}

	/// <summary>
	/// Проверка правильности вода ФИО
	/// </summary>
	/// <returns>Возвращает -1 в случае ошибки, 0 - в случае корректного ввода</returns>
	int nameValidation()
	{
		string letter;

		if ((fullName.firstName.size() < 2) || (fullName.firstName.size() > 12))
		{
			cout << "\nВозможно вы ошиблись при вводе имени пожалуйста повторите попытку!!!\n";
			system("pause");
			cout << endl;
			return -1;
		}

		if ((fullName.secondName.size() < 2) || (fullName.firstName.size() > 12))
		{
			cout << "\nВозможно вы ошиблись при вводе имени пожалуйста повторите попытку!!!\n";
			system("pause");
			cout << endl;
			return -1;
		}

		if ((fullName.thirdName.size() < 2) || (fullName.firstName.size() > 12))
		{
			cout << "\nВозможно вы ошиблись при вводе имени пожалуйста повторите попытку!!!\n";
			system("pause");
			cout << endl;
			return -1;
		}

		for (int i = 0; i < 10; i++)
		{
			letter = to_string(i);

			if (fullName.firstName.find(letter) != string::npos)
			{
				cout << "\nВозможно вы ошиблись при вводе имени пожалуйста повторите попытку!!!\n";
				system("pause");
				cout << endl;
				return -1;
			}

			if (fullName.secondName.find(letter) != string::npos)
			{
				cout << "\nВозможно вы ошиблись при вводе имени пожалуйста повторите попытку!!!\n";
				system("pause");
				cout << endl;
				return -1;
			}

			if (fullName.thirdName.find(letter) != string::npos)
			{
				cout << "\nВозможно вы ошиблись при вводе имени пожалуйста повторите попытку!!!\n";
				system("pause");
				cout << endl;
				return -1;
			}
		}

		return 1;
	}

	/// <summary>
	/// Проверяет правильность ввода даты рождения
	/// </summary>
	/// <returns>Возвращает -1 в случае ошибки, 0 - в случае корректного ввода</returns>
	int birthDateValidation()
	{
		if ((birthData.day > 31) || (birthData.day < 0))
		{
			cout << "\nВозможно вы ошиблись при вводе даты пожалуйста повторите попытку!!!\n";
			system("pause");
			cout << endl;
			return -1;
		}

		if ((birthData.month > 12) || (birthData.month < 0))
		{
			cout << "\nВозможно вы ошиблись при вводе даты пожалуйста повторите попытку!!!\n";
			system("pause");
			cout << endl;
			return -1;
		}

		if ((birthData.year < 1900) || (birthData.year > THIS_YEAR))
		{
			cout << "\nВозможно вы ошиблись при вводе даты пожалуйста повторите попытку!!!\n";
			system("pause");
			cout << endl;
			return -1;
		}

		return 0;
	}

	/// <summary>
	/// Проверяет правильность ввода номера зачётной книжки (уникальность)
	/// </summary>
	/// <returns>Возвращает 0 в случае уникальности номера, -1 - если повторяется</returns>
	int recordBookValidation()
	{
		if (studentCount > 1)
		{
			for (int i = 0; i < booksData.size(); i++)
			{
				if (booksData[i] == recordBookNumber)
				{
					cout << "\nСтудент с таким номером уже существует, проверьте ввод и повторите попытку\n";
					system("pause");
					cout << endl;
					return -1;
				}
			}

			booksData.push_back(recordBookNumber);
			return 0;
		}
		else
		{
			booksData.push_back(recordBookNumber);
			return 0;
		}
	}

	/// <summary>
	/// Проверяет правильность ввода оценки
	/// </summary>
	/// <param name="i"></param>
	/// <param name="j"></param>
	/// <returns> Возвращает 0 в случае успешной проверки </returns>
	int markValidation(int i, int j)
	{
		if ((subjects[i][j].mark < 2) || (subjects[i][j].mark > 5))
		{
			cout << "\nОшибка ввода, повторите попытку!\n";
			system("pause");
			return -1;
		}

		if (!(isdigit(subjects[i][j].mark)) == 0)
		{
			cout << "\nОшибка ввода, повторите попытку!\n";
			system("pause");
			return -1;
		}

		return 0;
	}

	/// <summary>
	/// Добавляет название и оценку по одного предмета
	/// </summary>
	/// <param name="i"></param>
	/// <param name="j"></param>
	/// <returns> Возвращает 1 в случае успешного добавления </returns>
	int addSudjects(int i, int j)
	{
		int indicator;

	start:

		cout << "\n\nВыберите действие:\n";
		cout << "1. Добавить предмет\n2. Перейти к след. сессии\n";
		cout << "Ваш выбор -> ";
		cin >> indicator;
		cout << endl;

		if (indicator == 1)
		{
		checkSName:
			cout << "\nНазвание предмета -> ";
			cin.ignore();
			getline(cin, subjects[i][j].name);
			cout << endl;

			for (int k = 0; k < SUBJECTNUMBER; k++)
			{
				if (subjects[i][j].name == subjectNames[k])
				{
					cout << "\nПредмет с таким именем уже существует! Повторите попытку\n";
					goto checkSName;
				}
			}

			subjectNames[subjectsCount] = subjects[i][j].name;

		checkMark:

			cout << "Оценку -> ";
			cin >> subjects[i][j].mark;
			cout << endl;

			if (markValidation(i, j) == -1)
			{
				cout << "\nНерпавильный ввод, пожалуйста повторите попытку\n";
				system("pause");
				goto checkMark;
			}

			return 1;
		}
		else if (indicator == 2)
		{
			return 0;
		}
		else
		{
			cout << "\nОшибка ввода повторите попытку!\n";
			goto start;
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

	vector<int> v3; // Вектор, хранящий код троечников - младший разряд числа отвечает за номер сессии от 1 до SESSIONNUMBER, а остальные цифры - порядковый номер студента
	vector<int> v4; // Вектор, хранящий код хорошистов - младший разряд числа отвечает за номер сессии от 1 до SESSIONNUMBER, а остальные цифры - порядковый номер студента
	vector<int> v5; // Вектор, хранящий код отличников - младший разряд числа отвечает за номер сессии от 1 до SESSIONNUMBER, а остальные цифры - порядковый номер студента

	vector<string> oldData;

	friend class MenuPattern;

public:

	/// <summary>
	/// Создает БД студентов открытую на запись, и проверяет успешность открытия
	/// </summary>
	void openToWrite()
	{
		studentCount = 0;

		booksData.clear();
		v5.clear();
		v4.clear();
		v3.clear();

		fileWrite.open("StudentsData.txt");

		if (!(fileWrite.is_open()))
		{
			cout << "\nФайл не был создан!!!\n";
		} 
		else
		{
			cout << "\nФайл успешно создан!\n\n";
		}
	}

	/// <summary>
	/// Открывает файл для чтения и проверяет успешность открытия
	/// </summary>
	void openToRead(int mode)
	{
		switch(mode)
		{
		case 0:
		{
			fileRead.open("StudentsData.txt");

			if (!(fileRead.is_open()))
			{
				cout << "\nФайл не был открыт для чтения !!!\n";
				system("pause");
			} // Проверка на открытие файла

			break;
		}
		case 1:
		{
			fileRead.open("TemporaryStudentsData.txt");

			if (!(fileRead.is_open()))
			{
				cout << "\nФайл не был открыт для чтения !!!\n";
				system("pause");
			} // Проверка на открытие файла

			break;
		}
		}
	}

	/// <summary>
	/// Создаёт временный файл для записи
	/// </summary>
	void createNewTemporaryFile(int mode)
	{
		switch (mode)
		{
		case 0:
		{
			fileWrite.open("TemporaryStudentsData.txt");

			if (!(fileWrite.is_open()))
			{
				cout << "\nФайл не был создан!!!\n";
			} // Проверка на открытие файла

			break;
		}
		case 1:
		{
			fileWrite.open("StudentsData.txt");

			if (!(fileWrite.is_open()))
			{
				cout << "\nФайл не был создан!!!\n";
			} // Проверка на открытие файла

			break;
		}
		}
	}

	/// <summary>
	/// Записывает в файл данные о студенте, взятые из класса Student
	/// </summary>
	void writeInFile()
	{
		addStudentData();

		fileWrite << fullName.firstName << ' ' << fullName.secondName << ' ' << fullName.thirdName;
		fileWrite << endl;

		fileWrite << "Дата рождения - " << birthData.day << '.' << birthData.month << '.' << birthData.year;
		fileWrite << endl;

		fileWrite << "Год поступления - " << startYear;
		fileWrite << endl;

		fileWrite << "Факульет - " << faculty;
		fileWrite << endl;

		fileWrite << "Кафедра - " << department;
		fileWrite << endl;

		fileWrite << "Группа - " << group;
		fileWrite << endl;

		fileWrite << "Номер зачётной книжки - " << recordBookNumber;
		fileWrite << endl;

		fileWrite << "Пол - " << sex;
		fileWrite << endl;

		for (int i = 0; i < SESSIONNUMBER; i++)
		{
			fileWrite << "Сессия номер " << i + 1 << " Студента номер " << studentCount;
			fileWrite << endl;

			for (int j = 0; j < SUBJECTNUMBER; j++)
			{
				if (subjects[i][j].mark == 0)
				{
					fileWrite << endl;
				}
				else
				{
					fileWrite << subjects[i][j].name << " Оценка - " << subjects[i][j].mark;
					fileWrite << endl;
				}
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
		openToRead(mode);

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
	/// Выводит строку с веденным номером
	/// </summary>
	/// <param name="startFilePos"></param>
	/// <returns> Возвращает строку </returns>
	string getInfo(int linePos)
	{
		openToRead(mode);

		curLine = 0;

		if (fileRead.is_open())
		{
			fileRead.seekg(0, ios::beg);

			while (getline(fileRead, tLine))
			{
				if (curLine == linePos)
				{
					fileRead.close();
					return tLine;
				}
				curLine++;
			}
		}
		else
		{
			cout << "\n Файл закрыт для чтения!!!\n";
			return "Error!!!";
		}

	}

	/// <summary>
	/// Выводит на экран информацию о результатах выбранной сессии
	/// </summary>
	/// <param name="sessionNumber"> Номер сессии </param>
	void printSessionInfo(int sessionNumber, int studentNumber)
	{
		string fullLine1 = "Сессия номер ";
		string fullLine2 = " Студента номер ";
		int tNumberLine;


		fullLine1 += to_string(sessionNumber); // Получаем строку типа:  Сессия номер x
		fullLine1 += fullLine2; 
		fullLine1 += to_string(studentNumber); // Получаем строку типа:  Сессия номер x Студента номер х

		tNumberLine = searchData(fullLine1); // Ищем номер строки в файле

		cout << "\nДанные по " << sessionNumber << " сесии:\n";

		printInfo(tNumberLine + 1, (tNumberLine + SUBJECTNUMBER));
	}

	/// <summary>
	/// Ищет в файле строку по введенной строке
	/// </summary>
	/// <param name="bookNumber"> Строка, которую нужно найти </param>
	/// <returns> Возвращает целое число - номер искомой строки, если найдено, в противном случае -1 </returns>
	int searchData(string fullLine)
	{
		openToRead(mode);

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

			return -1;
		}
		else
		{
			cout << "\nФайл закрыт для чтения!!!\n";
			return -1;
		}
	}

	/// <summary>
	/// Считывает строки с информацией о результатах сессий из файла и заносит данные в вектора в виде кода
	/// </summary>
	void countStudentsPerfomance()
	{
		string fullLine;
		string fullLine1;
		int tNumberLine;
		int averageNumber;

		for (int j = 0; j < studentCount; j++)
		{
			for (int i = 0; i < SESSIONNUMBER; i++)
			{
				tNumberLine = 0;
				averageNumber = 0;

				fullLine = "Сессия номер ";
				fullLine1 = " Студента номер ";

				fullLine += to_string(i + 1);
				fullLine += fullLine1;
				fullLine += to_string(j + 1);

				string temporary = getInfo(j * DECREMENT);
				
				if (temporary == "----------")
				{
					break;
				}

				tNumberLine = searchData(fullLine);

				for (int k = 0; k < SUBJECTNUMBER; k++)
				{
					tLine = getInfo(tNumberLine + k);
					averageNumber += countAverageNumber(tLine);
				}

				averageNumber = averageNumber / SUBJECTNUMBER;

				if (averageNumber == 5)
				{
					v5.push_back(i + 1 + (j + 1) * 10);
				}
				if (averageNumber == 4)
				{
					v4.push_back(i + 1 + (j + 1) * 10);
				}
				if (averageNumber == 3)
				{
					v3.push_back(i + 1 + (j + 1) * 10);
				}
			}
		}
	}

	/// <summary>
	/// Выводит на экран данные о результатах сессии, вводимой с клавиатуры
	/// </summary>
	void showStudentPerfomance(int sessionNumber)
	{
		int nameMarker;
		int Count = 0;
		int code = 0;

		cout << "\nТроечники в " << sessionNumber << " сессии:\n";

		if (v3.size() < 1)
		{
			cout << "Отсутствуют\n";
		}
		else
		{
			for (int i = 0; i < v3.size(); i++)
			{
				code = v3[i] % 10;

				if (code == sessionNumber)
				{
					Count++;

					code = (v3[i] - code) / 10;

					nameMarker = 1 + (code - 1) * (SESSIONNUMBER * (SUBJECTNUMBER + 1) + 8);

					printInfo(nameMarker, nameMarker);
				}
			}

			if (Count == 0)
			{
				cout << "Отсутствуют\n";
			}
		}

		Count = 0;
		code = 0;

		cout << "\nХорошисты в " << sessionNumber << " сессии:\n";

		if (v4.size() < 1)
		{
			cout << "Отсутствуют\n";
		}
		else
		{
			for (int i = 0; i < v4.size(); i++)
			{
				code = v4[i] % 10;

				if (code == sessionNumber)
				{
					Count++;

					code = (v4[i] - code) / 10;

					nameMarker = 1 + (code - 1) * (SESSIONNUMBER * (SUBJECTNUMBER + 1) + 8);

					printInfo(nameMarker, nameMarker);
				}
			}

			if (Count == 0)
			{
				cout << "Отсутствуют\n";
			}
		}

		Count = 0;
		code = 0;

		cout << "\nОтличники в " << sessionNumber << " сессии:\n";

		if (v5.size() < 1)
		{
			cout << "Отсутствуют\n";
		}
		else
		{
			for (int i = 0; i < v5.size(); i++)
			{
				code = v5[i] % 10;

				if (code == sessionNumber)
				{
					Count++;

					code = (v5[i] - code) / 10;

					nameMarker = 1 + (code - 1) * (SESSIONNUMBER * (SUBJECTNUMBER + 1) + 8);

					printInfo(nameMarker, nameMarker);
				}
			}

			if (Count == 0)
			{
				cout << "Отсутствуют\n";
			}
		}
	}

	/// <summary>
	/// Преобразует строку string типа: Предмет - оценка, в одно целое число int - оценку по предмету
	/// </summary>
	/// <returns> Возвращает целое число - оценку по предмету </returns>
	int countAverageNumber(string line)
	{
		if (line.find('5') != string::npos)
		{
			return 5;
		}
		else if (line.find('4') != string::npos)
		{
			return 4;
		}
		else if (line.find('3') != string::npos)
		{
			return 3;
		}
		else if (line.find('2') != string::npos)
		{
			return 2;
		}
		else
		{
			cout << "\nОшибка!!! Введена неверная строка в countAveraheNumber()\n";
			system("pause");
			return 0;
		}
	}

	/// <summary>
	/// Вычисляет порядковый номер студента по строке с его ФИО
	/// </summary>
	/// <returns> Возвращает порядковый номер студента </returns>
	int getStudentNumber(int startFilePos)
	{
		int count = 1;

		if (startFilePos == 1)
		{
			return 1;
		}
		else if (startFilePos > 1)
		{
			while (startFilePos != 1)
			{
				startFilePos -= DECREMENT;
				count++;
			}

			return count;
		}
		else
		{
			cout << "\nОшибка! Задана неверная строка при получении номера студента!\n";
			return -1;
		}
	}

	/// <summary>
	/// Проверяет есть ли в базе данных студенты, если да, то возвращает их кол-во
	/// </summary>
	/// <returns> Вовзвращает кол-во студентов в БД </returns>
	int checkForStudentCount()
	{
		openToRead(mode);

		curLine = 0;

		if (fileRead.is_open())
		{
			fileRead.seekg(0, ios::beg);

			while (getline(fileRead, tLine))
			{
				curLine++;
			}

			curLine = curLine / DECREMENT;

			fileRead.close();

			return curLine;
		}
		else
		{
			cout << "\nФайл закрыт для чтения!!!\n";
			return -1;
		}
	}

	/// <summary>
	/// Создаёт временный файл, помещает туда изменненные данные, затем удаляет старый файл
	/// </summary>
	void changeStudentData(int line)
	{
		int studentNumber;
		int tStudentCount;

		studentNumber = getStudentNumber(line);

		fileWrite.close();

		createNewTemporaryFile(mode);

		oldData.clear();

		saveOldData(line);

		tStudentCount = studentCount;
		studentCount = studentNumber - 1;

		if (studentNumber == 1)
		{
			writeInFile();

			copyFromOldData(0, oldData.size());
		}
		else if (studentNumber == tStudentCount)
		{
			copyFromOldData(0, oldData.size());

			writeInFile();
		}
		else
		{
			copyFromOldData(0, line - 1);

			writeInFile();

			copyFromOldData(line - 1, oldData.size());
		}

		if (mode == 0) 
		{ 
			mode = 1; 

			remove("StudentsData.txt");
		}
		else 
		{
			mode = 0; 

			remove("TemporaryStudentsData.txt");
		}

		studentCount = tStudentCount;
	}

	/// <summary>
	/// Сохраняет неизмененные данные из файла
	/// </summary>
	/// <param name="startPos"> номер строки, начниная с которой данные изменены, если передать -1, то все данные будут скопированы </param>
	void saveOldData(int startPos)
	{
		curLine = 0;

		openToRead(mode);

		if (fileRead.is_open())
		{
			fileRead.seekg(0, ios::beg);

			if (startPos != -1)
			{
				while (getline(fileRead, tLine))
				{
					if ((curLine < startPos - 1) || (curLine >= startPos + DECREMENT - 1))
					{
						oldData.push_back(tLine);
					}
					curLine++;
				}
			}
			else
			{
				while (getline(fileRead, tLine))
				{
					oldData.push_back(tLine);
				}
			}

			fileRead.close();
		}
		else
		{
			cout << "\nФайл закрыт для чтения!!!\n";
		}
	}

	/// <summary>
	/// Помещает в файл неизменненные данные из старого файла от start до end строки
	/// </summary>
	void copyFromOldData(int start, int end)
	{
		for (int i = start; i < end; i++)
		{
			fileWrite << oldData[i];
			fileWrite << endl;
		}
	}

	/// <summary>
	/// Удаляет номер зачётной книжки из реестра
	/// </summary>
	void deleteRecordBookNumber(string rbNumber)
	{
		int elem;

		for (int i = 0; i < booksData.size(); i++)
		{
			if (booksData[i] == rbNumber)
			{
				elem = i;
			}
		}

		booksData.erase(booksData.begin() + elem);
	}

	/// <summary>
	/// Проверяет файл на наличие уже записанных номеров зачётных книжек
	/// </summary>
	void checkRBNumber(int studentsNumber)
	{
		int coef = searchData("Номер зачётной книжки - ") - 1;

		for (int i = 0; i < studentsNumber; i++)
		{
			tLine = getInfo(coef + DECREMENT*i);

			tLine.erase(0, 24);

			booksData.push_back(tLine);
		}
	}

	/// <summary>
	/// Удаляет данные о студенте из файла, оставляя на их месте пробел
	/// </summary>
	void killStudent(int line)
	{
		int studentNumber;

		studentNumber = getStudentNumber(line);

		clearStudentPerfomance(studentNumber);

		fileWrite.close();

		createNewTemporaryFile(mode);

		saveOldData(line);

		if (studentNumber == 1)
		{
			for (int i = 0; i < DECREMENT; i++)
			{
				fileWrite << "----------\n";
			}

			copyFromOldData(0, oldData.size());
		}
		else if (studentNumber == studentCount)
		{
			copyFromOldData(0, oldData.size());

			for (int i = 0; i < DECREMENT; i++)
			{
				fileWrite << "----------\n";
			}
		}
		else
		{
			copyFromOldData(0, line - 1);

			for (int i = 0; i < DECREMENT; i++)
			{
				fileWrite << "----------\n";
			}

			copyFromOldData(line - 1, oldData.size());
		}

		if (mode == 0)
		{
			mode = 1;

			oldData.clear();

			remove("StudentsData.txt");
		}
		else
		{
			mode = 0;

			oldData.clear();

			remove("TemporaryStudentsData.txt");
		}
	}

	void clearStudentPerfomance(int StudentNumber)
	{
		int temp;

		for (int i = 0; i < v5.size(); i++)
		{
			temp = v5[i] / 10;

			if (temp == StudentNumber)
			{
				v5.erase(v5.begin() + i);
			}
		}

		for (int i = 0; i < v4.size(); i++)
		{
			temp = v4[i] / 10;

			if (temp == StudentNumber)
			{
				v4.erase(v4.begin() + i);
			}
		}

		for (int i = 0; i < v3.size(); i++)
		{
			temp = v3[i] / 10;

			if (temp == StudentNumber)
			{
				v3.erase(v3.begin() + i);
			}
		}
	}

	FileManager()
	{
		fileRead.open("StudentsData.txt");

		if (fileRead.is_open())
		{
			fileRead.close();

			studentCount = checkForStudentCount();

			if (studentCount != 0)
			{
				checkRBNumber(studentCount);
			}
		}
	}

	~FileManager()
	{
		fileRead.close();

		fileWrite.close();

		rename("TemporaryStudentsData.txt", "StudentsData.txt");
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

	int flag = 0;

public:

	/// <summary>
	/// Создаёт консольный интерфейс меню
	/// </summary>
	/// <returns>Возвращает 1 до тех пор пока пользователь не решит выйти</returns>
	int startMenu()
	{
		menu = 0;

		cout << "\nВыберите действие:\n";
		cout << "\n1. Создать базу данных студентов\n2. Записать данные студента в базу данных\n3. Узнать данные студента\n4. Изменить данные студента\n5. Удалить данные студента\n6. Посмотреть успеваемость студентов\n7. Выйти из программы\n";
		cout << "Ваш выбор -> ";
		cin >> menu;
		cout << endl;

		if ((menu > 1) && (menu < 7))
		{
			openToRead(mode);

			if (!(fileRead.is_open()))
			{
				system("cls");
				return 1;
			}

			fileRead.close();
		}

		switch (menu)
		{
		case 1:
		{
			flag = 1;

			openToWrite();

			system("pause");
			system("cls");
			return 1;
		}
		case 2:
		{
			if (flag == 0)
			{
				createNewTemporaryFile(mode);

				saveOldData(-1);

				copyFromOldData(0, oldData.size());

				writeInFile();

				if (mode == 0)
				{
					mode = 1;

					remove("StudentsData.txt");
				}
				else
				{
					mode = 0;

					remove("TemporaryStudentsData.txt");
				}

				cout << endl;
				system("pause");
			}
			else
			{
				writeInFile();

				cout << endl;
				system("pause");
			}

			system("cls");
			return 1;
		}
		case 3:
		{
			A:
			int searchedLine; 
			int studentNumber;
			int sessionNumber;

			cout << "\nВведите номер зачётной книжки -> ";
			cin >> tRecordBookNumber;
			cout << endl;

			searchedLine = searchData(tRecordBookNumber);

			if (searchedLine == -1)
			{
				cout << "\nТакой номер не был найден. Проверьте правильность ввода и повторите попытку\n";
				system("pause");
				goto A;
			}

			searchedLine -= 6; // Возврат к строке ФИО

			cout << "\nДанные о студенте:\n";

			printInfo(searchedLine, searchedLine + 7); // Печатаем инфо о студенте

		B:
			cout << "\nВыберите действие:\n";
			cout << "1. Посмотреть результаты сессий\n2. Вернуться в главное меню\n";
			cout << "Ваш выбор -> ";
			cin >> menu;
			cout << endl;

			if (menu == 1)
			{
				studentNumber = getStudentNumber(searchedLine); // Получаем порядковый номер студента по строке с его ФИО

				if (studentNumber == -1)
				{
					system("pause");
					return 1;
				} // Ловим ошибку

			C:
				cout << "\nВыберите номер сессии -> ";
				cin >> sessionNumber;
				cout << endl;

				if ((sessionNumber < 1) || (sessionNumber > SESSIONNUMBER))
				{
					cout << "\nОшибка ввода, повторите попытку\n";
					system("pause");
					system("cls");
					goto C;
				}

				printSessionInfo(sessionNumber, studentNumber); // Печатаем данные по сессии
			E:
				cout << "\n\nВыберите действие:\n";
				cout << "\n1. Выбрать другую сессию\n2. Вернуться на главный экран\n";
				cout << "Ваш выбор -> ";
				cin >> menu;
				cout << endl;

				if (menu == 1)
				{
					goto C;
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
			else if (menu == 2)
			{
				system("cls");
				return 1;
			}
			else
			{
				cout << "\nОшибка ввода повторите попытку!!!\n";
				system("pause");
				goto B;
			}
		}
		case 4:
		{
		begin:

			int tLine;

			cout << "\nВведите номер зачётной книжки студента, данные которого нужно изменить  -> ";
			cin >> tRecordBookNumber;
			cout << endl;

			tLine = searchData(tRecordBookNumber);

			if (tLine == -1)
			{
				cout << "\nТакой номер не был найден. Проверьте правильность ввода и повторите попытку\n";
				system("pause");
				goto begin;
			}

			tLine -= 6; // Возврат к строке ФИО

			cout << "\nВведите новые данные студента:\n";

			deleteRecordBookNumber(tRecordBookNumber);

			changeStudentData(tLine);

			cout << "\nДанные успешно изменены!\n";
			system("pause");
			system("cls");

			oldData.clear();

			return 1;
		}
		case 5:
		{
			int tLine;

			cout << "\nВведите номер зачётной книжки студента, данные которого нужно удалить  -> ";
			cin >> tRecordBookNumber;
			cout << endl;

			tLine = searchData(tRecordBookNumber);

			if (tLine == -1)
			{
				cout << "\nТакой номер не был найден. Проверьте правильность ввода и повторите попытку\n";
				system("pause");
				goto begin;
			}

			tLine -= 6; // Возврат к строке ФИО

			deleteRecordBookNumber(tRecordBookNumber);

			killStudent(tLine);

			cout << "\nДанные успешно удалены!\n";
			system("pause");
			system("cls");

			return 1;
		}
		case 6:
		{
			if (studentCount < 1)
			{
				studentCount = checkForStudentCount();
			}

			countStudentsPerfomance();

		A1:
			cout << "\nВведите номер сессии -> ";
			cin >> menu;
			cout << endl;

			if ((menu < 1) || (menu > SESSIONNUMBER))
			{
				cout << "\nОшибка ввода, повторите попытку\n";
				system("pause");
				goto A1;
			}

			showStudentPerfomance(menu);

		A2:
			cout << "\nВыберите действие:\n";
			cout << "\n1. Выбрать другую сессию\n2. Вернуться в главное меню\n";
			cout << "\nВаш выбор -> ";
			cin >> menu;
			cout << endl;

			if (menu == 1)
			{
				goto A1;
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
				goto A2;
			}
		}
		case 7:
		{
			system("cls");
			return 0;
		}
		default:
		{
			cout << "\nОшибка ввода!!!!\nПовторите попытку\n";
			system("pause");
			system("cls");
			return 1;
		}
		}
	}

};

int Student::studentCount = 0;

/// <summary>
/// Тело программы. Зацикливает выбор опций в объекте меню
/// </summary>
/// <returns>Возвращает 0 при успешном завершении</returns>
int main()
{
	int indicator = 1;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MenuPattern *Menu = new MenuPattern;

	while (indicator != 0)
	{

		indicator = Menu->startMenu();

	}
	
	delete Menu;

	return 0;
}