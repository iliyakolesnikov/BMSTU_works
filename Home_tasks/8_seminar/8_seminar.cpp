#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>

using namespace std;

// Задача 1: Обмен указателей на переменные
void swapPointers(int **a, int **b) {
    int *temp = *a;
    *a = *b;
    *b = temp;
}

int main1() {
    int x = 10, y = 20;
    int *p1 = &x, *p2 = &y;
    
    cout << "До обмена:" << endl;
    cout << "p1 указывает на: " << *p1 << " по адресу: " << p1 << endl;
    cout << "p2 указывает на: " << *p2 << " по адресу: " << p2 << endl;
    
    swapPointers(&p1, &p2);
    
    cout << "\nПосле обмена:" << endl;
    cout << "p1 указывает на: " << *p1 << " по адресу: " << p1 << endl;
    cout << "p2 указывает на: " << *p2 << " по адресу: " << p2 << endl;
    
    return 0;
}

// Задача 2: Динамическое создание двумерного массива
int main2() {
    int n, m;
    cout << "Введите n и m: ";
    cin >> n >> m;
    
    // Создание двумерного массива
    int **arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
    }
    
    // Заполнение массива
    int counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = counter % 100;
            counter++;
        }
    }
    
    // Вывод массива
    cout << "Массив:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    
    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    
    return 0;
}

// Задача 3: Освобождение памяти двумерного массива
void free2D(int **arr, int n) {
    for (int i = 0; i < n; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int main3() {
    int n = 3, m = 4;
    
    // Создание массива
    int **arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
        for (int j = 0; j < m; j++) {
            arr[i][j] = i * m + j;
        }
    }
    
    cout << "Массив создан:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    
    free2D(arr, n);
    cout << "Память освобождена" << endl;
    
    return 0;
}

// Задача 4: Транспонирование матрицы
int **transpose(int **matrix, int n, int m) {
    int **result = new int*[m];
    for (int i = 0; i < m; i++) {
        result[i] = new int[n];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][i] = matrix[i][j];
        }
    }
    
    return result;
}

int main4() {
    int n = 2, m = 3;
    
    // Создание исходной матрицы
    int **matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
        for (int j = 0; j < m; j++) {
            matrix[i][j] = i * m + j + 1;
        }
    }
    
    cout << "Исходная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    int **transposed = transpose(matrix, n, m);
    
    cout << "Транспонированная матрица:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }
    
    // Освобождение памяти
    free2D(matrix, n);
    free2D(transposed, m);
    
    return 0;
}

// Задача 5: Сортировка строк по сумме элементов
void sortRowsBySum(int **arr, int n, int m) {
    // Создаем массив пар (сумма, указатель на строку)
    pair<int, int*> *rows = new pair<int, int*>[n];
    
    // Вычисляем суммы для каждой строки
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            sum += arr[i][j];
        }
        rows[i] = make_pair(sum, arr[i]);
    }
    
    // Сортируем по сумме
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (rows[j].first > rows[j + 1].first) {
                swap(rows[j], rows[j + 1]);
            }
        }
    }
    
    // Переставляем указатели в исходном массиве
    for (int i = 0; i < n; i++) {
        arr[i] = rows[i].second;
    }
    
    delete[] rows;
}

int main5() {
    int n = 4, m = 3;
    
    // Создание массива
    int **arr = new int*[n];
    int data[4][3] = {{1, 2, 3}, {9, 8, 7}, {4, 5, 6}, {0, 1, 0}};
    
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
        for (int j = 0; j < m; j++) {
            arr[i][j] = data[i][j];
        }
    }
    
    cout << "Исходный массив:" << endl;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
            sum += arr[i][j];
        }
        cout << " (сумма: " << sum << ")" << endl;
    }
    
    sortRowsBySum(arr, n, m);
    
    cout << "\nПосле сортировки по сумме:" << endl;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
            sum += arr[i][j];
        }
        cout << " (сумма: " << sum << ")" << endl;
    }
    
    free2D(arr, n);
    return 0;
}

// Задача 6: Сумма элементов матрицы через указатели
int sumElements(int **arr, int n, int m) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += *(*(arr + i) + j);
        }
    }
    return sum;
}

int main6() {
    int n = 3, m = 5;
    
    int **arr = new int*[n];
    for (int i = 0; i < n; i++) {
        arr[i] = new int[m];
        for (int j = 0; j < m; j++) {
            arr[i][j] = (i + 1) * (j + 1);
        }
    }
    
    cout << "Массив:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "Сумма всех элементов: " << sumElements(arr, n, m) << endl;
    
    free2D(arr, n);
    return 0;
}

// Задача 7: Сортировка указателей на строки
void sortWords(char **words, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                swap(words[j], words[j + 1]);
            }
        }
    }
}

int main7() {
    const int count = 7;
    char *words[count] = {
        "banana", "apple", "cherry", "date", 
        "elderberry", "fig", "grape"
    };
    
    cout << "Исходный массив слов:" << endl;
    for (int i = 0; i < count; i++) {
        cout << words[i] << " ";
    }
    cout << endl;
    
    sortWords(words, count);
    
    cout << "После сортировки:" << endl;
    for (int i = 0; i < count; i++) {
        cout << words[i] << " ";
    }
    cout << endl;
    
    return 0;
}

// Задача 8: Моделирование теплопередачи
double **allocatePlate(int n, int m) {
    double **plate = new double*[n];
    for (int i = 0; i < n; i++) {
        plate[i] = new double[m];
        for (int j = 0; j < m; j++) {
            plate[i][j] = 20.0;
        }
    }
    return plate;
}

void freePlate(double **plate, int n) {
    for (int i = 0; i < n; i++) {
        delete[] plate[i];
    }
    delete[] plate;
}

void updateTemperature(double **plate, int n, int m) {
    double **newPlate = allocatePlate(n, m);
    
    // Копируем нагреватель в центре
    int center_i = n / 2, center_j = m / 2;
    newPlate[center_i][center_j] = 100.0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == center_i && j == center_j) continue;
            
            double sum = 0.0;
            int count = 0;
            
            if (i > 0) { sum += plate[i-1][j]; count++; }
            if (i < n-1) { sum += plate[i+1][j]; count++; }
            if (j > 0) { sum += plate[i][j-1]; count++; }
            if (j < m-1) { sum += plate[i][j+1]; count++; }
            
            newPlate[i][j] = sum / count;
        }
    }
    
    // Копируем новые значения обратно
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            plate[i][j] = newPlate[i][j];
        }
    }
    
    freePlate(newPlate, n);
}

int main8() {
    int n = 5, m = 5, iterations = 3;
    
    double **plate = allocatePlate(n, m);
    
    cout << "Начальное распределение температуры:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << fixed << setprecision(1) << plate[i][j] << " ";
        }
        cout << endl;
    }
    
    for (int k = 0; k < iterations; k++) {
        updateTemperature(plate, n, m);
        cout << "\nПосле итерации " << k + 1 << ":" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << fixed << setprecision(1) << plate[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    freePlate(plate, n);
    return 0;
}

// Задача 9: Нейронный слой
double *forward(double **weights, double *inputs, int n, int m) {
    double *outputs = new double[n];
    
    for (int i = 0; i < n; i++) {
        outputs[i] = 0.0;
        for (int j = 0; j < m; j++) {
            outputs[i] += weights[i][j] * inputs[j];
        }
    }
    
    return outputs;
}

void normalizeWeights(double **weights, int n, int m) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < m; j++) {
            sum += abs(weights[i][j]);
        }
        
        if (sum > 1.0) {
            for (int j = 0; j < m; j++) {
                weights[i][j] /= sum;
            }
        }
    }
}

int main9() {
    int n = 3, m = 4;
    
    // Создание матрицы весов
    double **weights = new double*[n];
    for (int i = 0; i < n; i++) {
        weights[i] = new double[m];
        for (int j = 0; j < m; j++) {
            weights[i][j] = (i + j + 1) * 0.5; // Примерные значения
        }
    }
    
    // Создание входного вектора
    double *inputs = new double[m];
    for (int j = 0; j < m; j++) {
        inputs[j] = (j + 1) * 0.2;
    }
    
    cout << "Матрица весов:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << fixed << setprecision(2) << weights[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\nВходной вектор:" << endl;
    for (int j = 0; j < m; j++) {
        cout << inputs[j] << " ";
    }
    cout << endl;
    
    double *outputs = forward(weights, inputs, n, m);
    
    cout << "\nВыходной вектор:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Нейрон " << i << ": " << outputs[i] << endl;
    }
    
    normalizeWeights(weights, n, m);
    cout << "\nПосле нормализации весов:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << fixed << setprecision(2) << weights[i][j] << " ";
        }
        cout << endl;
    }
    
    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] weights[i];
    }
    delete[] weights;
    delete[] inputs;
    delete[] outputs;
    
    return 0;
}

// Задача 10: Распределение нагрузки в системе
double *averageLoadPerNode(int **load, int n, int t) {
    double *averages = new double[n];
    
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < t; j++) {
            sum += *(*(load + i) + j);
        }
        averages[i] = sum / t;
    }
    
    return averages;
}

void normalizeLoad(int **load, int n, int t) {
    double *averages = averageLoadPerNode(load, n, t);
    
    for (int j = 0; j < t; j++) {
        for (int i = 0; i < n; i++) {
            if (*(*(load + i) + j) > 80) {
                double excess = (*(*(load + i) + j) - 80) * 0.1;
                int nodesToDistribute = n - 1;
                double perNode = excess / nodesToDistribute;
                
                for (int k = 0; k < n; k++) {
                    if (k != i) {
                        *(*(load + k) + j) = min(100, (int)(*(*(load + k) + j) + perNode));
                    }
                }
                *(*(load + i) + j) = max(0, (int)(*(*(load + i) + j) - excess));
            }
        }
    }
    
    delete[] averages;
}

int findCriticalInterval(int **load, int n, int t) {
    int maxSum = 0, criticalInterval = 0;
    
    for (int j = 0; j < t; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += *(*(load + i) + j);
        }
        
        if (sum > maxSum) {
            maxSum = sum;
            criticalInterval = j;
        }
    }
    
    return criticalInterval;
}

void printMatrix(int **load, int n, int t) {
    cout << "Матрица нагрузок:" << endl;
    cout << "Узел\\Интервал\t";
    for (int j = 0; j < t; j++) {
        cout << j << "\t";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "Узел " << i << ":\t\t";
        for (int j = 0; j < t; j++) {
            cout << *(*(load + i) + j) << "\t";
        }
        cout << endl;
    }
}

int main10() {
    int n = 3, t = 5;
    
    // Создание матрицы нагрузок
    int **load = new int*[n];
    int data[3][5] = {
        {40, 50, 70, 90, 100},
        {30, 40, 50, 60, 80},
        {20, 30, 30, 40, 50}
    };
    
    for (int i = 0; i < n; i++) {
        load[i] = new int[t];
        for (int j = 0; j < t; j++) {
            load[i][j] = data[i][j];
        }
    }
    
    cout << "=== Анализ распределения нагрузки ===" << endl;
    printMatrix(load, n, t);
    
    double *averages = averageLoadPerNode(load, n, t);
    cout << "\nСредняя нагрузка на узлах:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Узел " << i << ": " << averages[i] << "%" << endl;
    }
    
    normalizeLoad(load, n, t);
    cout << "\nПосле нормализации:" << endl;
    printMatrix(load, n, t);
    
    int critical = findCriticalInterval(load, n, t);
    cout << "\nКритический интервал: " << critical << endl;
    
    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] load[i];
    }
    delete[] load;
    delete[] averages;
    
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
    return 0;
}