using namespace std;

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product {
private:
    int productId;
    string name;
    double price;
    int quantityInStock;
    
public:
    Product(int id, const string& n, double p, int qty)
        : productId(id), name(n), price(p), quantityInStock(qty) {}
    
    int getProductId() const { return productId; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantityInStock; }
    
    void setPrice(double newPrice) {
        if (newPrice <= 0) {
            cerr << "Ошибка: цена должна быть больше 0" << endl;
            return;
        }
        price = newPrice;
    }
    
    void setQuantity(int newQuantity) {
        if (newQuantity < 0) {
            cerr << "Ошибка: количество не может быть отрицательным" << endl;
            return;
        }
        quantityInStock = newQuantity;
    }
    
    bool isAvailable() const {
        return quantityInStock > 0;
    }
    
    bool decreaseQuantity(int amount) {
        if (amount <= 0 || amount > quantityInStock) {
            cerr << "Ошибка: невозможно уменьшить количество" << endl;
            return false;
        }
        quantityInStock -= amount;
        return true;
    }
    
    void increaseQuantity(int amount) {
        if (amount <= 0) {
            cerr << "Ошибка: количество должно быть больше 0" << endl;
            return;
        }
        quantityInStock += amount;
    }
    
    void displayInfo() const {
        cout << "ID: " << productId << " | " << name << " | " 
             << price << " руб. | Кол-во: " << quantityInStock << endl;
    }
};

#endif
