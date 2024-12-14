#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void remove_digits(FILE *input, FILE *output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!isdigit(ch)) {
            fputc(ch, output);
        }
    }
}



void count_latin_letters(FILE *input, FILE *output) {
    char ch;
    int count = 0;  // Переменная для подсчета латинских букв

    while ((ch = fgetc(input)) != EOF) {
        // Проверяем, является ли символ латинской буквой
        if (isalpha(ch) && (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')) {
            count++;  // Увеличиваем счетчик для каждой латинской буквы
        }
    }

    // Записываем результат в файл
    fprintf(output, "Number of Latin letters: %d\n", count);
}


void count_special_symbols(FILE *input, FILE *output) {
    char ch;
    int count = 0;
    while ((ch = fgetc(input)) != EOF) {
        if (!(isalpha(ch) || isdigit(ch) || isspace(ch))) {
            count++;
        }
    }
    fprintf(output, "%d\n", count);
}

void replace_with_ascii_hex(FILE *input, FILE *output) {
    char ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!isdigit(ch)) {
            fprintf(output, "%X  ", (unsigned char)ch);
        } else {
            fputc(ch, output);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Insufficient arguments\n");
        return 1;
    }

    char *flag = argv[1];
    char *input_file = argv[2];
    char *output_file = NULL;

    if (argc > 3) {
        output_file = argv[3];
    } else {
        output_file = malloc(strlen(input_file) + 5);
        strcpy(output_file, "out_");
        strcat(output_file, input_file);
    }

    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Failed to open input file\n");
        return 1;
    }

    FILE *output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Failed to open input file\n");
        fclose(input);
        return 1;
    }

    if (strcmp(flag, "-d") == 0 || strcmp(flag, "/d") == 0) {
        remove_digits(input, output);
    } else if (strcmp(flag, "-i") == 0 || strcmp(flag, "/i") == 0) {
        count_latin_letters(input, output);
    } else if (strcmp(flag, "-s") == 0 || strcmp(flag, "/s") == 0) {
        count_special_symbols(input, output);
    } else if (strcmp(flag, "-a") == 0 || strcmp(flag, "/a") == 0) {
        replace_with_ascii_hex(input, output);
    } else {
        printf("Unknown flag: %s\n", flag);
        fclose(input);
        fclose(output);
        return 1;
    }

    fclose(input);
    fclose(output);

    printf("The result has been written to the file: %s\n", output_file);

    if (argc < 4) {
        free(output_file);
    }

    return 0;
}
