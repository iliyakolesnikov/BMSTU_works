#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;       //тип данных строка
    cout << "Введите строку: ";
    getline(cin, s);       //читает строку и сохраняет в переменную s

    string gl = "aeiouAEIOU";
    int cnt = 0;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (gl.find(c) != string::npos) {        //ищет позицию гласной буквы и если символ найден то увеличиваем счетчик на 1
            cnt++;
        }
    }
    cout << "Количество гласных: " << cnt << endl;
    return 0;
}