#include <iostream>
#include <fstream>
#include <string>
#include <pqxx/pqxx> // Библиотека PostgreSQL

using namespace std;
using namespace pqxx;

// --- 1. Настройки подключения 
string conn_str = "dbname=postgres user=postgres password=postgreS host=localhost";

// --- 2. Логирование ---
void logAction(string msg) {
    ofstream f("log.txt", ios::app);
    f << "[LOG]: " << msg << endl;
}

// --- 3. Шаблонный класс ---
template <typename T1, typename T2>
struct Pair {
    T1 name; 
    T2 count;
    void print() { cout << "Товар: " << name << " | Количество: " << count << endl; }
};

// --- 4. Классы ---
class Product {
public:
    string name; double price;
    Product(string n, double p) : name(n), price(p) {}
    virtual string getType() { return "Базовый"; }
};

class DigitalProduct : public Product {
public:
    DigitalProduct(string n, double p) : Product(n, p) {}
    string getType() override { return "Цифровой"; }
};

// --- 5. Функции работы с БД (Транзакции) ---

void addProduct(string name, double price) {
    try {
        connection C(conn_str);
        work txn(C); // Начало транзакции

        // Вставляем данные. txn.esc защищает от спецсимволов
        string sql = "INSERT INTO products (name, price) VALUES ('" + txn.esc(name) + "', " + to_string(price) + ")";
        txn.exec(sql);
        
        txn.commit(); // Сохранение
        cout << "Товар добавлен." << endl;
        logAction("Добавлен товар: " + name);
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void addOrder() {
    try {
        connection C(conn_str);
        work txn(C);
        
        txn.exec("INSERT INTO orders (order_date) VALUES (CURRENT_DATE)");
        
        txn.commit();
        cout << "Заказ создан текущей датой." << endl;
        logAction("Создан новый заказ");
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void addItemToOrder(int orderId, int prodId, int qty) {
    try {
        connection C(conn_str);
        work txn(C);

        // 1. Узнаем цену товара (для расчета total_price)
        result r = txn.exec("SELECT price FROM products WHERE id = " + to_string(prodId));
        if (r.empty()) { cout << "Товар не найден!" << endl; return; }
        
        double price = r[0][0].as<double>();
        double total = price * qty;

        // 2. Добавляем запись
        string sql = "INSERT INTO order_items (order_id, product_id, quantity, total_price) VALUES (" +
                     to_string(orderId) + ", " + 
                     to_string(prodId) + ", " + 
                     to_string(qty) + ", " + 
                     to_string(total) + ")";
        
        txn.exec(sql);
        txn.commit();
        cout << "Позиция добавлена. Сумма: " << total << endl;
        logAction("В заказ " + to_string(orderId) + " добавлен товар " + to_string(prodId));
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

void showAnalytics() {
    try {
        connection C(conn_str);
        work txn(C);
        
        // JOIN по product_id
        string sql = "SELECT p.name, SUM(oi.quantity) as total_qty "
                     "FROM products p "
                     "JOIN order_items oi ON p.id = oi.product_id "
                     "GROUP BY p.name "
                     "ORDER BY total_qty DESC LIMIT 3";

        result R = txn.exec(sql);
        
        cout << "\n--- ТОП-3 ТОВАРОВ ---" << endl;
        for (auto row : R) {
            // Используем шаблонный класс
            Pair<string, int> item = {row[0].c_str(), row[1].as<int>()};
            item.print();
        }
        logAction("Запрошен отчет");
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

// --- 6. Главное меню ---
int main() {
    int ch;
    while (true) {
        cout << "\n1. Добавить товар\n2. Создать заказ\n3. Добавить позицию\n4. Отчет (Топ-3)\n0. Выход\nВыбор: ";
        cin >> ch;
        if (ch == 0) break;

        if (ch == 1) {
            string n; double p;
            cout << "Имя: "; cin >> n;
            cout << "Цена: "; cin >> p;
            DigitalProduct dp(n, p); // Формальное использование классов
            addProduct(dp.name, dp.price);
        }
        else if (ch == 2) addOrder();
        else if (ch == 3) {
            int oid, pid, q;
            cout << "ID Заказа: "; cin >> oid;
            cout << "ID Товара: "; cin >> pid;
            cout << "Количество: "; cin >> q;
            addItemToOrder(oid, pid, q);
        }
        else if (ch == 4) showAnalytics();
    }
    return 0;
}

