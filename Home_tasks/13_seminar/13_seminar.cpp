#include <iostream>
#include <string>
using namespace std;



// Задача 1: Создание класса «Книга» 
class Publication {
public:
    string title;

    // Конструктор базового класса (не обязателен, но удобен)
    Publication(string t) : title(t) {}
    // Конструктор по умолчанию нужен, если будем создавать объекты без параметров
    Publication() : title("") {}
};

// Производный класс Book
class Book : public Publication {
public:
    string author;
    int year;

    // Конструктор с параметрами
    // Инициализирует базовый класс Publication через список инициализации
    Book(string t, string a, int y) : Publication(t), author(a), year(y) {}

    // Метод для вывода информации
    void displayInfo() {
        cout << "Название: " << title << ", Автор: " << author << ", Год выпуска: " << year << endl;
    }
};

void runTask1() {
    cout << "Задача 1: Создание класса «Книга»" << endl;

    // Создаем объект и инициализируем его конструктором
    Book myBook("Война и мир", "Лев Толстой", 1869);

    // Выводим информацию
    myBook.displayInfo();
    
    cout << endl;
}



// Задача 2: Создание класса «Прямоугольник»
class Shape {
public:
    double length;

    // Конструктор
    Shape(double l) : length(l) {}
    Shape() : length(0) {}
    
    // Виртуальный метод displayInfo для демонстрации полиморфизма
    virtual void displayInfo() {
        cout << "Длина: " << length << endl;
    }
};

// Производный класс Rectangle
class Rectangle : public Shape {
public:
    double width;

    // Конструктор с параметрами
    Rectangle(double l, double w) : Shape(l), width(w) {}

    // Метод вычисления площади
    double calculateArea() {
        return length * width;
    }

    // Метод вычисления периметра
    double calculatePerimeter() {
        return 2 * (length + width);
    }

    // Переопределенный метод вывода информации
    void displayInfo() override {
        cout << "Длина: " << length 
             << ", Ширина: " << width 
             << ", Площадь: " << calculateArea() 
             << ", Периметр: " << calculatePerimeter() << endl;
    }
};

void runTask2() {
    cout << "Задача 2: Создание класса «Прямоугольник»" << endl;

    // Создаем объект прямоугольника
    Rectangle rect(10.0, 5.0);

    // Выводим информацию
    rect.displayInfo();

    cout << endl;
}

int main() {
    runTask1();
    runTask2();

    return 0;
}
