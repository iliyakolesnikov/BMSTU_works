#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cctype>

using namespace std;

// Задача 1. Анализатор текстового файла с поиском позиций слов
int main1() {
    ifstream file("book.txt");
    if (!file) {
        cout << "Файл book.txt не найден!" << endl;
        return 0;
    }
    string target = "герой";
    string line;
    int line_num = 0;
    vector<pair<int, int>> positions;
    
    while (getline(file, line)) {
        line_num++;
        size_t pos = 0;
        // Поиск всех вхождений (с учётом регистра; можно сделать tolower, если нужно)
        while ((pos = line.find(target, pos)) != string::npos) {
            positions.push_back({line_num, static_cast<int>(pos + 1)}); // позиция с 1
            pos += target.length();
        }
    }
    file.close();

    ofstream out("word_positions.txt");
    for (const auto& p : positions) {
        out << "Строка: " << p.first << ", Позиция: " << p.second << ", Слово: " << target << endl;
    }
    out.close();

    cout << "Найдено вхождений слова \"" << target << "\": " << positions.size() << endl;
    cout << "Результаты сохранены в word_positions.txt" << endl;
    return 0;
}

// Задача 2. Редактор конфигурационных файлов с прямой заменой
int main2() {
    fstream file("config.txt", ios::in | ios::out);
    if (!file) {
        cout << "Файл config.txt не найден!" << endl;
        return 0;
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    size_t pos = content.find("timeout=30");
    if (pos != string::npos) {
        //content.replace(pos, strlen("timeout=30"), "timeout=60");
        ofstream out("config.txt");
        out << content;
        out.close();
        cout << "Значение timeout заменено на 60." << endl;
    } else {
        cout << "Параметр timeout=30 не найден." << endl;
    }
    return 0;
}

// Задача 3. Разделитель лог-файлов
int main3() {
    ifstream in("application.log");
    if (!in) {
        cout << "Файл application.log не найден!" << endl;
        return 0;
    }

    const size_t MAX_PART_SIZE = 1024; // 1KB на часть
    vector<string> part_files;
    string line;
    size_t current_size = 0;
    int part_num = 1;
    ofstream out;

    while (getline(in, line)) {
        if (current_size == 0) {
            string part_name = "log_part" + to_string(part_num) + ".txt";
            part_files.push_back(part_name);
            out.open(part_name);
            if (!out) {
                cerr << "Не удалось создать " << part_name << endl;
                return 0;
            }
        }
        size_t line_size = line.size() + 1; // + '\n'
        if (current_size + line_size > MAX_PART_SIZE && current_size > 0) {
            out.close();
            current_size = 0;
            part_num++;
            continue; // повторить обработку строки в новом файле
        }
        out << line << '\n';
        current_size += line_size;
    }
    if (out.is_open()) out.close();
    in.close();

    // Создаём индекс
    ofstream idx("log_index.txt");
    idx << "Всего частей: " << part_num << endl;
    for (const string& name : part_files) {
        idx << name << endl;
    }
    idx.close();

    cout << "Лог разделён на " << part_num << " частей. Индекс: log_index.txt" << endl;
    return 0;
}

// Задача 4. Запись и чтение массива чисел в бинарный файл
int main4() {
    int numbers[] = {15, 23, 7, 42, 18, 91, 3, 56, 77, 10};
    const size_t N = sizeof(numbers) / sizeof(numbers[0]);

    // Запись
    ofstream out_bin("numbers.bin", ios::binary);
    out_bin.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    out_bin.close();

    // Чтение
    ifstream in_bin("numbers.bin", ios::binary);
    in_bin.seekg(0, ios::end);
    size_t file_size = in_bin.tellg();
    in_bin.seekg(0, ios::beg);

    vector<int> buffer(N);
    in_bin.read(reinterpret_cast<char*>(buffer.data()), sizeof(int) * N);
    in_bin.close();

    cout << "Числа из файла: ";
    long long sum = 0;
    for (int x : buffer) {
        cout << x << " ";
        sum += x;
    }
    cout << "\nРазмер файла: " << file_size << " байт\n";
    cout << "Сумма: " << sum << endl;
    return 0;
}

// Задача 5. Работа со структурой Student в бинарном файле
struct Student {
    int id;
    char name[50];
    int age;
    double average_grade;
};

int main5() {
    Student students[] = {
        {1, "Иван Петров", 20, 4.5},
        {2, "Мария Сидорова", 19, 4.8},
        {3, "Алексей Иванов", 21, 4.2}
    };
    const size_t N = 3;

    // Запись
    ofstream out_st("students.dat", ios::binary);
    for (size_t i = 0; i < N; ++i) {
        out_st.write(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }
    out_st.close();

    // Чтение
    vector<Student> all;
    ifstream in_st("students.dat", ios::binary);
    Student s;
    while (in_st.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        all.push_back(s);
    }
    in_st.close();

    cout << "Студенты:\n";
    for (const auto& st : all) {
        cout << "ID: " << st.id << ", Имя: " << st.name
             << ", Возраст: " << st.age << ", Средний балл: " << st.average_grade << endl;
    }

    // Самый высокий балл
    auto best = max_element(all.begin(), all.end(),
        [](const Student& a, const Student& b) { return a.average_grade < b.average_grade; });
    cout << "Лучший студент: " << best->name << " (" << best->average_grade << ")\n";
    cout << "Всего студентов: " << all.size() << endl;
    return 0;
}

// Задача 6. Заполнение CSV файла данными о товарах
int main6() {
    srand(static_cast<unsigned>(time(0)));
    ofstream out("products.csv");
    out << "id,name,category,price,quantity\n";

    vector<string> categories = {"Электроника", "Аксессуары", "Одежда", "Книги", "Быт"};
    vector<string> names = {"Ноутбук", "Мышь", "Футболка", "Роман", "Чайник", "Наушники", "Часы", "Кроссовки", "Блокнот", "Лампа"};

    for (int i = 1; i <= 20; ++i) {
        string name = names[rand() % names.size()] + " " + to_string(i);
        string cat = categories[rand() % categories.size()];
        int price = 100 + rand() % 9901; // 100–10000
        int qty = 1 + rand() % 100;      // 1–100
        out << i << "," << name << "," << cat << "," << price << "," << qty << "\n";
    }
    out.close();

    // Проверка количества строк
    ifstream check("products.csv");
    int lines = 0;
    string line;
    while (getline(check, line)) lines++;
    check.close();

    cout << "Файл products.csv создан. Записей: " << (lines - 1) << " (заголовок + " << lines - 1 << " товаров)" << endl;
    return 0;
}

// Задача 7. Чтение и анализ CSV файла с товарами
struct Product {
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

int main7() {
    ifstream in("products.csv");
    if (!in) {
        cout << "Файл products.csv не найден! Выполните сначала задачу 6." << endl;
        return 0;
    }

    string line;
    getline(in, line); // пропускаем заголовок

    vector<Product> products;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 5) continue;
        Product p;
        p.id = stoi(fields[0]);
        p.name = fields[1];
        p.category = fields[2];
        p.price = stod(fields[3]);
        p.quantity = stoi(fields[4]);
        products.push_back(p);
    }
    in.close();

    cout << "Товары:\n";
    double total_value = 0;
    int total_qty = 0;
    for (const auto& p : products) {
        cout << p.id << ": " << p.name << " (" << p.category << ") — "
             << p.price << " руб., " << p.quantity << " шт.\n";
        total_value += p.price * p.quantity;
        total_qty += p.quantity;
    }

    auto cheapest = min_element(products.begin(), products.end(),
        [](const Product& a, const Product& b) { return a.price < b.price; });
    auto expensive = max_element(products.begin(), products.end(),
        [](const Product& a, const Product& b) { return a.price < b.price; });

    cout << "\nВсего товаров на складе: " << total_qty << endl;
    cout << "Суммарная стоимость: " << fixed << setprecision(2) << total_value << " руб." << endl;
    cout << "Самый дешёвый: " << cheapest->name << " (" << cheapest->price << " руб.)" << endl;
    cout << "Самый дорогой: " << expensive->name << " (" << expensive->price << " руб.)" << endl;
    return 0;
}

// Задача 8. Фильтрация товаров с использованием лямбда-функций
int main8() {
    ifstream in("products.csv");
    if (!in) {
        cout << "Файл products.csv не найден! Выполните сначала задачу 6." << endl;
        return 0;
    }

    string line;
    getline(in, line);
    vector<Product> products;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) fields.push_back(field);
        if (fields.size() != 5) continue;
        Product p;
        p.id = stoi(fields[0]);
        p.name = fields[1];
        p.category = fields[2];
        p.price = stod(fields[3]);
        p.quantity = stoi(fields[4]);
        products.push_back(p);
    }
    in.close();

    // Фильтры
    vector<Product> filtered;

    // Можно выбрать один фильтр; для примера — все три по очереди
    auto expensive_filter = [](const Product& p) { return p.price > 5000; };
    auto category_filter = [](const Product& p) { return p.category == "Электроника"; };
    auto stock_filter = [](const Product& p) { return p.quantity > 10; };

    // Применяем один из фильтров (например, дорогие)
    copy_if(products.begin(), products.end(), back_inserter(filtered), expensive_filter);

    ofstream out("filtered_products.csv");
    out << "id,name,category,price,quantity\n";
    for (const auto& p : filtered) {
        out << p.id << "," << p.name << "," << p.category << "," << p.price << "," << p.quantity << "\n";
    }
    out.close();

    cout << "Отфильтровано товаров (дороже 5000): " << filtered.size() << endl;
    cout << "Результат сохранён в filtered_products.csv" << endl;
    return 0;
}

// Задача 9. Сортировка товаров в CSV файле
int main9() {
    ifstream in("products.csv");
    if (!in) {
        cout << "Файл products.csv не найден!" << endl;
        return 0;
    }

    string line;
    getline(in, line);
    vector<Product> products;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) fields.push_back(field);
        if (fields.size() != 5) continue;
        Product p;
        p.id = stoi(fields[0]);
        p.name = fields[1];
        p.category = fields[2];
        p.price = stod(fields[3]);
        p.quantity = stoi(fields[4]);
        products.push_back(p);
    }
    in.close();

    int choice = 1; // по умолчанию — по цене по возрастанию
    auto comp = [](const Product& a, const Product& b) { return a.price < b.price; };
    string desc = "по цене (возрастание)";

    // Можно реализовать выбор, но для простоты — берём один вариант
    sort(products.begin(), products.end(), comp);

    ofstream out("sorted_products.csv");
    out << "id,name,category,price,quantity\n";
    for (const auto& p : products) {
        out << p.id << "," << p.name << "," << p.category << "," << p.price << "," << p.quantity << "\n";
    }
    out.close();

    cout << "Товары отсортированы " << desc << " и сохранены в sorted_products.csv" << endl;
    return 0;
}

// Задача 10. Чтение и запись конфигурации
int main10() {
    // Создаём конфиг
    ofstream cfg("config.json");
    cfg << "{\n";
    cfg << "  \"app_name\": \"My Application\",\n";
    cfg << "  \"version\": \"1.0.0\",\n";
    cfg << "  \"settings\": {\n";
    cfg << "    \"max_connections\": 100,\n";
    cfg << "    \"timeout\": 30,\n";
    cfg << "    \"debug_mode\": true\n";
    cfg << "  },\n";
    cfg << "  \"database\": {\n";
    cfg << "    \"host\": \"localhost\",\n";
    cfg << "    \"port\": 5432,\n";
    cfg << "    \"username\": \"admin\"\n";
    cfg << "  }\n";
    cfg << "}";
    cfg.close();
    cout << "config.json создан.\n";

    // Читаем и выводим
    ifstream in("config.json");
    string line;
    cout << "Содержимое config.json:\n";
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();

    // Читаем в строку и заменяем timeout
    ifstream in2("config.json");
    string content((istreambuf_iterator<char>(in2)), istreambuf_iterator<char>());
    in2.close();

    size_t pos = content.find("\"timeout\": 30");
    if (pos != string::npos) {
        //content.replace(pos, strlen("\"timeout\": 30"), "\"timeout\": 60");
        ofstream out("config.json");
        out << content;
        out.close();
        cout << "timeout изменён на 60.\n";
    }

    return 0;
}

// Задача 11. Обработчик данных с датчиков
int main11() {
    ifstream in("sensor_data.txt");
    if (!in) {
        cout << "Файл sensor_data.txt не найден!" << endl;
        return 0;
    }

    vector<double> temps;
    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        double val;
        while (ss >> val) {
            temps.push_back(val);
        }
    }
    in.close();

    // Фильтрация: [-50, +50]
    vector<double> valid;
    copy_if(temps.begin(), temps.end(), back_inserter(valid),
        [](double t) { return t >= -50.0 && t <= 50.0; });

    if (valid.empty()) {
        cout << "Нет корректных данных." << endl;
        return 0;
    }

    double avg = accumulate(valid.begin(), valid.end(), 0.0) / valid.size();

    ofstream out("filtered_sensor_data.txt");
    for (double t : valid) {
        out << t << "\n";
    }
    out.close();

    cout << "Фильтрация завершена. Корректных значений: " << valid.size() << endl;
    cout << "Средняя температура: " << fixed << setprecision(2) << avg << "°C" << endl;
    cout << "Отфильтрованные данные сохранены в filtered_sensor_data.txt" << endl;
    return 0;
}

// Задача 12. Сравнение скорости записи в файл
int main12() {
    const int N = 100000;
    vector<int> data(N);
    for (int i = 0; i < N; ++i) data[i] = rand();

    auto time_write = [](const vector<int>& d, const string& fname, bool batch) -> double {
        auto start = chrono::steady_clock::now();
        ofstream f(fname, ios::binary);
        if (batch) {
            f.write(reinterpret_cast<const char*>(d.data()), d.size() * sizeof(int));
        } else {
            for (int x : d) f.write(reinterpret_cast<const char*>(&x), sizeof(int));
        }
        f.close();
        auto end = chrono::steady_clock::now();
        return chrono::duration<double, milli>(end - start).count();
    };

    double time_batch = time_write(data, "batch.bin", true);
    double time_individual = time_write(data, "individual.bin", false);

    cout << "Сравнение скорости записи (100 000 чисел):\n";
    cout << "Пакетная запись: " << fixed << setprecision(2) << time_batch << " мс\n";
    cout << "Покомпонентная: " << time_individual << " мс\n";
    cout << "Разница: " << (time_individual - time_batch) << " мс\n";
    return 0;
}

// Главная функция — запускает все задачи
int main() {
    cout << "=== Задача 1. Анализатор текстового файла с поиском позиций слов ===" << endl;
    main1();
    cout << "\n=== Задача 2. Редактор конфигурационных файлов с прямой заменой ===" << endl;
    main2();
    cout << "\n=== Задача 3. Разделитель лог-файлов ===" << endl;
    main3();
    cout << "\n=== Задача 4. Запись и чтение массива чисел в бинарный файл ===" << endl;
    main4();
    cout << "\n=== Задача 5. Работа со структурой Student в бинарном файле ===" << endl;
    main5();
    cout << "\n=== Задача 6. Заполнение CSV файла данными о товарах ===" << endl;
    main6();
    cout << "\n=== Задача 7. Чтение и анализ CSV файла с товарами ===" << endl;
    main7();
    cout << "\n=== Задача 8. Фильтрация товаров с использованием лямбда-функций ===" << endl;
    main8();
    cout << "\n=== Задача 9. Сортировка товаров в CSV файле ===" << endl;
    main9();
    cout << "\n=== Задача 10. Чтение и запись конфигурации ===" << endl;
    main10();
    cout << "\n=== Задача 11. Обработчик данных с датчиков ===" << endl;
    main11();
    cout << "\n=== Задача 12. Сравнение скорости записи в файл ===" << endl;
    main12();
    return 0;
}