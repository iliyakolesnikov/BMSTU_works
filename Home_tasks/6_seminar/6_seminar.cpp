#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;



// Задача 1: Проверка палиндрома
int main() {
    char str[100];
    cout << "Введите строку: ";
    cin.getline(str, 100);
    
    int left = 0;
    int right = strlen(str) - 1;
    bool isPalindrome = true;
    
    while (left < right) {
        // Пропускаем пробелы слева
        while (left < right && isspace(str[left])) left++;
        // Пропускаем пробелы справа
        while (left < right && isspace(str[right])) right--;
        
        // Сравниваем символы без учета регистра
        if (tolower(str[left]) != tolower(str[right])) {
            isPalindrome = false;
            break;
        }        
        left++;
        right--;
    }    
    cout << (isPalindrome ? "Палиндром" : "Не палиндром") << endl;
    return 0;
}


// Задача 2: Подсчет уникальных символов
int main() {
    char str[100];
    cout << "Введите строку: ";
    cin.getline(str, 100);
    
    int count = 0;
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        bool found = false;
        // Проверяем, встречался ли символ ранее
        for (int j = 0; j < i; j++) {
            if (str[j] == str[i]) {
                found = true;
                break;
            }
        }
        if (!found) count++;
    }
    
    cout << "Уникальных символов: " << count << endl;
    return 0;
}


// Задача 3: Удаление всех цифр из строки
int main() {
    char str[100];
    cout << "Введите строку: ";
    cin.getline(str, 100);
    
    int writeIndex = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            str[writeIndex++] = str[i];
        }
    }
    str[writeIndex] = '\0';
    
    cout << "Результат: " << str << endl;
    return 0;
}


// Задача 4: Проверка содержания всех символов
int main() {
    char A[100], B[100];
    cout << "Введите строку A: ";
    cin.getline(A, 100);
    cout << "Введите строку B: ";
    cin.getline(B, 100);
    
    bool allFound = true;
    for (int i = 0; B[i] != '\0'; i++) {
        bool found = false;
        for (int j = 0; A[j] != '\0'; j++) {
            if (B[i] == A[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            allFound = false;
            break;
        }
    }
    
    cout << (allFound ? "Да" : "Нет") << endl;
    return 0;
}


// Задача 5: Подсчет гласных и согласных
int main() {
    char str[100];
    cout << "Введите строку: ";
    cin.getline(str, 100);
    
    int vowels = 0, consonants = 0;
    char vowelChars[] = "aeiouyAEIOUY";
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            bool isVowel = false;
            for (int j = 0; vowelChars[j] != '\0'; j++) {
                if (str[i] == vowelChars[j]) {
                    isVowel = true;
                    break;
                }
            }
            if (isVowel) vowels++;
            else consonants++;
        }
    }
    
    cout << "Гласных: " << vowels << endl;
    cout << "Согласных: " << consonants << endl;
    return 0;
}


// Задача 6: шифр Цезаря
int main() {
    char text[100];
    int shift;
    
    cout << "Введите текст: ";
    cin.getline(text, 100);
    cout << "Введите сдвиг: ";
    cin >> shift;
    cin.ignore(); // очистка буфера
    
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
            if (text[i] < 'A') text[i] += 26;
        } else if (islower(text[i])) {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
            if (text[i] < 'a') text[i] += 26;
        }
    }
    
    cout << "Заintифрованный текст: " << text << endl;
    return 0;
}


// Задача 7: Сжатие строки (RLE)
int main() {
    char str[100];
    cout << "Введите строку: ";
    cin.getline(str, 100);
    
    char result[200] = "";
    int len = strlen(str);
    int index = 0;
    
    for (int i = 0; i < len; i++) {
        char current = str[i];
        int count = 1;
        
        // Подсчитываем количество повторений
        while (i + 1 < len && str[i + 1] == current) {
            count++;
            i++;
        }
        
        // Добавляем символ и количество в результат
        result[index++] = current;
        result[index++] = count + '0';
    }
    result[index] = '\0';
    
    cout << "Сжатая строка: " << result << endl;
    return 0;
}


// Задача 8: Коррекция регистра в предложении
int main() {
    char text[200];
    cout << "Введите текст: ";
    cin.getline(text, 200);
    
    bool newSentence = true;
    int len = strlen(text);
    
    for (int i = 0; i < len; i++) {
        if (newSentence && isalpha(text[i])) {
            text[i] = toupper(text[i]);
            newSentence = false;
        } else {
            text[i] = tolower(text[i]);
        }
        
        // Проверяем конец предложения
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            newSentence = true;
        }
    }
    
    cout << "Исправленный текст: " << text << endl;
    return 0;
}


// Задача 9: Наибольшая общая подстрока
int main() {
    char str1[100], str2[100];
    cout << "Введите первую строку: ";
    cin.getline(str1, 100);
    cout << "Введите вторую строку: ";
    cin.getline(str2, 100);
    
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    // Создаем динамический массив
    int** dp = new int*[len1 + 1];
    for (int i = 0; i <= len1; i++) {
        dp[i] = new int[len2 + 1]();
    }
    
    int maxLength = 0;
    int endPos = 0;
    
    // Заполняем массив dp
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endPos = i - 1;
                }
            }
        }
    }
    
    // Выводим результат
    if (maxLength > 0) {
        cout << "Наибольintая общая подстрока: ";
        for (int i = endPos - maxLength + 1; i <= endPos; i++) {
            cout << str1[i];
        }
        cout << endl;
    } else {
        cout << "Общих подстрок нет" << endl;
    }
    
    // Освобождаем память
    for (int i = 0; i <= len1; i++) {
        delete[] dp[i];
    }
    delete[] dp;
    return 0;
}


// Задача 10: Инвертирование слов
int main0() {
    char text[100];
    cout << "Введите строку: ";
    cin.getline(text, 100);
    
    int len = strlen(text);
    int start = 0;
    
    for (int i = 0; i <= len; i++) {
        if (text[i] == ' ' || text[i] == '\0') {
            // Переворачиваем слово
            reverse(text + start, text + i);
            start = i + 1;
        }
    }
    
    cout << "Результат: " << text << endl;
    return 0;
}


// Задача 11: Подстроки с уникальными символами
int main1() {
    char str[100];
    int k;
    
    cout << "Введите строку: ";
    cin.getline(str, 100);
    cout << "Введите k: ";
    cin >> k;
    
    int len = strlen(str);
    
    for (int i = 0; i <= len - k; i++) {
        bool unique = true;
        
        // Проверяем, все ли символы в подстроке уникальны
        for (int j = i; j < i + k; j++) {
            for (int m = j + 1; m < i + k; m++) {
                if (str[j] == str[m]) {
                    unique = false;
                    break;
                }
            }
            if (!unique) break;
        }
        
        // Выводим подстроку если все символы уникальны
        if (unique) {
            for (int j = i; j < i + k; j++) {
                cout << str[j];
            }
            cout << endl;
        }
    }
    return 0;
}    
    
