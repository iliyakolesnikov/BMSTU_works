#include <iostream>
#include <cstring>
#include <cctype>
#include <climits>

using namespace std;

// Функция для поиска самой короткой общей подстроки (дополнительное задание)
string findShortestCommonSubstring(const string& word1, const string& word2) {
    int len1 = word1.length();
    int len2 = word2.length();
    string shortestCommon = "";
    
    // Перебираем все возможные подстроки первого слова
    for (int i = 0; i < len1; i++) {
        for (int j = i + 1; j <= len1; j++) {
            string substring = word1.substr(i, j - i);
            
            // Проверяем, содержится ли эта подстрока во втором слове
            if (word2.find(substring) != string::npos) {
                // Если это первая найденная подстрока или она короче предыдущей самой короткой
                if (shortestCommon.empty() || substring.length() < shortestCommon.length()) {
                    shortestCommon = substring;
                }
            }
        }
    }
    
    return shortestCommon;
}

int main() {
    const int MAX_LENGTH = 256;
    char input[MAX_LENGTH];
    
    // Ввод строки от пользователя
    cout << "Введите строку из 10 слов на латинице: ";
    cin.getline(input, MAX_LENGTH);
    
    // 1. Найти количество слов, оканчивающихся на букву 'a'
    int countEndsWithA = 0;
    
    // 2. Найти длину самого короткого слова
    int minLength = INT_MAX;
    
    // 3. Подсчитать количество букв 'b' во втором слове строки
    int countBInSecondWord = 0;
    int wordCount = 0;
    
    // 5. Найти количество слов, у которых первый и последний символы совпадают
    int countSameFirstLast = 0;
    
    // Для дополнительного задания
    string words[10];
    int wordIndex = 0;
    
    // Разделение строки на слова
    char* token = strtok(input, " ,.!?;:");
    while (token != nullptr && wordCount < 10) {
        string word = token;
        words[wordIndex++] = word;
        int wordLen = strlen(token);
        
        // 1. Проверка окончания на 'a'
        if (wordLen > 0 && tolower(token[wordLen - 1]) == 'a') {
            countEndsWithA++;
        }
        
        
        // 2. Поиск самого короткого слова
        if (wordLen < minLength) {
            minLength = wordLen;
        }

        
        // 3. Подсчет 'b' во втором слове
        if (wordCount == 1) { // Второе слово (индекс 1)
            for (int i = 0; i < wordLen; i++) {
                if (tolower(token[i]) == 'b') {
                    countBInSecondWord++;
                }
            }
        }

        
        // 5. Проверка совпадения первого и последнего символа
        if (wordLen > 0 && tolower(token[0]) == tolower(token[wordLen - 1])) {
            countSameFirstLast++;
        }
        
        wordCount++;
        token = strtok(nullptr, " ,.!?;:");
    }

    
    // 4. Заменить все буквы в верхнем регистре на строчные
    char lowerCaseString[MAX_LENGTH];
    strcpy(lowerCaseString, input);
    
    for (int i = 0; lowerCaseString[i] != '\0'; i++) {
        if (isupper(lowerCaseString[i])) {
            lowerCaseString[i] = tolower(lowerCaseString[i]);
        }
    }

    
    // *6. Найти самую короткую общую подстроку между двумя словами
    string shortestCommonSubstring = "";
    if (wordCount >= 2) {
        shortestCommonSubstring = findShortestCommonSubstring(words[0], words[1]);
        
        // Ищем среди всех пар слов
        for (int i = 0; i < wordCount; i++) {
            for (int j = i + 1; j < wordCount; j++) {
                string common = findShortestCommonSubstring(words[i], words[j]);
                if (!common.empty()) {
                    if (shortestCommonSubstring.empty() || 
                        common.length() < shortestCommonSubstring.length()) {
                        shortestCommonSubstring = common;
                    }
                }
            }
        }
    }

    
    // Вывод результатов
    cout << "\n=== РЕЗУЛЬТАТЫ ===" << endl;
    cout << "1. Количество слов, оканчивающихся на 'a': " << countEndsWithA << endl;
    cout << "2. Длина самого короткого слова: " << minLength << endl;
    cout << "3. Количество букв 'b' во втором слове: " << countBInSecondWord << endl;
    cout << "4. Строка в нижнем регистре: " << lowerCaseString << endl;
    cout << "5. Количество слов с одинаковыми первым и последним символами: " << countSameFirstLast << endl;
    
    if (!shortestCommonSubstring.empty()) {
        cout << "6. Самая короткая общая подстрока: " << shortestCommonSubstring << endl;
    } else {
        cout << "6. Общая подстрока не найдена" << endl;
    }
    
    return 0;
}