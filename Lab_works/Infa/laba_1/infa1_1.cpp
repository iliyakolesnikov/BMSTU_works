#include <iostream>
using namespace std;
int main(){
    setlocale(LC_ALL, "rus");
    int t;
    cout << "Сколько у вас топлива?";
    cin >>t;
    if (t >50){
        cout << "Топлива достаточно";
    }    
    else if (t >= 20 and t <= 50){
        cout <<" Рекомендуется заправка";
    }    
    else{
        cout <<"Толпиво на исходе, срочно заправьтесь!";
    }    
    return 0;
}