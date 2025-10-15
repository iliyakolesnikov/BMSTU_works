#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <iomanip>
#include <random>
using namespace std;


//1
int main(){
    vector <int> v = {1,2,3,4,5,6,7,8,9,10};
    for_each (v.begin(),v.end(),[](int x){cout << "  элемент: " << x << " ";});    
    return 0;
}


//2
int main(){
    vector <int> v = {1,2,3,4,5,6,7,8,9,10};
    cout << "старый массив:" << endl;
    for_each (v.begin(),v.end(), [] (int x){cout << x << " ";});
    cout << endl;
    cout << "новый массив:" << endl;
    for_each (v.begin(),v.end(), [] (int x){cout << x*2 << " ";}); 
    cout << endl;
    return 0;
}


//3
int main() {
    // Создаём вектор из 20 чисел (например, случайные или заданные)
    vector<int> v = {34, 12, 78, 45, 23, 89, 10, 67, 55, 91, 29, 48, 73, 14, 66, 82, 37, 50, 95, 21};
    // Находим итератор на максимальный элемент с помощью лямбды
    auto max_iter = max_element(v.begin(), v.end(),[](int a, int b) {
            return a < b;                 // возвращаем true, если a меньше b — стандартное сравнение
        });
    // Проверяем, что итератор не равен end()
    if (max_iter != v.end()) {
        cout << "Максимальное значение: " << *max_iter << endl;
    } else {
        cout << "Вектор пуст." << endl;
    }
    return 0;
}


//4
int main(){
    vector<int> v;
    int n;
    cout << "введите кол-во элементов: ";
    cin >> n;
    for (int i = 0; i < n; i++){
        v.push_back(rand() % 200-100);         //заполнение вектора случайными элементами от -100 до 100
    }

    cout << "старый массив: ";
    for (int x: v){ cout << x << " "; }

    auto del = v.erase(remove_if(v.begin(),v.end(),[](int x){            //удаление отрицательных чисел
        return x < 0;
    }),v.end());

    cout << "\nновый массив: ";
    for (int x: v){ cout << x << " "; }
    cout << endl;
    return 0;
}


//5
int main(){
    vector<int> v;
    int n = 20;
    srand(time(NULL));
    for (int i = 0; i < n; i++){
        v.push_back(rand() % 200-100);         //заполнение вектора случайными элементами от -100 до 100
    }
    cout << "старый массив: ";
    for (int x: v){ cout << x << " "; }

    auto [mn_t, mx_t] = minmax_element(v.begin(), v.end());
    int sm = accumulate(v.begin(),v.end(),0);
    int kol = v.size();
    float sred = sm / kol;
    sort(v.begin(),v.end());

    cout << "\nmin and max = " << *mx_t << " and " << *mn_t;
    cout << "\nсреднее значение = " << sred;
    cout << "\nотсортированный массив: ";
    for (int x: v){ cout << x << " "; }
    return 0;
}


//6
int main() {      
    vector<int> numbers = {7, 3, 7, 1, 5, 2, 8, 4, 7, 6, 9, 2, 5, 1, 3, 8, 4, 6, 9, 7};
    
    auto it = find(numbers.begin(), numbers.end(), 7);
    if (it != numbers.end()) {
        cout << "Число 7 найдено на позиции: " << distance(numbers.begin(), it) << endl;
    }
    
    sort(numbers.begin(), numbers.end());
    auto last = unique(numbers.begin(), numbers.end());
    numbers.erase(last, numbers.end());
    
    cout << "Уникальные элементы: ";
    for (int num : numbers) cout << num << " ";
    cout << endl << endl;
    return 0;
}


//7
int main() {    
    vector<double> temperatures = {-15.5, 25.3, -60.2, 45.7, 12.1, 55.8, -5.3, 30.2, -45.9, 20.1};
    
    temperatures.erase(
        remove_if(temperatures.begin(), temperatures.end(),
            [](double temp) { return temp < -50.0 || temp > 50.0; }),
        temperatures.end()
    );
    
    double average = accumulate(temperatures.begin(), temperatures.end(), 0.0) / temperatures.size();
    auto [min_it, max_it] = minmax_element(temperatures.begin(), temperatures.end());
    bool all_above_minus10 = all_of(temperatures.begin(), temperatures.end(),
        [](double temp) { return temp > -10.0; });
    
    cout << "Температуры: ";
    for (double temp : temperatures) cout << temp << " ";
    cout << "\nСредняя: " << average << "\nМин: " << *min_it << "\nМакс: " << *max_it;
    cout << "\nВсе температуры > -10: " << (all_above_minus10 ? "Да" : "Нет") << endl << endl;
    return 0;
}


//8
int main() {    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 180.0);
    
    vector<double> speeds(50);
    generate(speeds.begin(), speeds.end(), [&]() { return dist(gen); });
    
    vector<double> over_speeds;
    copy_if(speeds.begin(), speeds.end(), back_inserter(over_speeds),
        [](double speed) { return speed > 120.0; });
    
    double average_speed = accumulate(speeds.begin(), speeds.end(), 0.0) / speeds.size();
    bool always_moving = all_of(speeds.begin(), speeds.end(), [](double speed) { return speed > 0.0; });
    
    vector<double> sorted_speeds = speeds;
    sort(sorted_speeds.rbegin(), sorted_speeds.rend());
    
    cout << "Средняя скорость: " << average_speed << " км/ч" << endl;
    cout << "Превышений скорости > 120: " << over_speeds.size() << endl;
    cout << "Всегда двигался: " << (always_moving ? "Да" : "Нет") << endl;
    cout << "Топ-10 скоростей: ";
    for (int i = 0; i < 10 && i < sorted_speeds.size(); ++i) {
        cout << sorted_speeds[i] << " ";
    }
    cout << endl << endl;
    return 0;
}


//9
int main() {      
    vector<double> power = {85.5, 92.3, -5.2, 78.9, 45.6, -2.1, 67.8, 89.1, 55.4, 72.3, 
                          91.7, 8.5, 63.2, 95.8, -1.5, 59.7, 82.4, 48.9, 76.1, 88.6};
    
    power.erase(
        remove_if(power.begin(), power.end(), [](double p) { return p < 0.0; }),
        power.end()
    );
    
    auto [min_it, max_it] = minmax_element(power.begin(), power.end());
    double average_power = accumulate(power.begin(), power.end(), 0.0) / power.size();
    bool in_range = all_of(power.begin(), power.end(), 
        [](double p) { return p >= 10.0 && p <= 90.0; });
    
    vector<double> sorted_power = power;
    sort(sorted_power.begin(), sorted_power.end());
    double median;
    if (sorted_power.size() % 2 == 0) {
        median = (sorted_power[sorted_power.size()/2 - 1] + sorted_power[sorted_power.size()/2]) / 2.0;
    } else {
        median = sorted_power[sorted_power.size()/2];
    }
    
    cout << "Мин мощность: " << *min_it << " кВт" << endl;
    cout << "Макс мощность: " << *max_it << " кВт" << endl;
    cout << "Средняя мощность: " << average_power << " кВт" << endl;
    cout << "В диапазоне 10-90 кВт: " << (in_range ? "Да" : "Нет") << endl;
    cout << "Медиана: " << median << " кВт" << endl << endl;
    return 0;
}


//10
int main() {    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(50.0, 200.0);
    
    vector<double> consumption(30);
    generate(consumption.begin(), consumption.end(), [&]() { return dist(gen); });
    
    double total = accumulate(consumption.begin(), consumption.end(), 0.0);
    double average_consumption = total / consumption.size();
    auto [min_day, max_day] = minmax_element(consumption.begin(), consumption.end());
    
    double threshold = average_consumption * 1.2;
    vector<double> peak_days;
    copy_if(consumption.begin(), consumption.end(), back_inserter(peak_days),
        [threshold](double value) { return value > threshold; });
    
    cout << "Общее потребление: " << total << " кВт·ч" << endl;
    cout << "Среднесуточное: " << average_consumption << " кВт·ч" << endl;
    cout << "Мин потребление: " << *min_day << " кВт·ч (день " << distance(consumption.begin(), min_day) + 1 << ")" << endl;
    cout << "Макс потребление: " << *max_day << " кВт·ч (день " << distance(consumption.begin(), max_day) + 1 << ")" << endl;
    cout << "Пиковых дней (> +20% от среднего): " << peak_days.size() << endl << endl;
    return 0;
}


//11
int main() {    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 2.0);
    
    vector<double> amplitudes(50);
    generate(amplitudes.begin(), amplitudes.end(), [&]() { return dist(gen); });
    
    amplitudes.erase(
        remove_if(amplitudes.begin(), amplitudes.end(), [](double amp) { return amp < 0.1; }),
        amplitudes.end()
    );
    
    double average_amp = accumulate(amplitudes.begin(), amplitudes.end(), 0.0) / amplitudes.size();
    double max_amp = *max_element(amplitudes.begin(), amplitudes.end());
    bool all_above_threshold = all_of(amplitudes.begin(), amplitudes.end(),
        [](double amp) { return amp > 0.5; });
    
    vector<double> sorted_amplitudes = amplitudes;
    sort(sorted_amplitudes.rbegin(), sorted_amplitudes.rend());
    
    cout << "Средняя амплитуда: " << average_amp << endl;
    cout << "Максимальная амплитуда: " << max_amp << endl;
    cout << "Все амплитуды > 0.5: " << (all_above_threshold ? "Да" : "Нет") << endl;
    cout << "Топ-10 амплитуд: ";
    for (int i = 0; i < 10 && i < sorted_amplitudes.size(); ++i) {
        cout << sorted_amplitudes[i] << " ";
    }
    cout << endl << endl;
    return 0;
}


//12
int main() {    
    vector<double> fuel_level = {85, 82, 79, 76, 73, 70, 68, 65, 63, 60,
                                58, 55, 53, 50, 48, 45, 43, 40, 38, 35,
                                33, 30, 28, 25, 23, 20, 18, 15, 13, 10,
                                8, 7, 6, 5, 4, 3, 2, 1, 0.5, 0.3,
                                0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
    
    double min_fuel = *min_element(fuel_level.begin(), fuel_level.end());
    double max_fuel = *max_element(fuel_level.begin(), fuel_level.end());
    bool below_5_percent = any_of(fuel_level.begin(), fuel_level.end(),
        [max_fuel](double level) { return level < max_fuel * 0.05; });
    
    double consumption = fuel_level.front() - fuel_level.back();
    
    vector<double> sorted_fuel = fuel_level;
    sort(sorted_fuel.begin(), sorted_fuel.end());
    double median = sorted_fuel[sorted_fuel.size() / 2];
    
    cout << "Мин уровень топлива: " << min_fuel << "%" << endl;
    cout << "Макс уровень топлива: " << max_fuel << "%" << endl;
    cout << "Падал ниже 5% от макс: " << (below_5_percent ? "Да" : "Нет") << endl;
    cout << "Среднее потребление: " << consumption << "% за период" << endl;
    cout << "Медиана: " << median << "%" << endl << endl;
    return 0;
}


//13
int main() {    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.5, 11.5);
    
    vector<double> pressure(50);
    generate(pressure.begin(), pressure.end(), [&]() { return dist(gen); });
    
    pressure.erase(
        remove_if(pressure.begin(), pressure.end(),
            [](double p) { return p < 0.0 || p > 12.0; }),
        pressure.end()
    );
    
    double average_pressure = accumulate(pressure.begin(), pressure.end(), 0.0) / pressure.size();
    auto [min_p, max_p] = minmax_element(pressure.begin(), pressure.end());
    
    cout << "Среднее давление: " << average_pressure << " бар" << endl;
    cout << "Мин давление: " << *min_p << " бар" << endl;
    cout << "Макс давление: " << *max_p << " бар" << endl;
    
    cout << "Значения > 8 бар: ";
    for_each(pressure.begin(), pressure.end(), [](double p) {
        if (p > 8.0) cout << p << " ";
    });
    cout << endl << endl;
    return 0;
}


//14
int main() {    
    vector<double> hourly_consumption(24);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(100.0, 500.0);
    generate(hourly_consumption.begin(), hourly_consumption.end(), [&]() { return dist(gen); });
    
    double total_consumption = accumulate(hourly_consumption.begin(), hourly_consumption.end(), 0.0);
    double average_hourly = total_consumption / hourly_consumption.size();
    auto peak_hour = max_element(hourly_consumption.begin(), hourly_consumption.end());
    
    vector<double> deviations(24);
    transform(hourly_consumption.begin(), hourly_consumption.end(), deviations.begin(),
        [average_hourly](double value) { return value - average_hourly; });
    
    vector<double> sorted_consumption = hourly_consumption;
    sort(sorted_consumption.begin(), sorted_consumption.end());
    
    cout << "Суммарное потребление: " << total_consumption << " кВт·ч" << endl;
    cout << "Среднее потребление: " << average_hourly << " кВт·ч" << endl;
    cout << "Пиковый час: " << distance(hourly_consumption.begin(), peak_hour) 
         << " (" << *peak_hour << " кВт·ч)" << endl;
    
    cout << "Топ-5 минимальных часов: ";
    for (int i = 0; i < 5 && i < sorted_consumption.size(); ++i) {
        cout << sorted_consumption[i] << " ";
    }
    cout << endl << endl;
    return 0;
}


//15
int main() {    
    vector<vector<double>> temp(5, vector<double>(30));
    vector<vector<double>> pressure(5, vector<double>(100));
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> temp_dist(15.0, 35.0);
    uniform_real_distribution<double> pressure_dist(0.5, 2.5);
    
    // Заполняем данными
    for (auto& channel : temp) {
        generate(channel.begin(), channel.end(), [&]() { return temp_dist(gen); });
    }
    for (auto& channel : pressure) {
        generate(channel.begin(), channel.end(), [&]() { return pressure_dist(gen); });
    }
    
    // Средние температуры для каждого канала
    vector<double> avg_temperatures(5);
    transform(temp.begin(), temp.end(), avg_temperatures.begin(),
        [](const vector<double>& channel) {
            return accumulate(channel.begin(), channel.end(), 0.0) / channel.size();
        });
    
    // Минимальное и максимальное давление для каждого канала
    vector<pair<double, double>> pressure_ranges(5);
    transform(pressure.begin(), pressure.end(), pressure_ranges.begin(),
        [](const vector<double>& channel) {
            auto [min_it, max_it] = minmax_element(channel.begin(), channel.end());
            return make_pair(*min_it, *max_it);
        });
    
    // Канал с наибольшей вариацией температуры
    vector<double> temp_variations(5);
    transform(temp.begin(), temp.end(), temp_variations.begin(),
        [](const vector<double>& channel) {
            auto [min_it, max_it] = minmax_element(channel.begin(), channel.end());
            return *max_it - *min_it;
        });
    
    auto max_var_it = max_element(temp_variations.begin(), temp_variations.end());
    int max_var_channel = distance(temp_variations.begin(), max_var_it);
    
    // Нормализация давления
    vector<vector<double>> normalized_pressure = pressure;
    for (int i = 0; i < 5; ++i) {
        double min_p = pressure_ranges[i].first;
        double max_p = pressure_ranges[i].second;
        transform(normalized_pressure[i].begin(), normalized_pressure[i].end(), 
                 normalized_pressure[i].begin(),
            [min_p, max_p](double value) { 
                return (value - min_p) / (max_p - min_p); 
            });
    }
    
    // Сортировка средних температур
    vector<size_t> channel_indices(5);
    iota(channel_indices.begin(), channel_indices.end(), 0);
    sort(channel_indices.begin(), channel_indices.end(),
        [&avg_temperatures](size_t i, size_t j) { 
            return avg_temperatures[i] > avg_temperatures[j]; 
        });
    
    cout << "Средние температуры по каналам: ";
    for (double avg : avg_temperatures) cout << fixed << setprecision(2) << avg << " ";
    cout << "\nКанал с наибольшей вариацией температуры: " << max_var_channel << endl;
    cout << "Канал с максимальной средней температурой: " << channel_indices[0] << endl;
    
    cout << "Пики давления (>0.9) после нормализации: ";
    for (const auto& channel : normalized_pressure) {
        for_each(channel.begin(), channel.end(), [](double value) {
            if (value > 0.9) cout << value << " ";
        });
    }
    cout << endl;   
    return 0;
}






































