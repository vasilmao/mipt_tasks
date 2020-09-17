#include "task3_functions.h"

void my_kekprint(char *s, FILE *file, int size) {
    int cnt = 0;
    //for(int i = 0; i < size; ++i){
    while (*s != '\0') {
        fprintf(file, "%c", *s);
        s++;
        cnt++;
    }
    printf("%d\n", cnt);
}

int main() {

    //setlocale(LC_ALL, "en_EN.CP1251");
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
    //result = get_file_size("input.txt", &buffer_size);
    another_file_size(input, &buffer_size);
    //buffer_size *= 2;
    buffer_size++;

    printf("perviy - %d\n", buffer_size);
    //fprintf(output, "%d\n", buffer_size);

    if (result != 0) {
        printf("Не удалось определить размер файла input.txt");
        return 1;
    }

    char *buffer = calloc(buffer_size, sizeof(char));
    result = fread(buffer, sizeof(char), buffer_size, input);
    buffer_size = result;
    printf("%d\n", result);
    buffer[buffer_size] = '\0';
    //my_kekprint(buffer, output, buffer_size);
    int nlines = get_number_of_lines(buffer);
    printf("%d\n", nlines);
    char **lines = calloc(nlines + 1, sizeof(char*));
    //printf("%d\n", nlines);
    printf("YOY2\n");
    divide_into_lines(lines, nlines, buffer);
    //fprintf(output, "%s\n", buffer);

    //printf("%d\n", nlines);



    printf("YOY1\n");
    quicksort(lines, 0, nlines, compare_reverse);
    printf("YOY\n");
    //printf("\n%d\n", nlines);

    //my_print(lines[nlines - 1]);


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
