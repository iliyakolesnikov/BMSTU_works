#include <iostream>
using namespace std;
int main(){
    int c;
    cout << "Введите температуру в цельсиях:";
    cin >> c;
    int f = c*9/5 + 32;
    cout << "Температура в фаренгейтах: " << f;
    return 0;
}