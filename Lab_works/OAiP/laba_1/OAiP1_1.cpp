#include <iostream>
using namespace std;

const int s = 10;
int i = 0;
int j = 0;
int nums[10]; 
//сортировка пузырьком в порядке убывания
void bubbleSort(int nums[],int s){
    for (int i = 0; i < s; i++){
        for (int j = 0; j < s; j++){
            if (nums[j] < nums[j+1]){       //если текущий элемент меньше следующего
                int m = nums[j];            //записываем в переменную значение предыдущего (текущий минимальный)
                nums[j] = nums[j+1];        //в предыдущий элемент записываем значение следующего
                nums[j+1] = m;              //в следующий записываем значение m (текущий минимальный)
            }    
        }
    }
}


int main(){
//создание массива, ввод и вывод элементов      
    for (int i = 0; i < s; i++){
        cout << i+1 << " element:";
        cin >> nums[i];
    }
    for (int i = 0; i < s; i++){
        cout << nums[i] << " ";
    }
    cout << endl;   

//поиск суммы элементов
    int sum = 0;
    for (int i = 0; i < s; i++){
        sum += nums[i];
    }
    cout << "Сумма элементов = " << sum;
    cout << endl;

//поиск максимального элемента
    int max = -1000000;
    for (int i = 0; i < s; i++){
        if (nums[i] > max){
            max = nums[i];
        } 
    }
    cout << "Максимальный элемент = " << max << endl;

//обращение к функции сортировки
    bubbleSort(nums, s);
    cout << "Отсортированные элементы массива (по убыванию): ";
    for (int i = 0; i < s; i++) {
        cout << nums[i] << " ";
    }        
    return 0;
}