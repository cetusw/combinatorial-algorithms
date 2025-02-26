#!/bin/bash

assert_equal() {
    if diff -q "$1" "$2" > /dev/null; then
        echo -e "\033[32mTest passed $i: $1 matches $2\033[0m"
    else
        echo -e "\033[31mTest failed $i: $1 does not match $2\033[0m"
        exit 1
    fi
}

#1 Минимальная команда (1 сотрудник)
i=1
echo "123
123
45" > ./test/input.txt
./cmake-build-debug/assignment-task ./test/input.txt > ./test/output.txt
echo -e "Наименьшая подгруппа:\n1 " > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#2 Невозможно создать команду
((i++))
echo "1234567
123
45" > ./test/input.txt
./cmake-build-debug/assignment-task ./test/input.txt > ./test/output.txt
echo "Невозможно создать команду со всеми необходимыми навыками" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#3 Команда из двух сотрудников
((i++))
echo "1234
12
23
34" > ./test/input.txt
./cmake-build-debug/assignment-task ./test/input.txt > ./test/output.txt
echo -e "Наименьшая подгруппа:\n1 3 " > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#4 Один сотрудник покрывает всё
((i++))
echo "12345
12345
12" > ./test/input.txt
./cmake-build-debug/assignment-task ./test/input.txt > ./test/output.txt
echo -e "Наименьшая подгруппа:\n1 " > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#5 Некорректное количество аргументов
((i++))
./cmake-build-debug/assignment-task > ./test/output.txt
echo "Неверное количество аргументов" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#6 Пустой входной файл
((i++))
echo "" > ./test/input.txt
./cmake-build-debug/assignment-task ./test/input.txt > ./test/output.txt
echo "Невозможно создать команду со всеми необходимыми навыками" > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

#7 Перекрывающиеся навыки
((i++))
echo "123
12
23
13" > ./test/input.txt
./cmake-build-debug/assignment-task ./test/input.txt > ./test/output.txt
echo -e "Наименьшая подгруппа:\n1 2 " > ./test/expected.txt
assert_equal ./test/output.txt ./test/expected.txt

echo -e "\033[32mAll tests passed!\033[0m"