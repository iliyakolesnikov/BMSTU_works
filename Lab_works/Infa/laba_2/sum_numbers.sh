#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Пожалуйста, укажите два числа"
    exit 1
fi
num1=$1
num2=$2
sum=$(( num1 + num2 ))
echo "Сумма чисел $num1 и $num2 равна: $sum"
