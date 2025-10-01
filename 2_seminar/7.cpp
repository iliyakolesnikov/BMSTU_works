#include <iostream>
using namespace std;
int main(){
    int n;
    cout << "введите число";
    cin >> n;
    for (int i = 0; i < n; i++){
        cout << (i+1)*(i+1) << endl;
    }
    return 0;
}