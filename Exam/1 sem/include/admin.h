using namespace std;

#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
#include "product.h"
#include <algorithm>

class Admin : public User {
private:
    vector<shared_ptr<Product>> productCatalog;
    
public:
    Admin(int id, const string& n, const string& e, const string& pwd)
        : User(id, n, e, "admin") {
        cout << "Создан администратор: " << name << endl;
    }
    
    void displayMenu() override {
        cout << "\n=== МЕНЮ АДМИНИСТРАТОРА ===" << endl;
        cout << "1. Добавить товар" << endl;
        cout << "2. Удалить товар" << endl;
        cout << "3. Обновить товар" << endl;
        cout << "4. Просмотреть все заказы" << endl;
        cout << "5. Просмотреть аудит" << endl;
        cout << "6. Одобрить заказ" << endl;
    }
    
    bool viewOrderStatus() override {
        cout << "\nВсе заказы в системе: " << orders.size() << endl;
        return true;
    }
    
    bool cancelOrder(int orderId) override {
        cout << "Заказ " << orderId << " отменён администратором" << endl;
        return true;
    }
    
    void addProduct(shared_ptr<Product> product) {
        if (product) {
            productCatalog.push_back(product);
            cout << "Товар добавлен: " << product->getName() << endl;
        }
    }
    
    void removeProduct(int productId) {
        auto it = find_if(productCatalog.begin(), productCatalog.end(),
            [productId](const shared_ptr<Product>& p) {
                return p->getProductId() == productId;
            });
        
        if (it != productCatalog.end()) {
            cout << "Товар удалён: " << (*it)->getName() << endl;
            productCatalog.erase(it);
        }
    }
    
    void updateProduct(int productId, double newPrice, int newQuantity) {
        auto it = find_if(productCatalog.begin(), productCatalog.end(),
            [productId](const shared_ptr<Product>& p) {
                return p->getProductId() == productId;
            });
        
        if (it != productCatalog.end()) {
            (*it)->setPrice(newPrice);
            (*it)->setQuantity(newQuantity);
            cout << "Товар обновлён: " << (*it)->getName() << endl;
        }
    }
    
    void viewAllOrders() {
        cout << "\nВсе заказы: " << orders.size() << endl;
        for (const auto& order : orders) {
            cout << "Заказ " << order->getOrderId() << " - Статус: " 
                 << order->getStatus() << endl;
        }
    }
    
    void viewAuditLog() {
        cout << "\n=== ЖУРНАЛ АУДИТА ===" << endl;
        cout << "Все операции в системе логируются автоматически" << endl;
    }
    
    void approveOrder(int orderId) {
        cout << "Заказ " << orderId << " одобрен администратором" << endl;
    }
    
    vector<shared_ptr<Product>>& getCatalog() {
        return productCatalog;
    }
};

#endif
