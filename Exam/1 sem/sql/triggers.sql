-- Триггер: логирование создания заказа
CREATE OR REPLACE FUNCTION log_order_create()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log (user_id, operation, table_name, record_id, details)
    VALUES (NEW.user_id, 'CREATE', 'orders', NEW.order_id, 
            'Order created with total amount: ' || NEW.total_amount);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_order_create
AFTER INSERT ON orders
FOR EACH ROW
EXECUTE FUNCTION log_order_create();

-- Триггер: логирование изменения статуса заказа
CREATE OR REPLACE FUNCTION log_status_change()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.status IS DISTINCT FROM NEW.status THEN
        INSERT INTO order_status_history (order_id, old_status, new_status)
        VALUES (NEW.order_id, OLD.status, NEW.status);
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_order_status_change
AFTER UPDATE OF status ON orders
FOR EACH ROW
EXECUTE FUNCTION log_status_change();

-- Триггер: логирование удаления товара
CREATE OR REPLACE FUNCTION log_product_delete()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log (operation, table_name, record_id, details)
    VALUES ('DELETE', 'products', OLD.product_id, 
            'Product deleted: ' || OLD.name || ' (' || OLD.price || ')');
    RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_product_delete
BEFORE DELETE ON products
FOR EACH ROW
EXECUTE FUNCTION log_product_delete();

-- Триггер: логирование добавления товара
CREATE OR REPLACE FUNCTION log_product_create()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO audit_log (operation, table_name, record_id, details)
    VALUES ('CREATE', 'products', NEW.product_id, 
            'Product created: ' || NEW.name || ' (' || NEW.price || ')');
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_product_create
AFTER INSERT ON products
FOR EACH ROW
EXECUTE FUNCTION log_product_create();

-- Триггер: проверка количества товара перед добавлением в заказ
CREATE OR REPLACE FUNCTION check_product_quantity()
RETURNS TRIGGER AS $$
DECLARE
    v_available_qty INT;
BEGIN
    SELECT quantity_in_stock INTO v_available_qty
    FROM products WHERE product_id = NEW.product_id;
    
    IF v_available_qty < NEW.quantity THEN
        RAISE EXCEPTION 'Not enough products in stock. Available: %', v_available_qty;
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_check_product_quantity
BEFORE INSERT ON order_items
FOR EACH ROW
EXECUTE FUNCTION check_product_quantity();

\echo 'Все триггеры успешно созданы!'
