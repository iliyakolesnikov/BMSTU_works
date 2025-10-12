#include <iostream>
using namespace std;
int main(){
    setlocale(LC_ALL, "rus");
    int t = 1;
    while (t >= 0){
        cout << "Введите кол-во литров:";
        cin >> t;    
    }
    cout << "Вы ввели отрицательное число, конец программы";
    return 0;
}

