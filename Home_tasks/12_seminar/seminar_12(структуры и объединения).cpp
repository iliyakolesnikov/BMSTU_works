#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;


// Задача 1 (Структуры): Учет сотрудников

struct Employee {
    string name;
    int age;
    string position;
    double salary;
};

void runStructTask1() {
    cout << "=== СТРУКТУРЫ: Задача 1 (Учет сотрудников) ===" << endl;
    
    vector<Employee> employees;
    int count;
    
    cout << "Введите количество сотрудников: ";
    cin >> count;

    for (int i = 0; i < count; ++i) {
        Employee e;
        cout << "Сотрудник " << i + 1 << ":" << endl;
        cout << "Имя: "; cin >> e.name;
        cout << "Возраст: "; cin >> e.age;
        cout << "Должность: "; cin >> e.position;
        cout << "Зарплата: "; cin >> e.salary;
        employees.push_back(e);
    }

    // Поиск самого молодого и самого старшего
    if (employees.empty()) return;

    Employee youngest = employees[0];
    Employee oldest = employees[0];
    double totalSalary = 0;

    for (const auto& e : employees) {
        if (e.age < youngest.age) youngest = e;
        if (e.age > oldest.age) oldest = e;
        totalSalary += e.salary;
    }

    cout << "Самый молодой: " << youngest.name << " (" << youngest.age << ")" << endl;
    cout << "Самый старший: " << oldest.name << " (" << oldest.age << ")" << endl;
    cout << "Средняя зарплата: " << totalSalary / count << endl;
    cout << endl;
}


// Задача 2 (Структуры): Банковский счет

struct BankAccount {
    int accountNumber;
    string ownerName;
    double balance;
};

void runStructTask2() {
    cout << "=== СТРУКТУРЫ: Задача 2 (Банковский счет) ===" << endl;
    
    // Для упрощения создадим один тестовый счет
    BankAccount myAccount;
    
    cout << "Создание счета." << endl;
    cout << "Введите номер счета: "; cin >> myAccount.accountNumber;
    cout << "Введите имя владельца: "; cin >> myAccount.ownerName;
    myAccount.balance = 0.0;
    cout << "Счет создан!" << endl;

    // Простая имитация меню
    int choice = 0;
    while (choice != 4) {
        cout << "1. Пополнить  2. Снять  3. Инфо  4. Выход: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            cout << "Сумма пополнения: "; cin >> amount;
            myAccount.balance += amount;
        } else if (choice == 2) {
            double amount;
            cout << "Сумма снятия: "; cin >> amount;
            if (amount <= myAccount.balance) myAccount.balance -= amount;
            else cout << "Недостаточно средств!" << endl;
        } else if (choice == 3) {
            cout << "Счет #" << myAccount.accountNumber << ", Владелец: " 
                 << myAccount.ownerName << ", Баланс: " << myAccount.balance << endl;
        }
    }
    cout << endl;
}


// Задача 3 (Структуры): Библиотека

struct Book {
    string title;
    string author;
    int year;
};

struct Library {
    vector<Book> books;
};

void runStructTask3() {
    cout << "=== СТРУКТУРЫ: Задача 3 (Библиотека) ===" << endl;
    
    Library lib;
    
    // Добавляем книги
    lib.books.push_back({"Война и мир", "Толстой", 1869});
    lib.books.push_back({"1984", "Оруэлл", 1949});
    lib.books.push_back({"Преступление и наказание", "Достоевский", 1866});

    cout << "Список книг в библиотеке:" << endl;
    for (const auto& book : lib.books) {
        cout << "\"" << book.title << "\" - " << book.author << " (" << book.year << ")" << endl;
    }

    // Пример поиска
    string searchAuthor;
    cout << "Введите автора для поиска: "; cin >> searchAuthor;

    cout << "Найденные книги:" << endl;
    bool found = false;
    for (const auto& book : lib.books) {
        if (book.author == searchAuthor) {
            cout << book.title << endl;
            found = true;
        }
    }
    if (!found) cout << "Книг этого автора не найдено." << endl;
    cout << endl;
}


// Задача 4 (Объединения): Разные типы данных

union Variant {
    int iVal;
    double dVal;
    char cVal;
};

void runUnionTask1() {
    cout << "=== ОБЪЕДИНЕНИЯ: Задача 1 (Типы данных) ===" << endl;
    
    Variant v;
    char type;
    cout << "Выберите тип (i - int, d - double, c - char): ";
    cin >> type;

    if (type == 'i') {
        cout << "Введите целое число: ";
        cin >> v.iVal;
        cout << "Вы ввели int: " << v.iVal << endl;
    } else if (type == 'd') {
        cout << "Введите дробное число: ";
        cin >> v.dVal;
        cout << "Вы ввели double: " << v.dVal << endl;
    } else if (type == 'c') {
        cout << "Введите символ: ";
        cin >> v.cVal;
        cout << "Вы ввели char: " << v.cVal << endl;
    }
    cout << endl;
}


// Задача 5 (Объединения): Геометрические фигуры

union ShapeParams {
    double radius;      // Для круга
    struct {            // Для прямоугольника
        double width;
        double height;
    } rect;
};

void runUnionTask2() {
    cout << "=== ОБЪЕДИНЕНИЯ: Задача 2 (Фигуры) ===" << endl;
    
    ShapeParams shape;
    int choice;
    
    cout << "Выберите фигуру (1 - Круг, 2 - Прямоугольник): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Введите радиус: ";
        cin >> shape.radius;
        // 3.14159 - упрощенное пи
        cout << "Площадь круга: " << 3.14159 * shape.radius * shape.radius << endl;
    } else if (choice == 2) {
        cout << "Введите ширину: ";
        cin >> shape.rect.width;
        cout << "Введите высоту: ";
        cin >> shape.rect.height;
        cout << "Площадь прямоугольника: " << shape.rect.width * shape.rect.height << endl;
    }
    cout << endl;
}


// Задача 6 (Объединения): Дата и время

union DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

void runUnionTask3() {
    cout << "=== ОБЪЕДИНЕНИЯ: Задача 3 (Дата и время - демонстрация перезаписи) ===" << endl;
    
    DateTime dt;
    
    // В union мы не можем хранить всё сразу!
    // Сохраняя одно, мы "портим" другое.
    // Задача демонстрирует этот принцип.
    
    cout << "Устанавливаем год = 2023" << endl;
    dt.year = 2023;
    cout << "Значение в памяти (год): " << dt.year << endl;
    
    cout << "Устанавливаем месяц = 12" << endl;
    dt.month = 12; 
    cout << "Значение в памяти (месяц): " << dt.month << endl;
    
    cout << "А теперь посмотрим, что стало с годом: " << dt.year << endl;
    cout << "(Видите? Год стал равен 12, потому что память общая)" << endl;
    
    cout << endl;
}

int main() {
    // Запуск задач на структуры
    runStructTask1();
    runStructTask2();
    runStructTask3();
    // Запуск задач на объединения
    runUnionTask1();
    runUnionTask2();
    runUnionTask3();
    return 0;
}
