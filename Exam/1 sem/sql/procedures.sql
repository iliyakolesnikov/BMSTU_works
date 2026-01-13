-- Процедура: создать новый заказ
CREATE OR REPLACE PROCEDURE createOrder(
    p_user_id INT,
    p_order_date DATE
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_order_id INT;
BEGIN
    INSERT INTO orders (user_id, order_date, status, total_amount)
    VALUES (p_user_id, p_order_date, 'pending', 0)
    RETURNING order_id INTO v_order_id;
    
    INSERT INTO audit_log (user_id, operation, table_name, record_id, details)
    VALUES (p_user_id, 'CREATE', 'orders', v_order_id, 'New order created');
    
    RAISE NOTICE 'Order % created successfully', v_order_id;
END;
$$;

-- Процедура: добавить товар в заказ
CREATE OR REPLACE PROCEDURE addItemToOrder(
    p_order_id INT,
    p_product_id INT,
    p_quantity INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_product_price NUMERIC;
    v_user_id INT;
BEGIN
    -- Получить цену товара
    SELECT price INTO v_product_price FROM products WHERE product_id = p_product_id;
    
    -- Получить ID пользователя заказа
    SELECT user_id INTO v_user_id FROM orders WHERE order_id = p_order_id;
    
    -- Вставить элемент заказа
    INSERT INTO order_items (order_id, product_id, quantity, unit_price)
    VALUES (p_order_id, p_product_id, p_quantity, v_product_price);
    
    -- Обновить общую сумму заказа
    UPDATE orders
    SET total_amount = total_amount + (p_quantity * v_product_price)
    WHERE order_id = p_order_id;
    
    -- Уменьшить количество товара на складе
    UPDATE products
    SET quantity_in_stock = quantity_in_stock - p_quantity
    WHERE product_id = p_product_id;
    
    -- Логирование
    INSERT INTO audit_log (user_id, operation, table_name, record_id, details)
    VALUES (v_user_id, 'ADD_ITEM', 'order_items', p_order_id, 'Item added to order');
    
    RAISE NOTICE 'Item added to order %', p_order_id;
END;
$$;

-- Процедура: обновить статус заказа
CREATE OR REPLACE PROCEDURE updateOrderStatus(
    p_order_id INT,
    p_new_status VARCHAR
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_old_status VARCHAR;
    v_user_id INT;
BEGIN
    -- Получить старый статус
    SELECT status, user_id INTO v_old_status, v_user_id
    FROM orders WHERE order_id = p_order_id;
    
    -- Обновить статус
    UPDATE orders SET status = p_new_status WHERE order_id = p_order_id;
    
    -- Сохранить историю статуса
    INSERT INTO order_status_history (order_id, old_status, new_status, changed_by)
    VALUES (p_order_id, v_old_status, p_new_status, v_user_id);
    
    -- Логирование
    INSERT INTO audit_log (user_id, operation, table_name, record_id, details)
    VALUES (v_user_id, 'UPDATE_STATUS', 'orders', p_order_id, 
            'Status changed from ' || v_old_status || ' to ' || p_new_status);
    
    RAISE NOTICE 'Order % status updated to %', p_order_id, p_new_status;
END;
$$;

-- Процедура: отменить заказ
CREATE OR REPLACE PROCEDURE cancelOrder(p_order_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_user_id INT;
BEGIN
    SELECT user_id INTO v_user_id FROM orders WHERE order_id = p_order_id;
    
    UPDATE orders SET status = 'cancelled' WHERE order_id = p_order_id;
    
    INSERT INTO audit_log (user_id, operation, table_name, record_id, details)
    VALUES (v_user_id, 'CANCEL', 'orders', p_order_id, 'Order cancelled');
    
    RAISE NOTICE 'Order % cancelled', p_order_id;
END;
$$;

-- Процедура: вернуть товар
CREATE OR REPLACE PROCEDURE returnOrder(p_order_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    v_user_id INT;
    v_days_since INT;
BEGIN
    SELECT user_id, EXTRACT(DAY FROM (CURRENT_DATE - order_date))::INT
    INTO v_user_id, v_days_since
    FROM orders WHERE order_id = p_order_id;
    
    IF v_days_since > 30 THEN
        RAISE EXCEPTION 'Order cannot be returned after 30 days';
    END IF;
    
    UPDATE orders SET status = 'returned' WHERE order_id = p_order_id;
    
    INSERT INTO audit_log (user_id, operation, table_name, record_id, details)
    VALUES (v_user_id, 'RETURN', 'orders', p_order_id, 
            'Order returned within 30 days');
    
    RAISE NOTICE 'Order % returned successfully', p_order_id;
END;
$$;

-- Процедура: удалить товар из заказа
CREATE OR REPLACE PROCEDURE removeItemFromOrder(
    p_order_id INT,
    p_product_id INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_quantity INT;
    v_unit_price NUMERIC;
    v_user_id INT;
BEGIN
    -- Получить количество и цену товара
    SELECT oi.quantity, oi.unit_price, o.user_id
    INTO v_quantity, v_unit_price, v_user_id
    FROM order_items oi
    JOIN orders o ON oi.order_id = o.order_id
    WHERE oi.order_id = p_order_id AND oi.product_id = p_product_id;
    
    -- Удалить товар
    DELETE FROM order_items
    WHERE order_id = p_order_id AND product_id = p_product_id;
    
    -- Обновить сумму заказа
    UPDATE orders
    SET total_amount = total_amount - (v_quantity * v_unit_price)
    WHERE order_id = p_order_id;
    
    -- Вернуть товар на склад
    UPDATE products
    SET quantity_in_stock = quantity_in_stock + v_quantity
    WHERE product_id = p_product_id;
    
    -- Логирование
    INSERT INTO audit_log (user_id, operation, table_name, record_id, details)
    VALUES (v_user_id, 'REMOVE_ITEM', 'order_items', p_order_id, 
            'Item removed from order');
    
    RAISE NOTICE 'Item removed from order %', p_order_id;
END;
$$;

-- Процедура: обновить товар
CREATE OR REPLACE PROCEDURE updateProduct(
    p_product_id INT,
    p_price NUMERIC,
    p_quantity INT
)
LANGUAGE plpgsql
AS $$
BEGIN
    UPDATE products
    SET price = p_price, quantity_in_stock = p_quantity
    WHERE product_id = p_product_id;
    
    INSERT INTO audit_log (operation, table_name, record_id, details)
    VALUES ('UPDATE', 'products', p_product_id, 
            'Product updated: price=' || p_price || ', quantity=' || p_quantity);
    
    RAISE NOTICE 'Product % updated', p_product_id;
END;
$$;

\echo 'Все процедуры успешно созданы!'
