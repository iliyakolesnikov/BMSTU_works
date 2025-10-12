#!/bin/bash

echo "Сервер с подтверждением запущен на порту 12345"

while true; do
    # Читаем сообщение и отправляем подтверждение
    message=$(nc -l -p 12345 -q 0)
    timestamp=$(date '+%Y-%m-%d %H:%M:%S')
    
    echo "[$timestamp] Получено сообщение: $message"
    
    # Отправляем подтверждение клиенту
    echo "OK: Сообщение получено сервером в $timestamp" | nc localhost 12346 2>/dev/null &
done
