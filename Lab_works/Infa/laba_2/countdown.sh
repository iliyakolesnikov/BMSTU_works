#!/bin/bash

echo "Введите число для обратного отсчета:"
read number
echo "Начинаем обратный отсчет от $number до 1:"
for (( i=$number; i>=1; i--))
do
    echo $i
done
echo "Готово!"

