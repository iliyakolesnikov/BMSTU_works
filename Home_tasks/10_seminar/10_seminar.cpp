#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iomanip>

using namespace std;

// Задача 1: Чтение файла и вывод содержимого на экран
int main1() {
    ifstream file("input.txt");
    if (file.fail()) {
        cout << "Файл input.txt не найден!" << endl;
        return 0;
    }
    string line;
    cout << "Содержимое файла:\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
    return 0;
}

// Задача 2: Подсчёт количества строк в файле
int main2() {
    ifstream file("data.txt");
    string line;
    int count = 0;
    while (getline(file, line)) {
        count++;
    }
    cout << "Количество строк в файле: " << count << endl;
    file.close();
    return 0;
}

// Задача 3: Подсчёт количества слов в файле
int main3() {
    ifstream file("text.txt");
    string word;
    int count = 0;
    while (file >> word) {
        count++;
    }
    cout << "Количество слов в файле: " << count << endl;
    file.close();
    return 0;
}

// Задача 4: Копирование содержимого одного файла в другой
int main4() {
    ifstream in("source.txt");
    ofstream out("copy.txt");
    string line;
    int count = 0;
    while (getline(in, line)) {
        out << line << '\n';
        count++;
    }
    in.close();
    out.close();
    cout << "Файл успешно скопирован.\nКоличество скопированных строк: " << count << endl;
    return 0;
}

// Задача 5: Подсчёт количества символов в файле
int main5() {
    ifstream file("input.txt");
    char ch;
    int count = 0;
    while (file.get(ch)) {
        count++;
    }
    cout << "Количество символов в файле: " << count << endl;
    file.close();
    return 0;
}

// Задача 6: Запись пользовательского ввода в файл
int main6() {
    ofstream file("output.txt");
    string line;
    cout << "Введите строки (пустая строка завершает ввод):\n";
    while (getline(cin, line) && !line.empty()) {
        file << line << '\n';
    }
    file.close();
    cout << "Данные записаны в файл output.txt." << endl;
    return 0;
}

// Задача 7: Подсчёт количества чисел, суммы и среднего
int main7() {
    ifstream file("numbers.txt");
    int num;
    int count = 0, sum = 0;
    while (file >> num) {
        sum += num;
        count++;
    }
    double avg = count ? (double)sum / count : 0;
    cout << "Количество чисел: " << count << " Сумма: " << sum << " Среднее: " << avg << endl;
    file.close();
    return 0;
}

// Задача 8: Сравнение двух файлов построчно
int main8() {
    ifstream f1("file1.txt"), f2("file2.txt");
    string line1, line2;
    bool identical = true;

    while (getline(f1, line1) && getline(f2, line2)) {
        if (line1 != line2) {
            identical = false;
            break;
        }
    }
    // Проверяем, не осталось ли "хвоста" в одном из файлов
    if (getline(f1, line1) || getline(f2, line2)) {
        identical = false;
    }

    if (identical) {
        cout << "Файлы идентичны." << endl;
    } else {
        cout << "Файлы различаются." << endl;
    }

    f1.close();
    f2.close();
    return 0;
}

// Задача 9: Анализ температурных данных
int main9() {
    ifstream in("temperature_data.txt");
    ofstream out("report.txt");
    map<string, vector<double>> sensors;
    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name;
        double temp;
        while (ss >> name >> temp) {
            sensors[name].push_back(temp);
        }
    }
    in.close();

    for (const auto& s : sensors) {
        const vector<double>& vals = s.second;
        double min_val = *min_element(vals.begin(), vals.end());
        double max_val = *max_element(vals.begin(), vals.end());
        double avg_val = accumulate(vals.begin(), vals.end(), 0.0) / vals.size();
        out << s.first << ": min= " << min_val << ", max= " << max_val
            << ", avg= " << fixed << setprecision(1) << avg_val << endl;
    }
    out.close();
    cout << "Отчёт о температурных данных сохранён в report.txt" << endl;
    return 0;
}

// Задача 10: Учёт энергопотребления оборудования
int main10() {
    ifstream in("power_log.txt");
    ofstream out("energy_report.txt");
    map<string, vector<double>> devices;
    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string timestamp, dev;
        double power;
        ss >> timestamp >> dev >> power;
        devices[dev].push_back(power);
    }
    in.close();

    for (const auto& dev : devices) {
        const vector<double>& vals = dev.second;
        int count = vals.size();
        double total = accumulate(vals.begin(), vals.end(), 0.0);
        double avg = total / count;
        out << dev.first << ": measurements= " << count
            << ", total= " << fixed << setprecision(2) << total << " kWh"
            << ", average= " << fixed << setprecision(2) << avg << " kW" << endl;
    }
    out.close();
    cout << "Анализ завершён. Результаты сохранены в energy_report.txt" << endl;
    return 0;
}

// Задача 11: Анализ вибрационных данных
int main11() {
    ifstream in("vibration_log.txt");
    ofstream out("vibration_report.txt");
    vector<double> data;
    double val;

    while (in >> val) {
        data.push_back(val);
    }
    in.close();

    // Фильтрация значений выше 0.05
    vector<double> filtered;
    copy_if(data.begin(), data.end(), back_inserter(filtered),
            [](double x) { return x > 0.05; });

    if (data.empty()) {
        out << "Нет данных для анализа." << endl;
        cout << "Анализ вибрационных данных завершён. Отчёт сохранён в vibration_report.txt" << endl;
        out.close();
        return 0;
    }

    double avg = accumulate(data.begin(), data.end(), 0.0) / data.size();
    double min_val = filtered.empty() ? 0.0 : *min_element(filtered.begin(), filtered.end());
    double max_val = filtered.empty() ? 0.0 : *max_element(filtered.begin(), filtered.end());

    out << "Количество измерений: " << data.size() << endl;
    out << "Фильтрованные значения(>0.05):";
    for (double v : filtered) {
        out << " " << v;
    }
    out << endl;
    out << "Среднее значение: " << fixed << setprecision(4) << avg << endl;
    if (!filtered.empty()) {
        out << "Минимум: " << min_val << endl;
        out << "Максимум: " << max_val << endl;
    } else {
        out << "Минимум: нет значений >0.05" << endl;
        out << "Максимум: нет значений >0.05" << endl;
    }
    out.close();

    cout << "Анализ вибрационных данных завершён. Отчёт сохранён в vibration_report.txt" << endl;
    return 0;
}

// Основная функция — запускает все задачи по порядку
int main() {
    cout << "=== Задача 1 ===" << endl;
    main1();
    cout << "\n=== Задача 2 ===" << endl;
    main2();
    cout << "\n=== Задача 3 ===" << endl;
    main3();
    cout << "\n=== Задача 4 ===" << endl;
    main4();
    cout << "\n=== Задача 5 ===" << endl;
    main5();
    cout << "\n=== Задача 6 ===" << endl;
    main6();
    cout << "\n=== Задача 7 ===" << endl;
    main7();
    cout << "\n=== Задача 8 ===" << endl;
    main8();
    cout << "\n=== Задача 9 ===" << endl;
    main9();
    cout << "\n=== Задача 10 ===" << endl;
    main10();
    cout << "\n=== Задача 11 ===" << endl;
    main11();
    return 0;
}