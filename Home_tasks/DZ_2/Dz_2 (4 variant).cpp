#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

//  Класс управления освещением 
class Light {
private:
    bool isOn;

public:
    Light() : isOn(false) {}

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    
    // Возвращаем статус на русском (мужской род, т.к. Свет)
    string getStatus() const { return isOn ? "Включен" : "Выключен"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};

//  Класс управления термостатом 
class Thermostat {
private:
    int temperature;

public:
    Thermostat() : temperature(20) {}

    void setTemperature(int t) { temperature = t; }
    int getTemperature() const { return temperature; }
};

//  Класс системы безопасности 
class SecuritySystem {
private:
    bool isArmed;

public:
    SecuritySystem() : isArmed(false) {}

    void arm() { isArmed = true; }
    void disarm() { isArmed = false; }
    
    // Женский род, т.к. Система
    string getStatus() const { return isArmed ? "Включена" : "Выключена"; }
    bool getState() const { return isArmed; }
    void setState(bool state) { isArmed = state; }
};

//  Класс управления шторами 
class Curtains {
private:
    bool isUp;

public:
    Curtains() : isUp(false) {}

    void raise() { isUp = true; }
    void lower() { isUp = false; }
    
    // Множественное число
    string getStatus() const { return isUp ? "Подняты" : "Опущены"; }
    bool getState() const { return isUp; }
    void setState(bool state) { isUp = state; }
};

//  Класс управления кондиционером 
class AirConditioner {
private:
    bool isOn;

public:
    AirConditioner() : isOn(false) {}

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }
    
    // Мужской род
    string getStatus() const { return isOn ? "Включен" : "Выключен"; }
    bool getState() const { return isOn; }
    void setState(bool state) { isOn = state; }
};

//  Основной класс SmartHome 
class SmartHome {
private:
    Light light;
    Thermostat thermostat;
    SecuritySystem security;
    Curtains curtains;
    AirConditioner ac;
    string stateFile;

public:
    SmartHome(string filename = "home_state.txt") : stateFile(filename) {
        loadState();
    }

    void controlLight(bool state) {
        state ? light.turnOn() : light.turnOff();
    }

    void setTemperature(int temp) {
        thermostat.setTemperature(temp);
    }

    void controlSecurity(bool state) {
        state ? security.arm() : security.disarm();
    }

    void controlCurtains(bool state) {
        state ? curtains.raise() : curtains.lower();
    }

    void controlAirConditioner(bool state) {
        state ? ac.turnOn() : ac.turnOff();
    }

    // Отображение статуса
    void displayStatus() const {
        cout << "Текущее состояние:" << endl;
        cout << "Свет: " << light.getStatus() << endl;
        cout << "Температура: " << thermostat.getTemperature() << "°C" << endl;
        cout << "Система безопасности: " << security.getStatus() << endl;
        cout << "Шторы: " << curtains.getStatus() << endl;
        cout << "Кондиционер: " << ac.getStatus() << endl;
        cout << "-------------------------" << endl;
    }

    // Сохранение состояния
    void saveState() {
        ofstream outFile(stateFile);
        if (outFile.is_open()) {
            outFile << light.getState() << endl;
            outFile << thermostat.getTemperature() << endl;
            outFile << security.getState() << endl;
            outFile << curtains.getState() << endl;
            outFile << ac.getState() << endl;
            outFile.close();
            cout << "Состояние сохранено в файл " << stateFile << ". Выход..." << endl;
        } else {
            cerr << "Ошибка: Не удалось сохранить состояние в файл." << endl;
        }
    }

    // Загрузка состояния
    void loadState() {
        ifstream inFile(stateFile);
        if (inFile.is_open()) {
            bool lightState, securityState, curtainsState, acState;
            int temp;

            if (inFile >> lightState >> temp >> securityState >> curtainsState >> acState) {
                light.setState(lightState);
                thermostat.setTemperature(temp);
                security.setState(securityState);
                curtains.setState(curtainsState);
                ac.setState(acState);
                cout << "Состояние загружено из файла." << endl;
            } else {
                cout << "Ошибка чтения файла. Использованы настройки по умолчанию." << endl;
            }
            inFile.close();
        } else {
            cout << "Файл сохранения не найден. Использованы настройки по умолчанию." << endl;
        }
    }
};

int main() {

    SmartHome myHome;
    int choice;

    while (true) {
        myHome.displayStatus();
        
        cout << "Выберите действие:" << endl;
        cout << "1. Включить свет" << endl;
        cout << "2. Выключить свет" << endl;
        cout << "3. Задать температуру" << endl;
        cout << "4. Включить систему безопасности" << endl;
        cout << "5. Выключить систему безопасности" << endl;
        cout << "6. Поднять шторы" << endl;
        cout << "7. Опустить шторы" << endl;
        cout << "8. Включить кондиционер" << endl;
        cout << "9. Выключить кондиционер" << endl;
        cout << "10. Выход" << endl;
        cout << "> ";

        if (!(cin >> choice)) {
            cout << "Неверный ввод. Пожалуйста, введите число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 10) {
            myHome.saveState();
            break;
        }

        switch (choice) {
            case 1: myHome.controlLight(true); break;
            case 2: myHome.controlLight(false); break;
            case 3: {
                int t;
                cout << "Введите температуру: ";
                if (cin >> t) {
                    myHome.setTemperature(t);
                } else {
                    cout << "Некорректная температура!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            case 4: myHome.controlSecurity(true); break;
            case 5: myHome.controlSecurity(false); break;
            case 6: myHome.controlCurtains(true); break;
            case 7: myHome.controlCurtains(false); break;
            case 8: myHome.controlAirConditioner(true); break;
            case 9: myHome.controlAirConditioner(false); break;
            default: cout << "Неизвестная команда." << endl;
        }
        cout << endl;
    }

    return 0;
}

