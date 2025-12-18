-- Удаляем таблицы
DROP TABLE IF EXISTS order_items;
DROP TABLE IF EXISTS orders;
DROP TABLE IF EXISTS products;


CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    price DOUBLE PRECISION NOT NULL
);

CREATE TABLE orders (
    order_id SERIAL PRIMARY KEY,
    order_date DATE NOT NULL
);

CREATE TABLE order_items (
    order_item_id SERIAL PRIMARY KEY,
    quantity INTEGER NOT NULL,
    total_price DOUBLE PRECISION NOT NULL,
	order_id INTEGER NOT NULL,
	product_id INTEGER NOT NULL,
	FOREIGN KEY (order_id) REFERENCES orders(order_id),
	FOREIGN KEY (product_id) REFERENCES products(id)
);

-- Создаем индексы
CREATE INDEX idx_order_date ON orders(order_date);
CREATE INDEX idx_product_id ON order_items(product_id);



















