using namespace std;

#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"
#include "product.h"
#include <algorithm>

class Manager : public User {
public:
    Manager(int id, const string& n, const string& e, const string& pwd)
        : User(id, n, e, "manager") {
        cout << "Создан менеджер: " << name << endl;
    }
    
    void displayMenu() override {
        cout << "\n=== МЕНЮ МЕНЕДЖЕРА ===" << endl;
        cout << "1. Просмотреть ожидающие заказы" << endl;
        cout << "2. Обновить статус заказа" << endl;
        cout << "3. Обработать платёж" << endl;
        cout << "4. Отклонить заказ" << endl;
        cout << "5. Информация о товарах" << endl;
    }
    
    bool viewOrderStatus() override {
        cout << "\nОжидающие заказы:" << endl;
        int pendingCount = 0;
        for (const auto& order : orders) {
            if (order->getStatus() == "pending") {
                cout << "  Заказ " << order->getOrderId() << " - " 
                     << order->getOrderTotal() << " руб." << endl;
                pendingCount++;
            }
        }
        cout << "Всего ожидающих: " << pendingCount << endl;
        return true;
    }
    
    bool cancelOrder(int orderId) override {
        cout << "Заказ " << orderId << " отклонён менеджером" << endl;
        return true;
    }
    
    vector<shared_ptr<Order>> viewPendingOrders() {
        vector<shared_ptr<Order>> pending;
        copy_if(orders.begin(), orders.end(), back_inserter(pending),
            [](const shared_ptr<Order>& order) {
                return order->getStatus() == "pending";
            });
        return pending;
    }
    
    void updateOrderStatus(int orderId, const string& newStatus) {
        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const shared_ptr<Order>& order) {
                return order->getOrderId() == orderId;
            });
        
        if (it != orders.end()) {
            (*it)->updateStatus(newStatus);
        }
    }
    
    void processPayment(int orderId) {
        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const shared_ptr<Order>& order) {
                return order->getOrderId() == orderId;
            });
        
        if (it != orders.end()) {
            if ((*it)->processPayment()) {
                updateOrderStatus(orderId, "completed");
            }
        }
    }
    
    void rejectOrder(int orderId) {
        updateOrderStatus(orderId, "cancelled");
        cout << "Заказ " << orderId << " отклонён" << endl;
    }
};

#endif
