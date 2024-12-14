#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array(int *arr, int size, int a, int b) {
    // Заполняем массив случайными числами в диапазоне [a..b]
    for (int i = 0; i < size; i++) {
        arr[i] = a + rand() % (b - a + 1);
    }
}

void swap_min_max(int *arr, int size) {
    if (size == 0) return;

    int min_idx = 0, max_idx = 0;

    // Находим индексы минимального и максимального элемента
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[min_idx]) {
            min_idx = i;
        }
        if (arr[i] > arr[max_idx]) {
            max_idx = i;
        }
    }

    // Меняем местами минимальный и максимальный элементы
    int temp = arr[min_idx];
    arr[min_idx] = arr[max_idx];
    arr[max_idx] = temp;
}

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size, a, b;

    // Ввод данных с клавиатуры
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    printf("Enter the lower bound (a): ");
    scanf("%d", &a);

    printf("Enter the upper bound (b): ");
    scanf("%d", &b);

    // Инициализируем генератор случайных чисел
    srand(time(NULL));

    int *arr = (int *)malloc(size * sizeof(int));

    // Заполняем массив случайными числами
    fill_array(arr, size, a, b);

    printf("Initial array:\n");
    print_array(arr, size);

    // Меняем местами минимальный и максимальный элементы
    swap_min_max(arr, size);

    printf("Array after swapping min and max:\n");
    print_array(arr, size);

    free(arr);

    return 0;
}
