using namespace std;

#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <pqxx/pqxx>
#include <iostream>
#include <memory>
#include <string>

template<typename T>
class DatabaseConnection {
private:
    unique_ptr<pqxx::connection> conn;
    string connectionString;
    
public:
    DatabaseConnection(const string& connStr) : connectionString(connStr) {
        try {
            conn = make_unique<pqxx::connection>(connectionString);
            if (!conn->is_open()) {
                throw runtime_error("Ошибка: БД не открыта");
            }
            cout << "Подключение к БД успешно" << endl;
        } catch (const exception& e) {
            cerr << "Ошибка подключения: " << e.what() << endl;
            throw;
        }
    }
    
    ~DatabaseConnection() {
        if (conn && conn->is_open()) {
            conn->disconnect();
        }
    }
    
    bool executeQuery(const string& query) {
        try {
            pqxx::work txn(*conn);
            pqxx::result res = txn.exec(query);
            txn.commit();
            return true;
        } catch (const exception& e) {
            cerr << "Ошибка выполнения запроса: " << e.what() << endl;
            return false;
        }
    }
    
    bool executeNonQuery(const string& query) {
        try {
            pqxx::work txn(*conn);
            txn.exec(query);
            txn.commit();
            return true;
        } catch (const exception& e) {
            cerr << "Ошибка выполнения: " << e.what() << endl;
            return false;
        }
    }
    
    pqxx::result executeSelect(const string& query) {
        pqxx::work txn(*conn);
        pqxx::result res = txn.exec(query);
        txn.commit();
        return res;
    }
    
    bool beginTransaction() {
        try {
            cout << "Транзакция начата" << endl;
            return true;
        } catch (const exception& e) {
            cerr << "Ошибка начала транзакции: " << e.what() << endl;
            return false;
        }
    }
    
    bool commit() {
        try {
            cout << "Транзакция завершена" << endl;
            return true;
        } catch (const exception& e) {
            cerr << "Ошибка фиксации: " << e.what() << endl;
            return false;
        }
    }
    
    bool rollback() {
        try {
            cout << "Транзакция отменена" << endl;
            return true;
        } catch (const exception& e) {
            cerr << "Ошибка отката: " << e.what() << endl;
            return false;
        }
    }
    
    bool isConnected() const {
        return conn && conn->is_open();
    }
};

#endif
