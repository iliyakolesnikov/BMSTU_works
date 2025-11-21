#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Структура товара остаётся без изменений
struct Product {
    string name;
    int quantity;
    double price;
};

// Перегрузка оператора для удобного вывода
ostream& operator<<(ostream& os, const Product& p) {
    return os << "Название: " << p.name << ", Кол-во: " << p.quantity << ", Цена: " << p.price;
}

// Вспомогательная функция для чтения всех товаров из файла
vector<Product> readProductsFromFile() {
    vector<Product> products;
    ifstream inFile("orders.txt");
    Product temp;
    while (inFile >> temp.name >> temp.quantity >> temp.price) {
        products.push_back(temp);
    }
    return products;
}

// Вспомогательная функция для перезаписи файла товарами из вектора
void writeProductsToFile(const vector<Product>& products) {
    ofstream outFile("orders.txt");
    for (const auto& p : products) {
        outFile << p.name << " " << p.quantity << " " << p.price << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    do {
        cout << "\n1.Добавить 2.Найти 3.Сортировать 4.Вывод по цене 0.Выход\nВыбор: ";
        cin >> choice;

        switch (choice) {
            case 1: { // Добавление товара
                ofstream outFile("orders.txt", ios::app);
                ofstream logFile("output.txt", ios::app);
                Product p;
                cout << "Название: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, p.name);
                if (p.name.empty()) break;
                cout << "Кол-во: "; cin >> p.quantity;
                cout << "Цена: "; cin >> p.price;
                outFile << p.name << " " << p.quantity << " " << p.price << endl;
                logFile << "Добавлен: " << p << endl;
                cout << "Товар добавлен.\n";
                break;
            }
            case 2: { // Поиск товара
                string searchName;
                cout << "Название для поиска: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, searchName);
                
                vector<Product> products = readProductsFromFile();
                ofstream logFile("output.txt", ios::app);
                logFile << "Поиск '" << searchName << "':\n";
                bool found = false;
                for (const auto& p : products) {
                    if (p.name == searchName) {
                        cout << "Найден: " << p << endl;
                        logFile << "Найден: " << p << endl;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Товар не найден.\n";
                    logFile << "Товар не найден.\n";
                }
                break;
            }
            case 3: { // Сортировка
                vector<Product> products = readProductsFromFile();
                int sort_choice;
                cout << "Сортировать по: 1.Названию 2.Кол-ву 3.Цене\nВыбор: ";
                cin >> sort_choice;

                if (sort_choice == 1) sort(products.begin(), products.end(), [](auto a, auto b){ return a.name < b.name; });
                else if (sort_choice == 2) sort(products.begin(), products.end(), [](auto a, auto b){ return a.quantity < b.quantity; });
                else if (sort_choice == 3) sort(products.begin(), products.end(), [](auto a, auto b){ return a.price < b.price; });
                else { cout << "Неверный выбор.\n"; break; }
                
                writeProductsToFile(products);
                cout << "Файл отсортирован.\n";
                ofstream logFile("output.txt", ios::app);
                logFile << "Выполнена сортировка (критерий " << sort_choice << ")\n";
                for(const auto& p : products) logFile << p << endl;
                break;
            }
            case 4: { // Вывод по цене
                double maxPrice;
                cout << "Макс. цена: ";
                cin >> maxPrice;
                
                vector<Product> products = readProductsFromFile();
                ofstream logFile("output.txt", ios::app);
                logFile << "Запрос товаров (цена <= " << maxPrice << "):\n";
                bool found = false;
                for (const auto& p : products) {
                    if (p.price <= maxPrice) {
                        cout << p << endl;
                        logFile << p << endl;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Таких товаров нет.\n";
                    logFile << "Таких товаров нет.\n";
                }
                break;
            }
            case 0: cout << "Выход.\n"; break;
            default: cout << "Неверный выбор.\n"; break;
        }
    } while (choice != 0);

    return 0;
}

