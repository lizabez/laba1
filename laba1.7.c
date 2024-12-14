#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Функция для перевода числа в систему счисления с основанием 4
char* to_base_4(int num) {
    static char buffer[32];
    sprintf(buffer, "%o", num);  // Используем 8-ричную систему для вывода в строковом виде
    return buffer;
}

// Функция для перевода числа в систему счисления с основанием 8
char* to_base_8(int num) {
    static char buffer[32];
    sprintf(buffer, "%o", num);  // Используем 8-ричную систему для вывода в строковом виде
    return buffer;
}

// Функция для чтения лексем из файла и записи их в массив
int read_lexemes(const char* filename, char*** lexemes) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("The file could not be opened");
        return 0;
    }

    char** result = malloc(sizeof(char*) * 1000);  // Аллоцируем память для лексем
    int count = 0;
    char buffer[256];
    
    while (fscanf(file, "%255s", buffer) == 1) {
        result[count] = strdup(buffer);  // Копируем строку в массив
        count++;
    }
    
    fclose(file);
    *lexemes = result;
    return count;
}

// Функция для обработки флага -r
void process_r(char* file1_path, char* file2_path, char* output_path) {
    char** lexemes1, **lexemes2;
    int count1 = read_lexemes(file1_path, &lexemes1);
    int count2 = read_lexemes(file2_path, &lexemes2);

    FILE* output_file = fopen(output_path, "w");
    if (!output_file) {
        perror("The file could not be opened for writing");
        return;
    }

    int i = 0, j = 0;
    while (i < count1 || j < count2) {
        if (i < count1) {
            fprintf(output_file, "%s ", lexemes1[i]);
            i++;
        }
        if (j < count2) {
            fprintf(output_file, "%s ", lexemes2[j]);
            j++;
        }
    }

    fclose(output_file);

    // Освобождение памяти
    for (int i = 0; i < count1; i++) free(lexemes1[i]);
    for (int i = 0; i < count2; i++) free(lexemes2[i]);
    free(lexemes1);
    free(lexemes2);
}

// Функция для обработки флага -a
void process_a(char* file_path, char* output_path) {
    char** lexemes;
    int count = read_lexemes(file_path, &lexemes);

    FILE* output_file = fopen(output_path, "w");
    if (!output_file) {
        perror("The file could not be opened for writing");
        return;
    }

    for (int i = 0; i < count; i++) {
        char* lexeme = lexemes[i];
        if ((i + 1) % 10 == 0) {  // Десятая лексема
            for (int j = 0; lexeme[j]; j++) {
                lexeme[j] = tolower(lexeme[j]);  // Преобразуем в строчные буквы
            }
            for (int j = 0; lexeme[j]; j++) {
                fprintf(output_file, "%s ", to_base_4((int)lexeme[j]));
            }
        } else if ((i + 1) % 2 == 0) {  // Вторая лексема
            for (int j = 0; lexeme[j]; j++) {
                lexeme[j] = tolower(lexeme[j]);  // Преобразуем в строчные буквы
            }
            fprintf(output_file, "%s ", lexeme);
        } else if ((i + 1) % 5 == 0) {  // Пятая лексема
            for (int j = 0; lexeme[j]; j++) {
                fprintf(output_file, "%s ", to_base_8((int)lexeme[j]));
            }
        } else {
            fprintf(output_file, "%s ", lexeme);
        }
    }

    fclose(output_file);

    // Освобождение памяти
    for (int i = 0; i < count; i++) free(lexemes[i]);
    free(lexemes);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("The number of arguments is incorrect.\n");
        return 1;
    }

    char* flag = argv[1];
    
    if (strcmp(flag, "-r") == 0) {
        if (argc != 5) {
            printf("For the -r flag, 4 arguments must be specified.\n");
            return 1;
        }
        char* file1_path = argv[2];
        char* file2_path = argv[3];
        char* output_path = argv[4];
        process_r(file1_path, file2_path, output_path);
    } else if (strcmp(flag, "-a") == 0) {
        if (argc != 4) {
            printf("For the -a flag, 3 arguments must be specified.\n");
            return 1;
        }
        char* file_path = argv[2];
        char* output_path = argv[3];
        process_a(file_path, output_path);
    } else {
        printf("Unknown flag: %s\n", flag);
        return 1;
    }

    return 0;
}
