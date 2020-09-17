#include "task3_functions.h"



int main() {

    //setlocale(LC_ALL, "ru_RU.CP1251");
    int result = 0;
    FILE *input = NULL, *output = NULL;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    if (input == NULL) {
        printf("Ошибка чтения файла input.txt\n");
        return 1;
    }

    if (output == NULL) {
        printf("Ошибка чтения файла output.txt\n");
        return 1;
    }

    int buffer_size = 0;
    result = get_file_size("input.txt", &buffer_size);

    buffer_size++;

    printf("%d\n", buffer_size);
    //fprintf(output, "%d\n", buffer_size);

    if (result != 0) {
        printf("Не удалось определить размер файла input.txt");
        return 1;
    }

    char *buffer = calloc(buffer_size, sizeof(char));
    fread(buffer, sizeof(char), buffer_size, input);

    int nlines = get_number_of_lines(buffer);
    printf("%d\n", nlines);
    char **lines = calloc(nlines + 1, sizeof(char*));
    printf("%d\n", nlines);
    divide_into_lines(lines, nlines, buffer);

    printf("%d\n", nlines + 5);

    my_print(lines[0]);

    quicksort(lines, 0, nlines, compare_from_end);

    my_print(lines[0]);

    for(int i = 0; i < nlines; ++i) {
        my_fprint(lines[i], output);
        fprintf(output, "\n");
    }

    //printf("%d\n", compare_from_end("bb,a\n", "b,.,ba\n"));

    free(lines);
    free(buffer);

    fclose(input);
    fclose(output);
    return 0;
}
