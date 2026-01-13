using namespace std;

#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Order;

class User {
protected:
    int userId;
    string name;
    string email;
    string role;
    vector<shared_ptr<Order>> orders;
    
public:
    User(int id, const string& n, const string& e, const string& r)
        : userId(id), name(n), email(e), role(r) {}
    
    virtual ~User() = default;
    
    virtual void displayMenu() = 0;
    virtual bool viewOrderStatus() = 0;
    virtual bool cancelOrder(int orderId) = 0;
    
    int getUserId() const { return userId; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getRole() const { return role; }
    
    void addOrder(shared_ptr<Order> order) {
        orders.push_back(order);
    }
    
    size_t getOrderCount() const {
        return orders.size();
    }
    
    vector<shared_ptr<Order>>& getOrders() {
        return orders;
    }
    
    void displayUserInfo() const {
        cout << "\n=== Информация о пользователе ===" << endl;
        cout << "ID: " << userId << endl;
        cout << "Имя: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Роль: " << role << endl;
        cout << "Количество заказов: " << orders.size() << endl;
    }
};

#endif
