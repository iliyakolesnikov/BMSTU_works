#include <iostream>
using namespace std;
int main(){
    int n;
    cout << "Введите число: ";
    cin >> n;
    if (n % 3 == 0 and n % 5 != 0){
        cout << "дел на 3";
    }
    else if (n % 5 == 0 and n % 3 != 0){
        cout << "дел на 5";
    }
     else if (n % 5 == 0 and n % 3 == 0){
        cout << "дел на 3 и на 5";
    }
    return 0;
}