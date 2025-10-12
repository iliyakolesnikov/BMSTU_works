#!/bin/bash

# Проверяем, что передан аргумент с именем процесса
if [ $# -ne 1 ]; then
    echo "Пожалуйста, укажите имя процесса"
    echo "Использование: $0 <имя_процесса>"
    exit 1
fi
process_name=$1
# Проверяем, запущен ли процесс с помощью pgrep
if pgrep "$process_name" > /dev/null; then
    echo "Процесс '$process_name' запущен"
else
    echo "Процесс '$process_name' не найден"
fi
