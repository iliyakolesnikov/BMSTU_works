using namespace std;

#ifndef PAYMENT_STRATEGY_H
#define PAYMENT_STRATEGY_H

#include <string>
#include <iostream>

class PaymentStrategy {
public:
    virtual bool processPayment(double amount) = 0;
    virtual string getPaymentMethod() const = 0;
    virtual ~PaymentStrategy() = default;
};

class CardPayment : public PaymentStrategy {
private:
    string cardNumber;
    string expiryDate;
    string cvv;
    
public:
    CardPayment(const string& num, const string& date, const string& c)
        : cardNumber(num), expiryDate(date), cvv(c) {}
    
    bool processPayment(double amount) override {
        cout << "Обработка платежа картой: " << amount << " руб." << endl;
        cout << "Карта: " << cardNumber.substr(0, 4) << "****" << cardNumber.substr(12) << endl;
        cout << "Платёж успешно обработан!" << endl;
        return true;
    }
    
    string getPaymentMethod() const override {
        return "Card Payment";
    }
};

class EWalletPayment : public PaymentStrategy {
private:
    string walletId;
    
public:
    explicit EWalletPayment(const string& id) : walletId(id) {}
    
    bool processPayment(double amount) override {
        cout << "Обработка платежа кошельком: " << amount << " руб." << endl;
        cout << "ID кошелька: " << walletId << endl;
        cout << "Платёж успешно обработан!" << endl;
        return true;
    }
    
    string getPaymentMethod() const override {
        return "E-Wallet Payment";
    }
};

class SBPPayment : public PaymentStrategy {
private:
    string phoneNumber;
    
public:
    explicit SBPPayment(const string& phone) : phoneNumber(phone) {}
    
    bool processPayment(double amount) override {
        cout << "Обработка платежа через СБП: " << amount << " руб." << endl;
        cout << "Номер телефона: " << phoneNumber << endl;
        cout << "Платёж успешно обработан!" << endl;
        return true;
    }
    
    string getPaymentMethod() const override {
        return "SBP Payment";
    }
};

#endif
