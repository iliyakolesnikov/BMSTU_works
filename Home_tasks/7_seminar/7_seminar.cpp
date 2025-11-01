#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

// Задача 1: Подсчёт длины строки вручную
int myStrLen(const char* str) {
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

int main1() {
    const char* text = "Hello, World!";
    cout << "Длина строки: " << myStrLen(text) << endl;
    return 0;
}

// Задача 2: Копирование строки вручную
void myStrCopy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int main2() {
    char source[] = "Source string";
    char destination[50];
    myStrCopy(destination, source);
    cout << "Скопированная строка: " << destination << endl;
    return 0;
}

// Задача 3: Конкатенация двух строк
void myStrCat(char* dest, const char* src) {
    while (*dest != '\0') dest++;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int main3() {
    char str1[50] = "Hello, ";
    char str2[] = "World!";
    myStrCat(str1, str2);
    cout << "Результат конкатенации: " << str1 << endl;
    return 0;
}

// Задача 4: Подсчёт количества определённого символа в строке
int main4() {
    char text[] = "programming";
    char target = 'm';
    int count = 0;
    const char* ptr = text;
    
    while (*ptr != '\0') {
        if (*ptr == target) count++;
        ptr++;
    }
    
    cout << "Символ '" << target << "' встречается " << count << " раз(а)" << endl;
    return 0;
}

// Задача 5: Замена символа в строке
int main5() {
    char text[] = "Hello world, how are you?";
    char* ptr = text;
    
    while (*ptr != '\0') {
        if (*ptr == ' ') *ptr = '_';
        ptr++;
    }
    
    cout << "Результат замены: " << text << endl;
    return 0;
}

// Задача 6: Реверс строки
void reverse(char* str) {
    char* start = str;
    char* end = str;
    
    while (*end != '\0') end++;
    end--;
    
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main6() {
    char text[] = "abcdef";
    reverse(text);
    cout << "Перевернутая строка: " << text << endl;
    return 0;
}

// Задача 7: Проверка на палиндром
bool isPalindrome(const char* str) {
    const char* start = str;
    const char* end = str;
    
    while (*end != '\0') end++;
    end--;
    
    while (start < end) {
        if (*start != *end) return false;
        start++;
        end--;
    }
    return true;
}

int main7() {
    const char* text1 = "radar";
    const char* text2 = "hello";
    
    cout << text1 << " - " << (isPalindrome(text1) ? "палиндром" : "не палиндром") << endl;
    cout << text2 << " - " << (isPalindrome(text2) ? "палиндром" : "не палиндром") << endl;
    return 0;
}

// Задача 8: Поиск подстроки в строке
const char* findSubstring(const char* text, const char* word) {
    const char* textPtr = text;
    const char* wordPtr;
    
    while (*textPtr != '\0') {
        const char* temp = textPtr;
        wordPtr = word;
        
        while (*wordPtr != '\0' && *temp == *wordPtr) {
            temp++;
            wordPtr++;
        }
        
        if (*wordPtr == '\0') return textPtr;
        textPtr++;
    }
    
    return nullptr;
}

int main8() {
    const char* text = "Hello, World!";
    const char* word = "World";
    
    const char* result = findSubstring(text, word);
    if (result != nullptr) {
        cout << "Подстрока найдена: " << result << endl;
    } else {
        cout << "Подстрока не найдена" << endl;
    }
    return 0;
}

// Задача 9: Удаление пробелов из строки
void removeSpaces(char* str) {
    char* dest = str;
    char* src = str;
    
    while (*src != '\0') {
        if (*src != ' ') {
            *dest = *src;
            dest++;
        }
        src++;
    }
    *dest = '\0';
}

int main9() {
    char text[] = "H e l l o   W o r l d !";
    removeSpaces(text);
    cout << "Без пробелов: " << text << endl;
    return 0;
}

// Задача 10: Сравнение двух строк
int myStrCmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int main10() {
    const char* str1 = "apple";
    const char* str2 = "banana";
    const char* str3 = "apple";
    
    cout << "Сравнение '" << str1 << "' и '" << str2 << "': " << myStrCmp(str1, str2) << endl;
    cout << "Сравнение '" << str2 << "' и '" << str1 << "': " << myStrCmp(str2, str1) << endl;
    cout << "Сравнение '" << str1 << "' и '" << str3 << "': " << myStrCmp(str1, str3) << endl;
    return 0;
}

// Задача 11: Сумма элементов вектора через указатель
int main11() {
    vector<int> vec = {1, 2, 3, 4, 5};
    int sum = 0;
    int* p = &vec[0];
    
    for (size_t i = 0; i < vec.size(); i++) {
        sum += *(p + i);
    }
    
    cout << "Сумма элементов: " << sum << endl;
    return 0;
}

// Задача 12: Увеличение всех элементов вектора на 10
int main12() {
    vector<int> vec = {1, 2, 3, 4, 5};
    int* p = vec.data();
    
    for (size_t i = 0; i < vec.size(); i++) {
        *(p + i) += 10;
    }
    
    cout << "После увеличения: ";
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}

// Задача 13: Обработка телеметрического пакета
void parseTelemetry(const char* data) {
    const char* ptr = data;
    
    while (*ptr != '\0') {
        // Пропускаем пробелы в начале
        while (*ptr == ' ') ptr++;
        
        // Читаем имя параметра
        const char* nameStart = ptr;
        while (*ptr != ':' && *ptr != '\0') ptr++;
        if (*ptr == '\0') break;
        
        // Читаем значение
        const char* valueStart = ++ptr;
        while (*ptr != ';' && *ptr != '\0') ptr++;
        
        // Выводим результат
        cout << string(nameStart, valueStart - 1) << ": " << string(valueStart, ptr) << endl;
        
        if (*ptr == ';') ptr++;
    }
}

int main13() {
    const char* data = "TEMP:24.5;PRESS:101.3;HUM:55.2";
    parseTelemetry(data);
    return 0;
}

// Задача 14: Анализ временного ряда
double computeRMS(const vector<double>& signal) {
    const double* p = signal.data();
    double sum = 0.0;
    size_t n = signal.size();
    
    for (size_t i = 0; i < n; i++) {
        sum += (*(p + i)) * (*(p + i));
    }
    
    return sqrt(sum / n);
}

int main14() {
    vector<double> signal = {2.0, 3.0, 1.0, 4.0, 3.0};
    double rms = computeRMS(signal);
    cout << "RMS value: " << rms << endl;
    return 0;
}

// Задача 15: Буфер команд управления роботом
struct Command {
    string name;
    int value;
};

void parseCommand(const char* input, vector<Command>& buffer) {
    const char* ptr = input;
    
    // Читаем имя команды
    string name;
    while (*ptr != ' ' && *ptr != '\0') {
        name += *ptr;
        ptr++;
    }
    
    // Читаем значение (если есть)
    int value = 0;
    if (*ptr == ' ') {
        ptr++;
        value = atoi(ptr);
    }
    
    buffer.push_back({name, value});
}

int main15() {
    vector<Command> buffer;
    parseCommand("FORWARD 10", buffer);
    parseCommand("TURN 90", buffer);
    parseCommand("STOP", buffer);
    
    for (const auto& cmd : buffer) {
        cout << "Command: " << cmd.name << ", Value: " << cmd.value << endl;
    }
    return 0;
}

// Задача 16: Анализ параметров производственного процесса
void analyzePressure(const vector<double>& data, double& minVal, double& maxVal, double& avgVal) {
    const double* p = data.data();
    size_t n = data.size();
    
    if (n == 0) return;
    
    minVal = *p;
    maxVal = *p;
    double sum = 0.0;
    
    for (size_t i = 0; i < n; i++) {
        double current = *(p + i);
        if (current < minVal) minVal = current;
        if (current > maxVal) maxVal = current;
        sum += current;
    }
    
    avgVal = sum / n;
}

int main16() {
    vector<double> pressure = {101.3, 100.8, 101.9, 100.5, 102.0};
    double minVal, maxVal, avgVal;
    
    analyzePressure(pressure, minVal, maxVal, avgVal);
    
    cout << "Min pressure: " << minVal << endl;
    cout << "Max pressure: " << maxVal << endl;
    cout << "Average pressure: " << avgVal << endl;
    return 0;
}

// Главная функция для запуска всех задач
int main() {
    main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    main7();
    main8();
    main9();
    main10();
    main11();
    main12();
    main13();
    main14();
    main15();
    main16();
    return 0;
}

