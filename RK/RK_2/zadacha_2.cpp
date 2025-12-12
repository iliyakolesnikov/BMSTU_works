#include <iostream>
#include <string>

using namespace std;

// Задача 2

// Базовый класс BankAccount
class BankAccount {
protected:
    string accountNumber;
    string ownerName;
    double balance;

public:
    // Конструктор
    BankAccount(string accNum, string name, double initialBalance) 
        : accountNumber(accNum), ownerName(name), balance(initialBalance) {}

    // Метод для пополнения
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Счет пополнен на " << amount << ". Текущий баланс: " << balance << endl;
        } else {
            cout << "Сумма пополнения должна быть положительной." << endl;
        }
    }

    // Метод для снятия средств
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Снято " << amount << ". Текущий баланс: " << balance << endl;
        } else {
            cout << "Недостаточно средств или некорректная сумма." << endl;
        }
    }

    // Метод для отображения информации
    void displayInfo() const {
        cout << "Счет: " << accountNumber << ", Владелец: " << ownerName << ", Баланс: " << balance << endl;
    }
};

// Производный класс SavingsAccount
class SavingsAccount : public BankAccount {
private:
    double interestRate; // Процентная ставка

public:
    // Конструктор
    SavingsAccount(string accNum, string name, double initialBalance, double rate)
        : BankAccount(accNum, name, initialBalance), interestRate(rate) {}

    // Метод для начисления процентов
    void applyInterest() {
        double interest = balance * interestRate;
        balance += interest;
        cout << "Начислены проценты: " << interest << ". Новый баланс: " << balance << endl;
    }
};

void runTask2() {

    // 1. Создание обычного счета
    cout << "\n--- Работа с обычным счетом ---" << endl;
    BankAccount myAccount("RU123456", "Илья Колесников", 10000.0);
    myAccount.displayInfo();
    myAccount.deposit(500.0);
    myAccount.withdraw(200.0);
    myAccount.withdraw(2000.0); 

    // 2. Создание сберегательного счета
    cout << "\n--- Работа со сберегательным счетом ---" << endl;
    SavingsAccount mySavings("RU987654", "Илья Колесников", 5000.0, 0.05); // Ставка 5%
    mySavings.displayInfo();
    mySavings.deposit(1000.0);
    mySavings.applyInterest(); // Начисление процентов
    mySavings.withdraw(300.0);

    cout << endl;
}

int main() {
    runTask2();
    return 0;
}
