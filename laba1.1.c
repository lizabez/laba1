#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функция для проверки простоты числа
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Функция для вычисления факториала
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Функция для вывода чисел от 1 до 100, кратных x
void print_multiples(int x) {
    int found = 0;
    for (int i = 1; i <= 100; i++) {
        if (i % x == 0) {
            printf("%d ", i);
            found = 1;
        }
    }
    if (!found) {
        printf("There are no numbers that are multiples of %d, ranging from 1 to 100.\n", x);
    } else {
        printf("\n");
    }
}

// Функция для проверки простоты числа x
void check_prime(int x) {
    if (is_prime(x)) {
        printf("%d - a prime number. (prost)\n", x);
    } else {
        printf("%d - a composite number.\n", x);
    }
}

// Функция для вывода числа x в шестнадцатеричном формате
void print_hex_digits(int x) {
    printf("The digits of the number %d in the hexadecimal system: ", x);
    if (x == 0) {
        printf("0\n");
    } else {
        char hex[20];
        sprintf(hex, "%X", x); // Переводим в шестнадцатеричную строку
        for (int i = 0; hex[i] != '\0'; i++) {
            printf("%c ", hex[i]);
        }
        printf("\n");
    }
}

// Функция для вывода таблицы степеней для чисел от 1 до 10 с показателями от 1 до x
void print_powers_table(int x) {
    if (x > 10) {
        printf("Error: for the -e flag, the number x must be no more than 10.\n");
        return;
    }

    for (int base = 1; base <= 10; base++) {
        for (int exp = 1; exp <= x; exp++) {
            printf("%d^%d = %d\t", base, exp, (int)pow(base, exp));
        }
        printf("\n");
    }
}

// Функция для вычисления суммы всех чисел от 1 до x
void sum_numbers(int x) {
    int sum = 0;
    for (int i = 1; i <= x; i++) {
        sum += i;
    }
    printf("The sum of all natural numbers from 1 to %d = %d\n", x, sum);
}

// Функция для вычисления факториала числа x
void print_factorial(int x) {
    if (x < 0) {
        printf("Error: The factorial of a negative number does not exist.\n");
    } else {
        unsigned long long fact = factorial(x);
        printf("%d! = %llu\n", x, fact);
    }
}

// Главная функция
int main() {
    int x;
    char flag[3];

    // Запрашиваем ввод числа x
    printf("Enter a natural number x: ");
    scanf("%d", &x);

    if (x <= 0) {
        printf("Mistake: x must be a natural number.\n");
        return 1;
    }

    // Запрашиваем ввод флага
    printf("Enter the flag (-h, -p, -s, -e, -a, -f): ");
    scanf("%s", flag);

    // В зависимости от флага выполняем нужную операцию
    if (flag[0] == '-' || flag[0] == '/') {
        switch (flag[1]) {
            case 'h':
                print_multiples(x);
                break;
            case 'p':
                check_prime(x);
                break;
            case 's':
                print_hex_digits(x);
                break;
            case 'e':
                print_powers_table(x);
                break;
            case 'a':
                sum_numbers(x);
                break;
            case 'f':
                print_factorial(x);
                break;
            default:
                printf("Error: Unknown flag '%s'.\n", flag);
                return 1;
        }
    } else {
        printf("Error: The flag must start with the character '-' or '/'.\n");
        return 1;
    }

    return 0;
}
