#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Определение подынтегральных функций
double integrand_a(double x) {
    return log(1 + x) / x;
}

double integrand_b(double x) {
    return exp(-x * x) / 2.0;
}

double integrand_c(double x) {
    return log(1 / (1 - x));
}

double integrand_d(double x) {
    return x;
}

// Метод трапеций для численного интегрирования
double trapezoidal_rule(double (*f)(double), double a, double b, double epsilon) {
    int n = 1;
    double h, integral, integral_prev;

    // Начальные значения
    h = b - a;
    integral = h * (f(a) + f(b)) / 2.0;
    
    do {
        integral_prev = integral;
        n *= 2;
        h /= 2;
        integral = 0.0;
        
        // Разбиение на n отрезков
        for (int i = 1; i < n; i += 2) {
            integral += f(a + i * h);
        }
        
        integral = (integral_prev + h * integral) / 2.0;
        
    } while (fabs(integral - integral_prev) > epsilon);  // Остановка по точности
    
    return integral;
}

int main() {
    double epsilon;

    // Запрос значения epsilon у пользователя
    printf("Enter the accuracy of epsilon: ");
    if (scanf("%lf", &epsilon) != 1) {
        printf("Input error! Invalid format.\n");
        return 1;
    }

    // Проверка на допустимость значения epsilon
    if (epsilon <= 0) {
        printf("Error: epsilon must be a positive number.\n");
        return 1;
    }

    // Вычисление интегралов
    double result_a = trapezoidal_rule(integrand_a, 0.0, 1.0, epsilon);
    double result_b = trapezoidal_rule(integrand_b, 0.0, 1.0, epsilon);
    double result_c = trapezoidal_rule(integrand_c, 0.0, 1.0, epsilon);
    double result_d = trapezoidal_rule(integrand_d, 0.0, 1.0, epsilon);
    
    // Вывод результатов
    printf("The result of the integral (a): %.12f\n", result_a);
    printf("The result of the integral (b): %.12f\n", result_b);
    printf("The result of the integral (c): %.12f\n", result_c);
    printf("The result of the integral (d): %.12f\n", result_d);

    return 0;
}
