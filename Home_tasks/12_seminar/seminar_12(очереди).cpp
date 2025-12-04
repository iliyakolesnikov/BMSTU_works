#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// Задача 1 - Очередь в магазине

// Функция добавления человека в очередь
void addToQueue(queue<string>& q, const string& person) {
    q.push(person);
}

// Функция обработки человека из начала очереди
void processQueue(queue<string>& q) {
    if (!q.empty()) {
        cout << "Обработан клиент: " << q.front() << endl;
        q.pop(); // Удаляем человека из очереди
    } else {
        cout << "Очередь пуста." << endl;
    }
}

void runTask1() {
    cout << "=== ЗАДАЧА 1: Очередь в магазине ===" << endl;
    queue<string> shopQueue;

    addToQueue(shopQueue, "Иван");
    addToQueue(shopQueue, "Анна");
    addToQueue(shopQueue, "Петр");

    processQueue(shopQueue);
    processQueue(shopQueue);
    processQueue(shopQueue);
    processQueue(shopQueue); // Проверка пустой очереди
    cout << endl; // Пустая строка для разделения задач
}



// Задача 2 - Сетевые события

// Функция добавления события
void addEvent(queue<string>& eventQueue, const string& event) {
    eventQueue.push(event);
}

// Функция обработки события
void processEvents(queue<string>& eventQueue) {
    if (!eventQueue.empty()) {
        cout << "Обработка события: " << eventQueue.front() << endl;
        eventQueue.pop();
    } else {
        cout << "Очередь событий пуста." << endl;
    }
}

void runTask2() {
    cout << "=== ЗАДАЧА 2: Сетевые события ===" << endl;
    queue<string> events;

    addEvent(events, "Вход пользователя");
    addEvent(events, "Получение сообщения");
    addEvent(events, "Отправка файла");

    while (!events.empty()) {
        processEvents(events);
    }
    processEvents(events); // Проверка
    cout << endl;
}



// Задача 3 - Интернет-магазин

struct Order {
    string customerName;
    vector<string> items;
};

// Функция добавления заказа
void addOrder(queue<Order>& orderQueue, const Order& newOrder) {
    orderQueue.push(newOrder);
}

// Функция обработки заказа
void processOrder(queue<Order>& orderQueue) {
    if (!orderQueue.empty()) {
        Order current = orderQueue.front();
        
        cout << "Заказчик: " << current.customerName << endl;
        cout << "Товары: ";
        for (const string& item : current.items) {
            cout << item << ", ";
        }
        cout << endl << "-------------------" << endl;
        
        orderQueue.pop();
    } else {
        cout << "Очередь заказов пуста." << endl;
    }
}

void runTask3() {
    cout << "=== ЗАДАЧА 3: Интернет-магазин ===" << endl;
    queue<Order> orders;

    Order order1 = {"Дмитрий", {"Телефон", "Зарядка"}};
    Order order2 = {"Елена", {"Книга"}};
    Order order3 = {"Максим", {"Ноутбук", "Мышка"}};

    addOrder(orders, order1);
    addOrder(orders, order2);
    addOrder(orders, order3);

    while (!orders.empty()) {
        processOrder(orders);
    }
    cout << endl;
}


int main() {
    runTask1();
    runTask2();
    runTask3();
    return 0;
}

