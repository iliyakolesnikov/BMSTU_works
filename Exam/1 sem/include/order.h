using namespace std;

#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "order_item.h"
#include "payment.h"

class Order {
private:
    int orderId;
    int userId;
    string orderDate;
    string status;  // pending, completed, cancelled, returned
    vector<OrderItem> items;
    unique_ptr<Payment> payment;
    double totalAmount;
    
public:
    Order(int id, int uid, const string& date)
        : orderId(id), userId(uid), orderDate(date), 
          status("pending"), totalAmount(0.0) {}
    
    int getOrderId() const { return orderId; }
    int getUserId() const { return userId; }
    string getOrderDate() const { return orderDate; }
    string getStatus() const { return status; }
    double getOrderTotal() const { return totalAmount; }
    
    void addItem(const OrderItem& item) {
        items.push_back(item);
        totalAmount += item.getTotal();
    }
    
    void removeItem(int productId) {
        auto it = find_if(items.begin(), items.end(),
            [productId](const OrderItem& item) {
                return item.getProductId() == productId;
            });
        
        if (it != items.end()) {
            totalAmount -= it->getTotal();
            items.erase(it);
        }
    }
    
    void setPayment(unique_ptr<Payment> p) {
        payment = move(p);
    }
    
    bool processPayment() {
        if (!payment) {
            cerr << "Ошибка: платёж не установлен" << endl;
            return false;
        }
        return payment->processPayment();
    }
    
    void updateStatus(const string& newStatus) {
        status = newStatus;
        cout << "Статус заказа " << orderId << " обновлён на: " << newStatus << endl;
    }
    
    bool canReturn() const {
        return status == "completed" && !orderDate.empty();
    }
    
    vector<OrderItem>& getItems() {
        return items;
    }
    
    void displayItems() const {
        cout << "\nТовары в заказе " << orderId << ":" << endl;
        for (const auto& item : items) {
            cout << "  - " << item.getProductName() << ": " 
                 << item.getQuantity() << " x " << item.getUnitPrice() 
                 << " = " << item.getTotal() << " руб." << endl;
        }
        cout << "Итого: " << totalAmount << " руб." << endl;
    }
};

#endif
