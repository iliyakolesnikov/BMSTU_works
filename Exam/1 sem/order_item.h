using namespace std;

#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

#include <string>
#include <iostream>

class OrderItem {
private:
    int orderItemId;
    int productId;
    string productName;
    int quantity;
    double unitPrice;
    
public:
    OrderItem(int id, int prodId, const string& name, int qty, double price)
        : orderItemId(id), productId(prodId), productName(name), 
          quantity(qty), unitPrice(price) {}
    
    int getOrderItemId() const { return orderItemId; }
    int getProductId() const { return productId; }
    string getProductName() const { return productName; }
    int getQuantity() const { return quantity; }
    double getUnitPrice() const { return unitPrice; }
    
    void setQuantity(int qty) {
        if (qty <= 0) {
            cerr << "Ошибка: количество должно быть больше 0" << endl;
            return;
        }
        quantity = qty;
    }
    
    double getTotal() const {
        return quantity * unitPrice;
    }
    
    bool validateQuantity(int availableQuantity) const {
        return quantity <= availableQuantity && quantity > 0;
    }
};

#endif
