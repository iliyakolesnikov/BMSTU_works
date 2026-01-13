using namespace std;

#ifndef PAYMENT_H
#define PAYMENT_H

#include <memory>
#include <string>
#include "payment_strategy.h"

class Payment {
private:
    int paymentId;
    double amount;
    string status;  // pending, completed, failed
    unique_ptr<PaymentStrategy> strategy;
    
public:
    Payment(int id, double amt) 
        : paymentId(id), amount(amt), status("pending") {}
    
    void setPaymentStrategy(unique_ptr<PaymentStrategy> s) {
        strategy = move(s);
    }
    
    bool processPayment() {
        if (!strategy) {
            cerr << "Ошибка: стратегия платежа не установлена" << endl;
            return false;
        }
        
        if (strategy->processPayment(amount)) {
            status = "completed";
            return true;
        } else {
            status = "failed";
            return false;
        }
    }
    
    string getPaymentStatus() const {
        return status;
    }
    
    double getAmount() const {
        return amount;
    }
    
    string getPaymentMethod() const {
        if (strategy) {
            return strategy->getPaymentMethod();
        }
        return "Unknown";
    }
};

#endif
