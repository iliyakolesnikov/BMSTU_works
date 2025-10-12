// //1

// #include <iostream>
// #include <cmath>
// using namespace std;

// int main() {
//     int n;    
//     cout << "Введите количество натуральных чисел: ";
//     cin >> n;
    
//     int cnt = 0;
//     int currentNumber;
    
//     cout << "Введите последовательность из " << n << " чисел:" << endl;
//     for (int k = 1; k <= n; k++) {
//         cin >> currentNumber;

//         int stepen = pow(2,k);          //находим 2 в степени порядкового номера числа k
//         if (currentNumber > stepen) {
//             cnt++;
//             cout << "A" << k << " = " << currentNumber << " > 2**" << k << " = " << 2*k << " ✓" << endl;
//         }
//     }    
//     cout << "\nИтого: " << cnt << " чисел удовлетворяют условию Ak > 2k" << endl;    
//     return 0;
// }




// //2

// #include <iostream>
// using namespace std;

// int main(){
//     int n;
//     cout << "Введите кол-во чисел: ";
//     cin >> n;

//     int num;
//     int cnt = 0;
//     long current_max = -1000000;

//     cout << "Введите последовательность из " << n << " чисел:" << endl;
//     for (int k = 1; k <= n; k++){
//         cin >> num;
//         if (num % 2 == 0){
//             cnt ++;
//         }
//         if ((num % 2 != 0) and (num > current_max)){
//             current_max = num;
//         }
//     }
//     cout << "\nкол-во четных чисел = " << cnt << endl;
//     cout << "наибольшее нечетное число = " << current_max << endl;
//     return 0;
// }




// //3.1

// #include <iostream>
// using namespace std;

// int main(){
//     const int s = 15;
//     double nums[s];    

//     cout << "введите массив из " << s << " элементов: " << endl;
//     for (int i = 0; i < s; i++){
//         cin >> nums[i];
//     }

// // Поиск индексов минимального и максимального элементов
//     int min_ind = 0;
//     int max_ind = 0;
//     for (int i = 0; i < s; i++){
//          if (nums[i] < nums[min_ind]){
//             min_ind = i;
//         }
//         if (nums[i] > nums[max_ind]){
//             max_ind = i;
//         }
//     }
       
//     cout << "исходный массив: ";
//     for (int i = 0; i < s; i++){
//         cout << nums[i] << " ";
//     }
//     cout << endl;

//     double t = nums[0];
//     nums[0] = nums[min_ind];            //обмен минимального с первым
//     nums[min_ind] = t;

//     t = nums[s-1];
//     nums[s-1] = nums[max_ind];         //обмен максимального с последним
//     nums[max_ind] = t;

//     cout << "новый массив: ";
//     for (int i = 0; i < s; i++){
//         cout << nums[i] << " ";
//     }
//     cout << endl;
//     return 0;
// }



// //3.2 (альтернатива)

// #include <iostream>
// #include <algorithm>
// using namespace std;

// int main() {
//     const int N = 15;
//     double numbers[N];
    
//     // Ввод последовательности
//     cout << "Введите " << N << " вещественных чисел:" << endl;
//     for (int i = 0; i < N; i++) {
//         cin >> numbers[i];
//     }
    
//     // Поиск индексов минимального и максимального элементов
//     int minIndex = min_element(numbers, numbers + N) - numbers;
//     int maxIndex = max_element(numbers, numbers + N) - numbers;
    
//     // Вывод исходной последовательности
//     cout << "Исходная последовательность: ";
//     for (double num : numbers) {
//         cout << num << " ";
//     }
//     cout << endl;
    
//     // Обмен минимального с первым и максимального с последним
//     swap(numbers[0], numbers[minIndex]);
//     swap(numbers[N - 1], numbers[maxIndex]);
    
//     // Вывод результата
//     cout << "Результат: ";
//     for (double num : numbers) {
//         cout << num << " ";
//     }
//     cout << endl;    
//     return 0;
// }




// //4

// #include <iostream>
// using namespace std;

// int main(){
//     const int s = 15;
//     float nums[s];

//     cout << "Введите последовательность из " << s << " чисел: " << endl;
//     for (int i = 0; i < s; i++){
//         cin >> nums[i];
//     }

//     cout << "исходный массив: ";
//     for (int i = 0; i < s; i++){
//         cout << nums[i] << " ";
//     }
//     cout << endl;

//     int min_ind = 0;
//     int max_ind = 0;
//     for (int i = 0; i < s; i++){
//          if (nums[i] < nums[min_ind]){
//             min_ind = i;
//         }
//         if (nums[i] > nums[max_ind]){
//             max_ind = i;
//         }
//     }
//     if (max_ind < min_ind){
//         cout << "произведение = " << nums[max_ind]*nums[min_ind] << endl;
//     }
//     return 0;  
// }




//5

// #include <iostream>
// using namespace std;

// int main(){
//     const int s = 10;
//     int nums[s];

//     cout << "Введите последовательность из " << s << " чисел: " << endl;
//     for (int i = 0; i < s; i++){
//         cin >> nums[i];
//     }

//     cout << "исходный массив: ";
//     for (int i = 0; i < s; i++){
//         cout << nums[i] << " ";
//     }
//     cout << endl;

//     int min_ind = 0;
//     int max_ind = 0;
//     for (int i = 0; i < s; i++){
//          if (nums[i] < nums[min_ind]){
//             min_ind = i;
//         }
//         if (nums[i] > nums[max_ind]){
//             max_ind = i;
//         }
//     }

//     if ((min_ind == 4) and (max_ind == 9)){
//         cout << "ср арифм = " << (nums[min_ind] + nums[max_ind]) / 2 << endl;
//     }
//     return 0;
// }




// //6

// #include <iostream>
// using namespace std;

// int main(){
//     const int s = 15;
//     float nums[s];

//     cout << "Введите последовательность из " << s << " чисел: " << endl;
//     for (int i = 0; i < s; i++){
//         cin >> nums[i];
//     }

//     cout << "исходный массив: ";
//     for (int i = 0; i < s; i++){
//         cout << nums[i] << " ";
//     }
//     cout << endl;

//     int min_ind = 0;
//     int max_ind = 0;
//     for (int i = 0; i < s; i++){
//          if (nums[i] < nums[min_ind]){
//             min_ind = i;
//         }
//         if (nums[i] > nums[max_ind]){
//             max_ind = i;
//         }
//     }

//     if ((min_ind == 1) and (max_ind == 0)){
//         cout << "новый массив: ";
//         for (int i = 0; i < s; i++){
//             cout << nums[i] / 2 << " ";
//         }
//     }
//     return 0;
// }




// //7

// #include <iostream>
// using namespace std;

// int main(){
//     const int s = 15;
//     int nums[s];

//     cout << "Введите последовательность из " << s << " чисел: " << endl;
//     for (int i = 0; i < s; i++){
//         cin >> nums[i];
//     }

//     cout << "исходный массив: ";
//     for (int i = 0; i < s; i++){
//         cout << nums[i] << " ";
//     }
//     cout << endl;

//     int min_ind = 0;
//     int max_ind = 0;
//     for (int i = 0; i < s; i++){
//          if (nums[i] < nums[min_ind]){
//             min_ind = i;
//         }
//         if (nums[i] > nums[max_ind]){
//             max_ind = i;
//         }
//     }
    
//     if (nums[min_ind] == 0 or nums[max_ind] == 0){
//         cout << "новый массив: ";
//         for (int i = 0; i < min_ind; i++){
//             cout << nums[i]*0 << " ";
//         }
//         for (int i = min_ind; i < s; i++){
//         cout << nums[i] << " ";
//         }
//     }
//     cout << endl;
//     return 0;
// }




// //8

// #include <iostream>
// using namespace std;

// int main(){
//     const int s = 10;
//     int nums[s];

//     cout << "Введите последовательность из " << s << " чисел: " << endl;
//     for (int i = 0; i < s; i++){
//         cin >> nums[i];
//     }

//     cout << "исходный массив: ";
//     for (int i = 0; i < s; i++){
//         cout << nums[i] << " ";
//     }
//     cout << endl;

//     int min_ind = 0;
//     int max_ind = 0;
//     for (int i = 0; i < s; i++){
//          if (nums[i] < nums[min_ind]){
//             min_ind = i;
//         }
//         if (nums[i] > nums[max_ind]){
//             max_ind = i;
//         }
//     }
     
//     if (min_ind == 4 and max_ind == 1){
//         cout << "новый массив: ";
//         for (int i = 0; i < min_ind; i++){
//             cout << nums[i] << " ";
//         }
//         for (int i = min_ind; i < s; i++){
//             nums[i] = nums[max_ind];
//             cout << nums[i] << " ";
//         }
//     }
//     cout << endl;
//     return 0;
// }


































