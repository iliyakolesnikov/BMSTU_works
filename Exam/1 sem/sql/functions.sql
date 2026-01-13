-- Функция: получить статус заказа
CREATE OR REPLACE FUNCTION getOrderStatus(p_order_id INT)
RETURNS VARCHAR AS $$
BEGIN
    RETURN (SELECT status FROM orders WHERE order_id = p_order_id);
END;
$$ LANGUAGE plpgsql;

-- Функция: получить общее потраченное пользователем
CREATE OR REPLACE FUNCTION getTotalSpentByUser(p_user_id INT)
RETURNS NUMERIC AS $$
BEGIN
    RETURN (
        SELECT COALESCE(SUM(total_amount), 0)
        FROM orders
        WHERE user_id = p_user_id AND status = 'completed'
    );
END;
$$ LANGUAGE plpgsql;

-- Функция: получить количество заказов пользователя
CREATE OR REPLACE FUNCTION getUserOrderCount(p_user_id INT)
RETURNS INT AS $$
BEGIN
    RETURN (SELECT COUNT(*) FROM orders WHERE user_id = p_user_id);
END;
$$ LANGUAGE plpgsql;

-- Функция: получить количество завершённых заказов
CREATE OR REPLACE FUNCTION getCompletedOrderCount(p_user_id INT)
RETURNS INT AS $$
BEGIN
    RETURN (SELECT COUNT(*) FROM orders WHERE user_id = p_user_id AND status = 'completed');
END;
$$ LANGUAGE plpgsql;

-- Функция: проверить можно ли вернуть товар (не более 30 дней)
CREATE OR REPLACE FUNCTION canReturnOrder(p_order_id INT)
RETURNS BOOLEAN AS $$
BEGIN
    RETURN (
        SELECT (CURRENT_DATE - order_date) <= 30
        FROM orders
        WHERE order_id = p_order_id AND status = 'completed'
    );
END;
$$ LANGUAGE plpgsql;

-- Функция: получить дни с момента заказа
CREATE OR REPLACE FUNCTION getDaysSinceOrder(p_order_id INT)
RETURNS INT AS $$
BEGIN
    RETURN (
        SELECT EXTRACT(DAY FROM (CURRENT_DATE - order_date))::INT
        FROM orders
        WHERE order_id = p_order_id
    );
END;
$$ LANGUAGE plpgsql;

-- Функция: получить товары в заказе
CREATE OR REPLACE FUNCTION getOrderItems(p_order_id INT)
RETURNS TABLE (product_name VARCHAR, quantity INT, unit_price NUMERIC, total NUMERIC) AS $$
BEGIN
    RETURN QUERY
    SELECT p.name, oi.quantity, oi.unit_price, (oi.quantity * oi.unit_price)
    FROM order_items oi
    JOIN products p ON oi.product_id = p.product_id
    WHERE oi.order_id = p_order_id;
END;
$$ LANGUAGE plpgsql;

-- Функция: получить популярные товары
CREATE OR REPLACE FUNCTION getPopularProducts(p_limit INT DEFAULT 5)
RETURNS TABLE (product_id INT, product_name VARCHAR, purchase_count BIGINT) AS $$
BEGIN
    RETURN QUERY
    SELECT p.product_id, p.name, COUNT(oi.order_item_id)::BIGINT
    FROM products p
    LEFT JOIN order_items oi ON p.product_id = oi.product_id
    GROUP BY p.product_id, p.name
    ORDER BY COUNT(oi.order_item_id) DESC
    LIMIT p_limit;
END;
$$ LANGUAGE plpgsql;

-- Функция: получить логи аудита пользователя
CREATE OR REPLACE FUNCTION getAuditLogByUser(p_user_id INT)
RETURNS TABLE (log_id INT, operation VARCHAR, table_name VARCHAR, record_id INT, created_at TIMESTAMP) AS $$
BEGIN
    RETURN QUERY
    SELECT al.log_id, al.operation, al.table_name, al.record_id, al.created_at
    FROM audit_log al
    WHERE al.user_id = p_user_id
    ORDER BY al.created_at DESC;
END;
$$ LANGUAGE plpgsql;

-- Функция: получить историю статусов заказа
CREATE OR REPLACE FUNCTION getOrderStatusHistory(p_order_id INT)
RETURNS TABLE (old_status VARCHAR, new_status VARCHAR, changed_at TIMESTAMP) AS $$
BEGIN
    RETURN QUERY
    SELECT osh.old_status, osh.new_status, osh.changed_at
    FROM order_status_history osh
    WHERE osh.order_id = p_order_id
    ORDER BY osh.changed_at DESC;
END;
$$ LANGUAGE plpgsql;

-- Функция: сгенерировать отчёт по заказам
CREATE OR REPLACE FUNCTION generateOrderReport()
RETURNS TABLE (order_id INT, user_name VARCHAR, order_date DATE, status VARCHAR, total NUMERIC) AS $$
BEGIN
    RETURN QUERY
    SELECT o.order_id, u.name, o.order_date, o.status, o.total_amount
    FROM orders o
    JOIN users u ON o.user_id = u.user_id
    ORDER BY o.order_date DESC;
END;
$$ LANGUAGE plpgsql;

-- Функция: получить доход по дням
CREATE OR REPLACE FUNCTION getRevenueByDay(p_start_date DATE, p_end_date DATE)
RETURNS TABLE (order_date DATE, total_revenue NUMERIC, order_count INT) AS $$
BEGIN
    RETURN QUERY
    SELECT o.order_date, SUM(o.total_amount), COUNT(o.order_id)::INT
    FROM orders o
    WHERE o.status = 'completed' AND o.order_date BETWEEN p_start_date AND p_end_date
    GROUP BY o.order_date
    ORDER BY o.order_date DESC;
END;
$$ LANGUAGE plpgsql;

\echo 'Все функции успешно созданы!'
