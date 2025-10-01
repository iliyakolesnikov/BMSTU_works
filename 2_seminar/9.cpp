#include <iostream>
using namespace std;
int main(){
    int n;
    cout << "введи число";
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++){
        if (i % 2 == 0 or i % 5 == 0){
            sum += i;
        }
    }
    cout << "сумма чисел кратных 2 или 5 = " << sum << endl;
    return 0;
}