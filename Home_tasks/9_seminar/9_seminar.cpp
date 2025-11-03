#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
#include <iomanip>

using namespace std;

// Задача 1: Простое использование std::unique_ptr<int>
int main1() {
    auto ptr = make_unique<int>(10);
    cout << "Значение: " << *ptr << endl;
    
    *ptr = 25;
    cout << "Новое значение: " << *ptr << endl;
    
    return 0;
}

// Задача 2: Массив через std::unique_ptr<int[]>
int main2() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;
    
    auto arr = make_unique<int[]>(n);
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}

// Задача 3: Заполнение массива через функцию
void fillArray(unique_ptr<int[]>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
    }
}

int main3() {
    int n = 5;
    auto arr = make_unique<int[]>(n);
    
    fillArray(arr, n);
    
    cout << "Массив квадратов: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}

// Задача 4: Передача владения через std::move
int main4() {
    auto ptr1 = make_unique<int>(42);
    cout << "ptr1: " << *ptr1 << endl;
    
    auto ptr2 = move(ptr1);
    
    cout << "После move:" << endl;
    cout << "ptr1: " << (ptr1 ? "не nullptr" : "nullptr") << endl;
    cout << "ptr2: " << *ptr2 << endl;
    
    return 0;
}

// Задача 5: Двумерная таблица
int main5() {
    int n = 3, m = 4;
    auto arr = make_unique<int[]>(n * m);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i * m + j] = i * j;
        }
    }
    
    cout << "Таблица произведений:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(3) << arr[i * m + j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}

// Задача 6: Совместное владение через std::shared_ptr<int>
int main6() {
    auto ptr1 = make_shared<int>(100);
    cout << "use_count после создания: " << ptr1.use_count() << endl;
    
    auto ptr2 = ptr1;
    auto ptr3 = ptr1;
    cout << "use_count после создания копий: " << ptr1.use_count() << endl;
    
    ptr2.reset();
    cout << "use_count после удаления ptr2: " << ptr1.use_count() << endl;
    cout << "Значение: " << *ptr1 << endl;
    
    return 0;
}

// Задача 7: Анализ строки с unique_ptr
int main7() {
    string text = "Hello World Programming";
    int length = text.length();
    
    auto charArray = make_unique<char[]>(length + 1);
    copy(text.begin(), text.end(), charArray.get());
    charArray[length] = '\0';
    
    int vowels = 0, consonants = 0;
    string vowelsStr = "aeiouAEIOU";
    
    for (int i = 0; i < length; i++) {
        if (isalpha(charArray[i])) {
            if (vowelsStr.find(charArray[i]) != string::npos) {
                vowels++;
            } else {
                consonants++;
            }
        }
    }
    
    auto vowelArray = make_unique<char[]>(vowels + 1);
    int index = 0;
    for (int i = 0; i < length; i++) {
        if (vowelsStr.find(charArray[i]) != string::npos) {
            vowelArray[index++] = charArray[i];
        }
    }
    vowelArray[vowels] = '\0';
    
    cout << "Исходная строка: " << charArray.get() << endl;
    cout << "Гласных: " << vowels << ", Согласных: " << consonants << endl;
    cout << "Только гласные: " << vowelArray.get() << endl;
    
    return 0;
}

// Задача 8: Несколько массивов с unique_ptr
int main8() {
    int size = 5;
    
    auto temperatures = make_unique<double[]>(size);
    auto pressures = make_unique<double[]>(size);
    auto humidities = make_unique<double[]>(size);
    
    // Заполнение данными
    double tempData[] = {20.5, 22.1, 19.8, 21.3, 23.0};
    double pressData[] = {1013.2, 1012.8, 1014.1, 1013.5, 1012.9};
    double humidData[] = {45.0, 47.5, 43.2, 46.8, 44.1};
    
    copy(tempData, tempData + size, temperatures.get());
    copy(pressData, pressData + size, pressures.get());
    copy(humidData, humidData + size, humidities.get());
    
    auto calculateAverage = [](const unique_ptr<double[]>& arr, int n) {
        double sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i];
        }
        return sum / n;
    };
    
    cout << "| Параметр    | Среднее значение |" << endl;
    cout << "|-------------|------------------|" << endl;
    cout << "| Температура | " << fixed << setprecision(1) 
         << calculateAverage(temperatures, size) << "°C      |" << endl;
    cout << "| Давление    | " << fixed << setprecision(1) 
         << calculateAverage(pressures, size) << " hPa  |" << endl;
    cout << "| Влажность   | " << fixed << setprecision(1) 
         << calculateAverage(humidities, size) << "%       |" << endl;
    
    return 0;
}

// Задача 9: Совместный буфер через std::shared_ptr<std::vector<int>>
void processA(shared_ptr<vector<int>> buf) {
    for (auto& num : *buf) {
        num += 1;
    }
}

void processB(shared_ptr<vector<int>> buf) {
    for (auto& num : *buf) {
        num *= 2;
    }
}

int main9() {
    auto buffer = make_shared<vector<int>>();
    
    for (int i = 1; i <= 10; i++) {
        buffer->push_back(i);
    }
    
    cout << "Исходный буфер: ";
    for (auto num : *buffer) {
        cout << num << " ";
    }
    cout << endl;
    
    processA(buffer);
    cout << "После processA: ";
    for (auto num : *buffer) {
        cout << num << " ";
    }
    cout << endl;
    
    processB(buffer);
    cout << "После processB: ";
    for (auto num : *buffer) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}

// Задача 10: Возврат unique_ptr из функции
unique_ptr<int[]> createArray(int n) {
    auto arr = make_unique<int[]>(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

int main10() {
    int n = 6;
    auto arr = createArray(n);
    
    cout << "Массив из функции: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}

// Задача 11: Обработка сигналов датчиков
int main11() {
    vector<double> signals = {25.4, 27.1, 30.0, 29.5, 28.3};
    int n = signals.size();
    
    auto signalArray = make_unique<double[]>(n);
    copy(signals.begin(), signals.end(), signalArray.get());
    
    auto mean = [](const unique_ptr<double[]>& arr, int size) {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }
        return sum / size;
    };
    
    auto normalize = [](unique_ptr<double[]>& arr, int size, double maxVal) {
        for (int i = 0; i < size; i++) {
            arr[i] /= maxVal;
        }
    };
    
    auto copyBack = [](unique_ptr<double[]>& src, vector<double>& dest, int size) {
        for (int i = 0; i < size; i++) {
            dest[i] = src[i];
        }
    };
    
    cout << "Исходные данные: ";
    for (auto val : signals) {
        cout << val << " ";
    }
    cout << endl;
    
    double average = mean(signalArray, n);
    cout << "Среднее значение: " << fixed << setprecision(2) << average << endl;
    
    double maxSignal = *max_element(signals.begin(), signals.end());
    normalize(signalArray, n, maxSignal);
    copyBack(signalArray, signals, n);
    
    cout << "Нормализованные сигналы: ";
    for (auto val : signals) {
        cout << fixed << setprecision(3) << val << " ";
    }
    cout << endl;
    
    return 0;
}

// Задача 12: Фильтрация логов системы
int main12() {
    vector<string> logs = {
        "INFO: Start",
        "ERROR: Disk failure", 
        "WARNING: Low memory",
        "ERROR: Disk failure",
        "INFO: Stop"
    };
    
    auto logPtr = make_shared<vector<string>>(logs);
    
    vector<string> errors;
    auto errorFilter = [](const string& log) {
        return log.find("ERROR") != string::npos;
    };
    
    copy_if(logPtr->begin(), logPtr->end(), back_inserter(errors), errorFilter);
    
    sort(errors.begin(), errors.end());
    errors.erase(unique(errors.begin(), errors.end()), errors.end());
    
    cout << "Исходный журнал:" << endl;
    for (const auto& log : *logPtr) {
        cout << log << endl;
    }
    
    cout << "\nОшибки:" << endl;
    for (const auto& error : errors) {
        cout << error << endl;
    }
    
    return 0;
}

// Задача 13: Объединение текстовых блоков
int main13() {
    auto part1 = make_unique<string>("Sensor data:");
    auto part2 = make_unique<string>("Voltage stable.");
    auto part3 = make_unique<string>("System nominal.");
    
    vector<unique_ptr<string>> reportParts;
    reportParts.push_back(move(part1));
    reportParts.push_back(move(part2));
    reportParts.push_back(move(part3));
    
    auto concatParts = [](const vector<unique_ptr<string>>& parts) {
        string result;
        for (const auto& part : parts) {
            result += *part + "\n";
        }
        return result;
    };
    
    auto countWord = [](const string& text, const string& word) {
        int count = 0;
        size_t pos = 0;
        while ((pos = text.find(word, pos)) != string::npos) {
            count++;
            pos += word.length();
        }
        return count;
    };
    
    string report = concatParts(reportParts);
    int dataCount = countWord(report, "data");
    
    cout << "Отчёт:\n" << report << endl;
    cout << "Слово \"data\" встречается " << dataCount << " раз" << endl;
    
    return 0;
}

// Задача 14: Матричный анализ
int main14() {
    int n = 3, m = 3;
    
    auto matrix = make_unique<double[]>(n * m);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    copy(data, data + n * m, matrix.get());
    
    auto sumColumns = [&]() {
        vector<double> sums(m, 0);
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                sums[j] += matrix[i * m + j];
            }
        }
        return sums;
    };
    
    auto maxIndex = [](const vector<double>& sums) {
        return max_element(sums.begin(), sums.end()) - sums.begin();
    };
    
    auto columnSums = sumColumns();
    int maxCol = maxIndex(columnSums);
    
    cout << "Матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i * m + j] << " ";
        }
        cout << endl;
    }
    
    cout << "Суммы столбцов: [";
    for (size_t i = 0; i < columnSums.size(); i++) {
        cout << columnSums[i] << (i < columnSums.size() - 1 ? ", " : "");
    }
    cout << "]" << endl;
    
    cout << "Столбец с максимальной суммой: " << maxCol + 1 
         << " (" << columnSums[maxCol] << ")" << endl;
    
    return 0;
}

// Задача 15: Анализ маршрутов
int main15() {
    vector<string> routes = {
        "Moscow-Berlin",
        "Berlin-Paris", 
        "Paris-Rome",
        "Rome-Moscow"
    };
    
    auto pRoutes = make_shared<vector<string>>(routes);
    
    auto countCity = [](shared_ptr<vector<string>> routes, const string& city) {
        return count_if(routes->begin(), routes->end(), 
            [&](const string& route) {
                return route.find(city) != string::npos;
            });
    };
    
    auto sortByLength = [](shared_ptr<vector<string>> routes) {
        sort(routes->begin(), routes->end(), 
            [](const string& a, const string& b) {
                return a.length() > b.length();
            });
    };
    
    auto concat = [](shared_ptr<vector<string>> routes) {
        string result;
        for (size_t i = 0; i < routes->size(); i++) {
            result += (*routes)[i];
            if (i < routes->size() - 1) {
                result += " -> ";
            }
        }
        return result;
    };
    
    int parisCount = countCity(pRoutes, "Paris");
    cout << "Количество маршрутов с \"Paris\": " << parisCount << endl;
    
    sortByLength(pRoutes);
    cout << "Отсортированные маршруты:" << endl;
    for (const auto& route : *pRoutes) {
        cout << route << endl;
    }
    
    string combined = concat(pRoutes);
    cout << "\nОбщий маршрут:\n" << combined << endl;
    
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
    return 0;
}