using namespace std;

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "order.h"
#include "product.h"
#include "payment_strategy.h"
#include <algorithm>
#include <numeric>

class Customer : public User {
private:
    vector<shared_ptr<Product>> availableProducts;
    shared_ptr<Order> currentOrder;
    
public:
    Customer(int id, const string& n, const string& e, const string& pwd)
        : User(id, n, e, "customer") {
        cout << "Создан покупатель: " << name << endl;
    }
    
    void displayMenu() override {
        cout << "\n=== МЕНЮ ПОКУПАТЕЛЯ ===" << endl;
        cout << "1. Создать новый заказ" << endl;
        cout << "2. Добавить товар в заказ" << endl;
        cout << "3. Просмотреть свои заказы" << endl;
        cout << "4. Оплатить заказ" << endl;
        cout << "5. Вернуть товар" << endl;
        cout << "6. Отследить заказ" << endl;
    }
    
    bool viewOrderStatus() override {
        cout << "\nВаши заказы (" << orders.size() << "):" << endl;
        for (const auto& order : orders) {
            cout << "  Заказ " << order->getOrderId() << " - " 
                 << order->getStatus() << " - " << order->getOrderTotal() 
                 << " руб." << endl;
        }
        return true;
    }
    
    bool cancelOrder(int orderId) override {
        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const shared_ptr<Order>& order) {
                return order->getOrderId() == orderId;
            });
        
        if (it != orders.end()) {
            (*it)->updateStatus("cancelled");
            cout << "Ваш заказ " << orderId << " отменён" << endl;
            return true;
        }
        return false;
    }
    
    void createNewOrder(int orderId, const string& orderDate) {
        currentOrder = make_shared<Order>(orderId, userId, orderDate);
        orders.push_back(currentOrder);
        cout << "Создан новый заказ #" << orderId << endl;
    }
    
    void addToOrder(shared_ptr<Product> product, int quantity) {
        if (!currentOrder) {
            cerr << "Ошибка: сначала создайте заказ" << endl;
            return;
        }
        
        if (product && product->getQuantity() >= quantity) {
            OrderItem item(0, product->getProductId(), product->getName(), 
                          quantity, product->getPrice());
            currentOrder->addItem(item);
            product->decreaseQuantity(quantity);
            cout << "Товар добавлен в заказ: " << product->getName() << endl;
        } else {
            cerr << "Ошибка: товар недоступен" << endl;
        }
    }
    
    void removeFromOrder(int productId) {
        if (currentOrder) {
            currentOrder->removeItem(productId);
            cout << "Товар удалён из заказа" << endl;
        }
    }
    
    void makePayment(int orderId, unique_ptr<PaymentStrategy> paymentMethod) {
        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const shared_ptr<Order>& order) {
                return order->getOrderId() == orderId;
            });
        
        if (it != orders.end()) {
            auto payment = make_unique<Payment>(orderId, (*it)->getOrderTotal());
            payment->setPaymentStrategy(move(paymentMethod));
            
            (*it)->setPayment(move(payment));
            
            if ((*it)->processPayment()) {
                (*it)->updateStatus("completed");
                cout << "Платёж успешно обработан!" << endl;
            }
        }
    }
    
    bool returnProduct(int orderId, int productId) {
        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const shared_ptr<Order>& order) {
                return order->getOrderId() == orderId;
            });
        
        if (it != orders.end() && (*it)->canReturn()) {
            (*it)->removeItem(productId);
            (*it)->updateStatus("returned");
            cout << "Товар успешно возвращен" << endl;
            return true;
        }
        return false;
    }
    
    vector<shared_ptr<Order>> viewMyOrders() {
        return orders;
    }
    
    void trackOrder(int orderId) {
        auto it = find_if(orders.begin(), orders.end(),
            [orderId](const shared_ptr<Order>& order) {
                return order->getOrderId() == orderId;
            });
        
        if (it != orders.end()) {
            cout << "\nОтслеживание заказа #" << orderId << endl;
            cout << "Дата: " << (*it)->getOrderDate() << endl;
            cout << "Статус: " << (*it)->getStatus() << endl;
            cout << "Сумма: " << (*it)->getOrderTotal() << " руб." << endl;
            (*it)->displayItems();
        }
    }
    
    void setAvailableProducts(const vector<shared_ptr<Product>>& products) {
        availableProducts = products;
    }
    
    double getTotalSpent() const {
        return accumulate(orders.begin(), orders.end(), 0.0,
            [](double sum, const shared_ptr<Order>& order) {
                if (order->getStatus() == "completed") {
                    return sum + order->getOrderTotal();
                }
                return sum;
            });
    }
};

#endif
