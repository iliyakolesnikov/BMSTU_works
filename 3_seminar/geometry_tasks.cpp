// //1

// #include <iostream>
// using namespace std;

// int main(){
//     int k[6];
//     cout << "Введите координаты вершин треугольника:" << endl;
//     for (int i = 0; i < 6; i++){
//         cin >> k[i];
//     }
//     float S = 0.5*abs(k[0]*(k[5]-k[3]) + k[2]*(k[5]-k[1]) + k[4]*(k[1]-k[3]));
//     cout << "Площадь треугольника = " << S << endl;
//     return 0;
// }




// //2

// #include <iostream>
// #include <cmath>
// using namespace std;

// int main(){
//     int k[8];
//     cout << "Введите координаты 4 вершин многоульника: " << endl;
//     for (int i = 0; i < 8; i++){
//         cin >> k[i];
//     }
//     int a1 = pow(pow(k[0],2) + pow(k[1],2),0.5);
//     int a2 = pow(pow(k[2],2) + pow(k[3],2),0.5);
//     int a3 = pow(pow(k[4],2) + pow(k[5],2),0.5);
//     int a4 = pow(pow(k[6],2) + pow(k[7],2),0.5);
//     cout << "Периметр равен " << a1+a2+a3+a4;
//     return 0;
// }




// //3

// #include <iostream>
// #include <cmath>
// using namespace std;

// int main(){
//     int k[6];
//     cout << "Введите координаты 3 вершин многоульника: " << endl;
//     for (int i = 0; i < 6; i++){
//         cin >> k[i];
//     }
//     int Cx = (k[0] + k[2] + k[4])/3;
//     int Cy = (k[1] + k[3] + k[5])/3;
//     cout << "Координаты центра масс: " << "x - " << Cx << ";   y - " << Cy << endl;
//     return 0;
// }




// //4

// #include <iostream>
// #include <cmath>
// using namespace std;

// int main(){
//     int k[8];
//     cout << "Введите координаты 4 вершин прямоугольника: " << endl;
//     for (int i = 0; i < 8; i++){
//         cin >> k[i];
//     }

//     int mx_sm = -100000;
//     int mn_sm = 100000;
//     int Xmx = 0;
//     int Ymx = 0;
//     int Xmn = 0;
//     int Ymn = 0;

//     for (int i = 0; i < 7; i+=2){
//         int sm = k[i] + k[i+1];
//         if (sm > mx_sm){
//             mx_sm = sm;
//             Xmx = k[i];
//             Ymx = k[i+1];
//         } 
//         if (sm < mn_sm){
//             mn_sm = sm;
//             Xmn = k[i];
//             Ymn = k[i+1];
//         } 
//     }
//     float X = pow(Xmx - Xmn,2);
//     float Y = pow(Ymx - Ymn,2);
//     float d = pow(X+Y,0.5);
//     cout << "длина диагонали =  " << d << endl;
//     return 0;
// }




// //5

// #include <iostream>
// #include <cmath>
// using namespace std;

// int main(){
//     int k[6];
//     cout << "Введите координаты 3 точек: " << endl;
//     for (int i = 0; i < 6; i++){
//         cin >> k[i];
//     }
//     if ((k[2]-k[0])*(k[5]-k[1]) - (k[3]-k[1])*(k[4]-k[0]) == 0){
//         cout << "точки лежат на одной прямой" << endl;
//     }
//     else{
//         cout << "не лежат на одной прямой" << endl;
//     }
//     return 0;
// }




// //6

// #include <iostream>
// using namespace std;

// int main(){
// 	const int a = 4;
// 	int kX[a];
// 	int kY[a];
//     cout << "Введите координаты вершин отрезков:" << endl;
// 	for (int i = 0; i < a; i++) {
// 		cin >> kX[i];
// 		cin >> kY[i];
// 	}
// 	int x1 = kX[0];
// 	int x2 = kX[1];
// 	int x3 = kX[2];
// 	int x4 = kX[3];
// 	int y1 = kY[0];
// 	int y2 = kY[1];
// 	int y3 = kY[2];
// 	int y4 = kY[3];
// 	if ((x2 >= x4 && y2>=y4 && x1<=x3 && y1<=y3)||(x2 <= x4 && y2 <= y4 && x1 >= x3 && y1 >= y3)) {
// 		cout << "Пересечение" << endl;
// 	}
//     else{
//         cout << "Не переcекаются" << endl;
//     }
// 	return 0;
// }




// //8

// #include <iostream>
// #include <cmath>
// using namespace std;
// int main(){
//     int k[2][2];
//     cout << "Введите координаты 2 точек отрезка: " << endl;
//     for (int i = 0; i < 2; i++){
//         for (int j = 0; j < 2; j++){
//             cin >> k[i][j];
//         }
//     } 
//     int dx = k[0][0] - k[1][0];
//     int dy = k[0][1] - k[1][1];
//     int d = pow(pow(dx,2) + pow(dy,2),0.5);
//     cout << "длина = " << d << endl;
// 	return 0;
// }




// //9

// #include <iostream>
// using namespace std;

// int main() {
//     int n1, n2;
//     double x1[100], y1[100], x2[100], y2[100];

//     cout << "Введите количество вершин первого многоугольника (до 100): ";
//     cin >> n1;
//     cout << "Введите координаты " << n1 << " вершин: " << endl;
//     for (int i = 0; i < n1; i++) {
//         cin >> x1[i] >> y1[i];
//     }

//     cout << "Введите количество вершин второго многоугольника (до 100): ";
//     cin >> n2;
//     cout << "Введите координаты " << n2 << " вершин: " << endl;
//     for (int i = 0; i < n2; i++) {
//         cin >> x2[i] >> y2[i];
//     }

//     // Проверка пересечения
//     for (int i = 0; i < n1; i++) {
//         double Ax = x1[i], Ay = y1[i];
//         double Bx = x1[(i + 1) % n1], By = y1[(i + 1) % n1];

//         for (int j = 0; j < n2; j++) {
//             double Cx = x2[j], Cy = y2[j];
//             double Dx = x2[(j + 1) % n2], Dy = y2[(j + 1) % n2];

//             double v1 = (Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax);
//             double v2 = (Bx - Ax) * (Dy - Ay) - (By - Ay) * (Dx - Ax);
//             double v3 = (Dx - Cx) * (Ay - Cy) - (Dy - Cy) * (Ax - Cx);
//             double v4 = (Dx - Cx) * (By - Cy) - (Dy - Cy) * (Bx - Cx);

//             if (v1 * v2 < 0 and v3 * v4 < 0) {
//                 cout << "многоульники пересекаются" << endl;
//                 return 0;
//             }
//         }
//     }
//     cout << "не пересекаются" << endl;
//     return 0;
// }


























