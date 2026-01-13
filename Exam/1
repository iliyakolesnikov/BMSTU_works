#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std; // Чтобы не писать std:: каждый раз

// Функция добавления события
void addEvent(queue<string>& eventQueue, const string& event) {
    eventQueue.push(event);
}

// Функция обработки события
void processEvents(queue<string>& eventQueue) {
    if (!eventQueue.empty()) {
        cout << "Обработка события: " << eventQueue.front() << endl;
        eventQueue.pop(); // Удаляем событие после обработки
    } else {
        cout << "Очередь событий пуста." << endl;
    }
}

// Блок main №2
int main() {
    queue<string> events;

    // Симуляция поступления событий
    addEvent(events, "Запрос авторизации");
    addEvent(events, "Загрузка данных");
    addEvent(events, "Ошибка соединения");

    // Обработка событий по порядку
    while (!events.empty()) {
        processEvents(events);
    }
    
    // Попытка обработать пустую очередь
    processEvents(events);

    return 0;
}

