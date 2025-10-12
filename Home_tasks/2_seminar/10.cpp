#include <iostream>
using namespace std;
int main(){
    int n;
    cout << "Введите число: ";
    cin >> n;
    if (n > 0){
        cout << "положительное";
    }
    else if (n == 0){
        cout << " равно 0";
    }
     else if (n < 0){
        cout << "отрицательное";
    }
    cout << endl;
    return 0;
}