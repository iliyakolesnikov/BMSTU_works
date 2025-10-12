#include <iostream>
using namespace std;
int main(){
    int ds;
    cout << "введи длину в см: ";
    cin >> ds;
    int dm = ds/100;
    int dms = ds%100;
    cout << "перевод в м и см: " << dm << " м, "  << dms << " см";
    return 0;
}