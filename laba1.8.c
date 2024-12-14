#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Функция для определения минимального основания системы счисления
int determine_min_base(const char *number_str) {
    int max_digit = '0';  // Начинаем с цифры '0'
    
    // Проходим по всем символам числа
    for (int i = 0; number_str[i] != '\0'; i++) {
        char c = number_str[i];
        
        // Приводим к нижнему регистру
        c = tolower(c);
        
        if (isdigit(c)) {
            max_digit = (max_digit > c) ? max_digit : c;
        } else if (isalpha(c)) {
            max_digit = (max_digit > c) ? max_digit : c;
        }
    }

    // Если max_digit - цифра, то минимальное основание: 'max_digit' + 1
    if (isdigit(max_digit)) {
        return max_digit - '0' + 1;
    }
    // Если max_digit - буква, то минимальное основание: (char) - 'a' + 10 + 1
    else {
        return max_digit - 'a' + 10 + 1;
    }
}

// Функция для преобразования числа в десятичную систему счисления
long long convert_to_decimal(const char *number_str, int base) {
    long long decimal_value = 0;
    int power = 1;

    // Идем по числу с конца
    for (int i = strlen(number_str) - 1; i >= 0; i--) {
        char c = tolower(number_str[i]);
        
        int digit_value;
        if (isdigit(c)) {
            digit_value = c - '0';
        } else {
            digit_value = c - 'a' + 10;
        }

        decimal_value += digit_value * power;
        power *= base;
    }

    return decimal_value;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    char number_str[100];
    while (fscanf(input_file, "%s", number_str) != EOF) {
        // Определяем минимальное основание для текущего числа
        int min_base = determine_min_base(number_str);
        
        // Преобразуем число в десятичное представление
        long long decimal_value = convert_to_decimal(number_str, min_base);
        
        // Выводим результат в выходной файл
        fprintf(output_file, "%s %d %lld\n", number_str, min_base, decimal_value);
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
