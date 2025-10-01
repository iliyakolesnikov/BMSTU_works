#include <iostream>
using namespace std;
int main(){
    int t;
    cout << "Сколько вам лет?";
    cin >>t;
    if (t > 60){
        cout << "вам больше 60";
    }    
    else if (t >= 18 and t <= 60){
        cout << "вам от 18 до 60";
    }    
    else if (t < 18){
        cout <<"вам меньше 18";
    }    
    return 0;
}