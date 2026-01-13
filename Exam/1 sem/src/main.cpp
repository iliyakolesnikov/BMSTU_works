using namespace std;

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include "include/admin.h"
#include "include/manager.h"
#include "include/customer.h"
#include "include/product.h"
#include "include/payment_strategy.h"

int main() {
    cout << "=================================================\n";
    cout << "===   СИСТЕМА ИНТЕРНЕТ-МАГАЗИНА НА C++ ===\n";
    cout << "=================================================\n\n";
    
    // === ДЕМОНСТРАЦИЯ РАБОТЫ С РОЛЯМИ И ПОЛЬЗОВАТЕЛЯМИ ===
    cout << "=== СОЗДАНИЕ ПОЛЬЗОВАТЕЛЕЙ ===\n";
    
    auto admin = make_unique<Admin>(1, "Иван Петров", "admin@shop.com", "admin_pwd");
    auto manager = make_unique<Manager>(2, "Петр Сидоров", "manager@shop.com", "mgr_pwd");
    auto customer1 = make_unique<Customer>(3, "Александр Смирнов", "alex@mail.com", "cust_pwd");
    auto customer2 = make_unique<Customer>(4, "Мария Иванова", "maria@mail.com", "cust_pwd");
    
    // === ДЕМОНСТРАЦИЯ РАБОТЫ С ТОВАРАМИ ===
    cout << "\n=== УПРАВЛЕНИЕ ТОВАРАМИ ===\n";
    
    auto laptop = make_shared<Product>(1, "Ноутбук Dell", 50000.0, 10);
    auto mouse = make_shared<Product>(2, "Мышка Logitech", 1500.0, 50);
    auto keyboard = make_shared<Product>(3, "Клавиатура Keychron", 3000.0, 30);
    auto monitor = make_shared<Product>(4, "Монитор LG", 15000.0, 5);
    auto headphones = make_shared<Product>(5, "Наушники Sony", 8000.0, 20);
    
    admin->addProduct(laptop);
    admin->addProduct(mouse);
    admin->addProduct(keyboard);
    admin->addProduct(monitor);
    admin->addProduct(headphones);
    
    cout << "\n=== ТОВАРЫ В КАТАЛОГЕ ===\n";
    for (const auto& prod : admin->getCatalog()) {
        prod->displayInfo();
    }
    
    // === ДЕМОНСТРАЦИЯ СОЗДАНИЯ И УПРАВЛЕНИЯ ЗАКАЗАМИ ===
    cout << "\n=== РАБОТА ПОКУПАТЕЛЯ 1 ===\n";
    
    customer1->createNewOrder(101, "2025-01-13");
    customer1->addToOrder(laptop, 1);
    customer1->addToOrder(mouse, 2);
    customer1->addToOrder(keyboard, 1);
    
    auto order1 = customer1->viewMyOrders()[0];
    order1->displayItems();
    
    // === ДЕМОНСТРАЦИЯ РАЗЛИЧНЫХ МЕТОДОВ ОПЛАТЫ (ПАТТЕРН STRATEGY) ===
    cout << "\n=== ОПЛАТА ЗАКАЗА 101 (КАРТОЙ) ===\n";
    auto cardPayment = make_unique<CardPayment>("1234567890123456", "12/25", "123");
    customer1->makePayment(101, move(cardPayment));
    
    cout << "\n=== РАБОТА ПОКУПАТЕЛЯ 2 ===\n";
    
    customer2->createNewOrder(102, "2025-01-13");
    customer2->addToOrder(monitor, 1);
    customer2->addToOrder(headphones, 1);
    
    auto order2 = customer2->viewMyOrders()[0];
    order2->displayItems();
    
    cout << "\n=== ОПЛАТА ЗАКАЗА 102 (ЭЛЕКТРОННЫЙ КОШЕЛЁК) ===\n";
    auto ewalletPayment = make_unique<EWalletPayment>("wallet_123456");
    customer2->makePayment(102, move(ewalletPayment));
    
    // === ДЕМОНСТРАЦИЯ STL АЛГОРИТМОВ ===
    cout << "\n=== ДЕМОНСТРАЦИЯ STL АЛГОРИТМОВ ===\n";
    
    // Создаём вектор всех заказов
    vector<shared_ptr<Order>> allOrders;
    allOrders.push_back(order1);
    allOrders.push_back(order2);
    
    // find_if: найти первый завершённый заказ
    auto completedIt = find_if(allOrders.begin(), allOrders.end(),
        [](const shared_ptr<Order>& order) {
            return order->getStatus() == "completed";
        });
    
    if (completedIt != allOrders.end()) {
        cout << "Первый завершённый заказ: #" << (*completedIt)->getOrderId() << endl;
    }
    
    // copy_if: скопировать все завершённые заказы
    vector<shared_ptr<Order>> completedOrders;
    copy_if(allOrders.begin(), allOrders.end(), back_inserter(completedOrders),
        [](const shared_ptr<Order>& order) {
            return order->getStatus() == "completed";
        });
    cout << "Завершённых заказов: " << completedOrders.size() << endl;
    
    // accumulate: подсчитать общую сумму
    double totalAmount = accumulate(allOrders.begin(), allOrders.end(), 0.0,
        [](double sum, const shared_ptr<Order>& order) {
            return sum + order->getOrderTotal();
        });
    cout << "Общая сумма всех заказов: " << totalAmount << " руб." << endl;
    
    // === ДЕМОНСТРАЦИЯ УМНЫХ УКАЗАТЕЛЕЙ ===
    cout << "\n=== ИНФОРМАЦИЯ ОБ ИСПОЛЬЗУЕМЫХ УМНЫХ УКАЗАТЕЛЯХ ===\n";
    cout << "- unique_ptr<Payment>: используется в Order для исключительного владения" << endl;
    cout << "- shared_ptr<Order>: используется в User для совместного владения" << endl;
    cout << "- make_unique<> и make_shared<>: предпочтительные способы создания" << endl;
    cout << "- Нет new/delete операторов - полное управление памятью через RAII" << endl;
    
    // === ДЕМОНСТРАЦИЯ ФУНКЦИЙ ПОКУПАТЕЛЕЙ ===
    cout << "\n=== ИНФОРМАЦИЯ О ПОКУПАТЕЛЯХ ===\n";
    
    customer1->displayUserInfo();
    cout << "Потрачено: " << customer1->getTotalSpent() << " руб." << endl;
    
    customer2->displayUserInfo();
    cout << "Потрачено: " << customer2->getTotalSpent() << " руб." << endl;
    
    // === ДЕМОНСТРАЦИЯ МЕНЮ РОЛЕЙ ===
    cout << "\n=== МЕНЮ АДМИНИСТРАТОРА ===\n";
    admin->displayMenu();
    
    cout << "\n=== МЕНЮ МЕНЕДЖЕРА ===\n";
    manager->displayMenu();
    
    cout << "\n=== МЕНЮ ПОКУПАТЕЛЯ ===\n";
    customer1->displayMenu();
    
    // === ДЕМОНСТРАЦИЯ ОТСЛЕЖИВАНИЯ ЗАКАЗОВ ===
    cout << "\n=== ОТСЛЕЖИВАНИЕ ЗАКАЗА ===\n";
    customer1->trackOrder(101);
    
    cout << "\n=== ОТСЛЕЖИВАНИЕ ЗАКАЗА 2 ===\n";
    customer2->trackOrder(102);
    
    // === ДЕМОНСТРАЦИЯ ПРОСМОТРА ИНФОРМАЦИИ ===
    cout << "\n=== ПРОСМОТР ВСЕ ЗАКАЗОВ АДМИНИСТРАТОРОМ ===\n";
    admin->viewAllOrders();
    
    cout << "\n=== ПРОСМОТР ОЖИДАЮЩИХ ЗАКАЗОВ МЕНЕДЖЕРОМ ===\n";
    manager->viewOrderStatus();
    
    cout << "\n=================================================\n";
    cout << "===     СИСТЕМА РАБОТАЕТ КОРРЕКТНО!     ===\n";
    cout << "=================================================\n";
    
    return 0;
}
