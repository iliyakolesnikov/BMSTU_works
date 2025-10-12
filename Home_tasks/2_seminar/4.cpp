#include <iostream>
using namespace std;
int main(){
    int n;
    cout << "Введите число: ";
    cin >> n;
    if (n % 2 == 0){
        cout << "четное";
    }
    else{
        cout << "нечетное";
    }
    return 0;
}