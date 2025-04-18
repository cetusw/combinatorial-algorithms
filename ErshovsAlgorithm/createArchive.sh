#!/bin/bash

# Удаляем существующий файл архива
output="program.txt"
rm -f "$output"

# Рекурсивно обрабатываем файлы, исключая указанные папки
find . -type d \( -name 'cmake-build-debug' -o -name '.idea' \) -prune -o -type f -print | while read -r file; do
    # Получаем относительный путь (убираем ./ в начале)
    rel_path="${file#./}"

    # Записываем разделитель с путем
    echo "<<<FILE>>>$rel_path" >> "$output"
    # Добавляем содержимое файла
    cat "$file" >> "$output"
    # Записываем конечный разделитель
    echo "<<<END>>>" >> "$output"
done

echo "Архив проекта создан в файле $output."