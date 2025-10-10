#include <iostream>
#include <cmath>
using namespace std;


int det(int matrix[3][3]) {
 return matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])      //ф-я для нахождения определителя
 - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
 + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
}




//// ЗАДАЧИ ИЗ ПРЕЗЕНТАЦИИ

//1
// int main(){
//     int t[3][3];
//     t[0][2] = t[1][2] = t[2][2] = 1;
//     cout << "Введите координаты 3 точек: " << endl;
//     for (int i = 0; i < 3; i++){
//         for (int j = 0; j < 2; j++){
//             cin >> t[i][j]; 
//         }                        
//     }
//     float d = det(t);
//     cout << "Площадь  = " << abs(d/2) << endl;
//     return 0;
// }


//2
// int main(){
//     float matr[2][2];
//     float vec[2], res[2];

//     float x,y,d;
//     cout << "Введите координаты точки(x и y) и угол поворота(в градусах): " << endl;
//     cin >> x >> y >> d;
//     float gr = d;
//     d = d * M_PI / 180.0;          //перевод в радианы

//     vec[0] = x; vec[1] = y;    
//     matr[0][0] = cos(d); matr[0][1] = sin(d); matr[1][0] = -sin(d); matr[1][1] = cos(d);

//     for (int i = 0; i < 2; i++){
//         for (int j = 0; j < 2; j++){
//             res[i] = matr[i][j]*vec[j];
//         }
//     }
//     cout << "Координаты повернутой точки на " << gr << " градуса: ";
//     for (int i = 0; i < 2; i++){
//         cout << res[i] << " ";
//     }
//     cout << endl;
//     return 0;
// }


//3
// int main(){
//     int t[3][3];
//     t[0][2] = t[1][2] = t[2][2] = 1;
//     cout << "введите координаты 3 точек:" << endl;
//     for (int i = 0; i < 3; i++){
//         for (int j = 0; j < 2; j++){
//             cin >> t[i][j];
//         }
//     }
//     float d = det(t);
//     if (d == 0)
//         cout << "точки коллинеарны ";
//     else
//         cout << "НЕ коллинеарны";
//     return 0;
// }


//4
// int main() {
//     // Шаг 1: Задаём четыре точки 
//     // Измените их на свои! Точки должны быть НЕ копланарными (иначе нет сферы).
//     double x[4];
//     double y[4];
//     double z[4];
//     cout << "x:" << endl;
//     for (int i = 0; i < 4; i++){
//         cin >> x[i];
//     }
//     cout << "y:" << endl;
//        for (int i = 0; i < 4; i++){
//         cin >> y[i];
//     }
//     cout << "z:" << endl;
//        for (int i = 0; i < 4; i++){
//         cin >> z[i];
//     }
    

//     // Шаг 2: Строим матрицу A (4x4) и вектор b (4x1)
//     double A[4][5] = {0};  // Расширенная матрица [A | b] для Гаусса (4 строки, 5 столбцов)
//     for (int i = 0; i < 4; i++) {
//         double sq = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];  // x² + y² + z² для точки i
//         A[i][0] = x[i];  // Коэффициент при D
//         A[i][1] = y[i];  // При E
//         A[i][2] = z[i];  // При F
//         A[i][3] = 1.0;   // При G
//         A[i][4] = -sq;   // Правая часть: -(x² + y² + z²)
//     }

//     // Выводим матрицу для проверки (опционально)
//     cout << "Расширенная матрица [A | b]:\n";
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 5; j++) {
//             cout << A[i][j] << "\t";
//         }
//         cout << "\n";
//     }
//     cout << "\n";

//     // Шаг 3: Метод Гаусса (прямой ход: приводим к верхнетреугольной форме)
//     // Мы работаем с расширенной матрицей A[4][5]
//     for (int col = 0; col < 4; col++) {  // Для каждого столбца (0..3)
//         // Находим максимальный элемент в столбце col (с строки col) для стабильности
//         int maxRow = col;
//         for (int row = col + 1; row < 4; row++) {
//             if (abs(A[row][col]) > abs(A[maxRow][col])) {
//                 maxRow = row;
//             }
//         }
//         // Меняем строки местами
//         if (maxRow != col) {
//             for (int j = 0; j < 5; j++) {
//                 double temp = A[col][j];
//                 A[col][j] = A[maxRow][j];
//                 A[maxRow][j] = temp;
//             }
//         }

//         // Если ведущий элемент нулевой — ошибка (система вырожденная)
//         if (abs(A[col][col]) < 1e-10) {
//             cout << "Ошибка: Система вырожденная (точки копланарны?). Нет уникальной сферы.\n";
//             return 1;
//         }

//         // Вычитаем из нижних строк, чтобы обнулить столбец
//         for (int row = col + 1; row < 4; row++) {
//             double factor = A[row][col] / A[col][col];
//             for (int j = col; j < 5; j++) {
//                 A[row][j] -= factor * A[col][j];
//             }
//         }
//     }

//     // Шаг 4: Обратный ход (находим X = (D, E, F, G) снизу вверх)
//     double D, E, F, G;
//     G = A[3][4] / A[3][3];  // Последняя строка
//     F = (A[2][4] - A[2][3] * G) / A[2][2];
//     E = (A[1][4] - A[1][2] * F - A[1][3] * G) / A[1][1];
//     D = (A[0][4] - A[0][1] * E - A[0][2] * F - A[0][3] * G) / A[0][0];

//     // Шаг 5: Находим центр (a,b,c) и радиус r
//     double a = -D / 2.0;
//     double b = -E / 2.0;
//     double c = -F / 2.0;
//     double r_squared = a*a + b*b + c*c - G;
//     double r = sqrt(r_squared);

//     // Шаг 6: Выводим результат
//     cout << "Уравнение сферы: x² + y² + z² + " 
//               << D << "x + " << E << "y + " << F << "z + " << G << " = 0\n";
//     cout << "Центр: (" << a << ", " << b << ", " << c << ")\n";
//     cout << "Радиус: " << r << "\n";

//     // Проверка: подставляем первую точку (должно быть близко к 0)
//     double check = x[0]*x[0] + y[0]*y[0] + z[0]*z[0] + D*x[0] + E*y[0] + F*z[0] + G;
//     cout << "Проверка для точки 1: " << check << " (должно быть ~0)\n";

//     return 0;
// }




////ЗАДАЧИ ИЗ ФАЙЛА

#include <iostream>
using namespace std;

//1
int main() {
    int N;
    cout << "размер квадратной матрицы:" << endl;
    cin >> N;
    int A[100][100];

    cout << "элементы матрицы размера " << N  << ":" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> A[i][j];

    
    //Отражение относительно главной диагонали
    int m1[100][100];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m1[i][j] = A[j][i];
    
    //Отражение относительно побочной диагонали
    int m2[100][100];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m2[i][j] = A[N-1-j][N-1-i];
    
    //Зеркальное отражение относительно вертикальной оси
    int m3[100][100];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m3[i][j] = A[i][N-1-j];
    
    //Зеркальное отражение относительно горизонтальной оси
    int m4[100][100];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            m4[i][j] = A[N-1-i][j];
    
    // Вывод матриц
    cout << "Матрица:" << endl;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) cout << A[i][j] << " ";       //начальная матрица
        cout << endl;
    }
        
    cout << "Матрица, отраженная относительно главной диагонали" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << m1[i][j] << " ";
        cout << endl;
    }

    cout << "Матрица, отражение относительно побочной диагонали" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << m2[i][j] << " ";
        cout << endl;
    }

    cout << "Матрица, зеркальное отражение относительно вертикальной оси" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << m3[i][j] << " ";
        cout << endl;
    }

    cout << "Матрица, зеркальное отражение относительно горизонтльной оси" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) cout << m4[i][j] << " ";
        cout << endl;
    }
    return 0;
}


//2
int main(){
    int N = 0;
    double m[50][50];

    cout << "Введите порядок матрицы\n";
    cin >> N;

    // Ввод элементов матрицы
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> m[i][j];
        }
    }

    // Вывод матрицы
    cout << "\nМатрица" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }

    // Вычисляем сумму первой строки (остальные суммы будем сравнивать с ней)
    int fixSum = 0;
    for (int j = 0; j < N; j++) {
        fixSum += m[0][j];
    }

    // Проверим суммы всех строк
    for (int i = 1; i < N; i++) {
        int lineSum = 0;
        for (int j = 0; j < N; j++) {
            lineSum += m[i][j];
        }
        if (lineSum != fixSum)
            cout << "NO" << endl;
        
    }

    // Проверим суммы всех столбцов
    for (int j = 0; j < N; j++) {
        int colSum = 0;
        for (int i = 0; i < N; i++) {
            colSum += m[i][j];
        }
        if (colSum != fixSum) 
            cout << "NO" << endl;
    }

    // Проверим сумму элементов главной диагонали
    int maindiagSum = 0;
    for (int i = 0; i < N; i++) {
        maindiagSum += m[i][i];
    }
    if (maindiagSum != fixSum) {
        cout << "NO" << endl;
    }

    // Проверим сумму элементов побочной диагонали
    int sidediagSum = 0;
    for (int i = 0; i < N; i++) {
        sidediagSum += m[i][N - 1 - i];
    }
    if (sidediagSum != fixSum)
        cout << "NO" << endl;

    // Если все проверки пройдены
    cout << "YES " << fixSum << endl;

    return 0;
}



//3
int main() {
    int N, M;
    cout << "кол-во строк и столбцов:" << endl;
    cin >> N >> M;
    int A[100][100];
    
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> A[i][j];

    int row_min[100], row_max[100];
    int col_min[100], col_max[100];
    
    // Находим min и max для каждой строки
    for (int i = 0; i < N; i++) {
        row_min[i] = A[i][0];
        row_max[i] = A[i][0];
        for (int j = 1; j < M; j++) {
            if (A[i][j] < row_min[i]) row_min[i] = A[i][j];
            if (A[i][j] > row_max[i]) row_max[i] = A[i][j];
        }
    }
    
    // Находим min и max для каждого столбца
    for (int j = 0; j < M; j++) {
        col_min[j] = A[0][j];
        col_max[j] = A[0][j];
        for (int i = 1; i < N; i++) {
            if (A[i][j] < col_min[j]) col_min[j] = A[i][j];
            if (A[i][j] > col_max[j]) col_max[j] = A[i][j];
        }
    }
    
    bool found = false;
    // Ищем точки типа A (min в строке, max в столбце)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == row_min[i] && A[i][j] == col_max[j]) {
                cout << "A " << A[i][j] << " " << i+1 << " " << j+1 << endl;
                found = true;
            }
        }
    }
    
    // Ищем точки типа B (max в строке, min в столбце)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == row_max[i] && A[i][j] == col_min[j]) {
                cout << "B " << A[i][j] << " " << i+1 << " " << j+1 << endl;
                found = true;
            }
        }
    }
    
    if (!found) cout << "NONE" << endl;
}



// Задача 4: Спиральное заполнение матрицы
int main() {
    int N;
    cin >> N;
    int A[100][100] = {0};
    
    int num = 1;
    int top = 0, bottom = N-1, left = 0, right = N-1;
    
    while (num <= N*N) {
        // Вправо
        for (int j = left; j <= right && num <= N*N; j++)
            A[top][j] = num++;
        top++;
        
        // Вниз
        for (int i = top; i <= bottom && num <= N*N; i++)
            A[i][right] = num++;
        right--;
        
        // Влево
        for (int j = right; j >= left && num <= N*N; j--)
            A[bottom][j] = num++;
        bottom--;
        
        // Вверх
        for (int i = bottom; i >= top && num <= N*N; i--)
            A[i][left] = num++;
        left++;
    }
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
    return 0;
}

// Задача 5: Обход матрицы по спирали (чтение)
int main() {
    int N, M;
    cin >> N >> M;
    int A[100][100];
    
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> A[i][j];
    
    int top = 0, bottom = N-1, left = 0, right = M-1;
    int count = 0;
    
    while (count < N*M) {
        // Вправо
        for (int j = left; j <= right && count < N*M; j++) {
            cout << A[top][j] << " ";
            count++;
        }
        top++;
        
        // Вниз
        for (int i = top; i <= bottom && count < N*M; i++) {
            cout << A[i][right] << " ";
            count++;
        }
        right--;
        
        // Влево
        for (int j = right; j >= left && count < N*M; j--) {
            cout << A[bottom][j] << " ";
            count++;
        }
        bottom--;
        
        // Вверх
        for (int i = bottom; i >= top && count < N*M; i--) {
            cout << A[i][left] << " ";
            count++;
        }
        left++;
    }
    cout << endl;
    return 0;
}

// Задача 6: Решить систему 2x2
int main() {
    // 2x + 3y = 13
    // 5x - y = 9
    
    // Решаем методом Крамера
    double det = 2*(-1) - 3*5;  // главный определитель
    double det_x = 13*(-1) - 3*9;
    double det_y = 2*9 - 13*5;
    
    double x = det_x / det;
    double y = det_y / det;
    
    cout << "x = " << x << ", y = " << y << endl;
    return 0;
}

// Задача 7: Решить систему 3x3
int main() {
    // x + y + z = 6
    // 2x - y + 3z = 14  
    // -x + 4y - z = 2
    
    // Метод Крамера
    double det = 1*(-1)*(-1) + 1*3*(-1) + 1*2*4 - 1*(-1)*(-1) - 1*2*(-1) - 1*3*4;
    double det_x = 6*(-1)*(-1) + 1*3*2 + 1*14*4 - 1*(-1)*2 - 1*14*(-1) - 6*3*4;
    double det_y = 1*14*(-1) + 6*3*(-1) + 1*2*2 - 1*14*(-1) - 1*2*(-1) - 6*3*2;
    double det_z = 1*(-1)*2 + 1*14*(-1) + 6*2*4 - 6*(-1)*(-1) - 1*2*2 - 1*14*4;
    
    double x = det_x / det;
    double y = det_y / det;
    double z = det_z / det;
    
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
    return 0;
}

// Задача 8: Решить систему 3x3
int main() {
    // 3x - y + 2z = 5
    // 2x + 4y - z = 6
    // x - 3y + z = 4
    
    // Метод Крамера
    double det = 3*4*1 + (-1)*(-1)*1 + 2*2*(-3) - 2*4*1 - (-1)*2*1 - 3*(-1)*(-3);
    double det_x = 5*4*1 + (-1)*(-1)*4 + 2*6*(-3) - 2*4*4 - (-1)*6*1 - 5*(-1)*(-3);
    double det_y = 3*6*1 + 5*(-1)*1 + 2*2*4 - 2*6*1 - 5*2*1 - 3*(-1)*4;
    double det_z = 3*4*4 + (-1)*6*1 + 5*2*(-3) - 5*4*1 - (-1)*2*4 - 3*6*(-3);
    
    double x = det_x / det;
    double y = det_y / det;
    double z = det_z / det;
    
    cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
    return 0;
}
   
    

































