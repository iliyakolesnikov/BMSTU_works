--CREATE DATABASE order_management;

CREATE TABLE products (
    id      SERIAL PRIMARY KEY,
    name    VARCHAR(100) NOT NULL,
    price   NUMERIC(10,2) NOT NULL
);

CREATE TABLE orders (
    order_id    SERIAL PRIMARY KEY,
    order_date  DATE NOT NULL
);

CREATE TABLE order_items (
    order_item_id   SERIAL PRIMARY KEY,
    order_id        INTEGER NOT NULL,
    product_id      INTEGER NOT NULL,
    quantity        INTEGER NOT NULL,
    total_price     NUMERIC(10,2) NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (product_id) REFERENCES products(id)
);


INSERT INTO products (name, price) VALUES
    ('Телефон', 50000.00),
    ('Ноутбук', 150000.00),
    ('Наушники', 5000.00);

INSERT INTO orders (order_date) VALUES
	('20.11.25'),
    ('21.11.25');

INSERT INTO order_items (order_id, product_id, quantity, total_price) VALUES
    (1, 1, 2, 100000.00),  -- 2 телефона
    (2, 3, 4, 20000.00),   -- 4 наушники
    (1, 2, 5, 750000.00),  -- 5 ноутбуков
	(2, 1, 20, 1000000.00);  -- 20 телефонов


--5.1
SELECT id, name, price FROM products;

-- 5.2. Все позиции заказа по определенному заказу
SELECT oi.order_item_id, oi.order_id, p.name, oi.quantity, oi.total_price
FROM order_items oi
JOIN products p ON oi.product_id = p.id
WHERE oi.order_id = 1;

-- 5.3. Общая стоимость всех товаров в конкретном заказе
SELECT oi.order_id, SUM(oi.total_price) AS order_total
FROM order_items oi
WHERE oi.order_id = 2
GROUP BY oi.order_id;

-- 5.4. Список всех заказов за определенный период с общей суммой
SELECT o.order_id, o.order_date, SUM(oi.total_price) AS order_total
FROM orders o
JOIN order_items oi ON o.order_id = oi.order_id
WHERE o.order_date  = '2025-11-21' 
GROUP BY o.order_id, o.order_date
ORDER BY o.order_date;


-- по желанию
SELECT p.id, p.name, SUM(oi.quantity) AS total_quantity
FROM order_items oi
JOIN orders o ON oi.order_id = o.order_id
JOIN products p ON oi.product_id = p.id
WHERE o.order_date = '2025-11-20'
GROUP BY p.id, p.name
ORDER BY total_quantity DESC;

UPDATE products
SET price = 77000.00
WHERE id = 1;

DELETE FROM order_items
WHERE order_item_id = 3;





