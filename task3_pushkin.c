#include "task3_functions.h"


int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (compare_strings(argv[i], "--test") == 0) {
                
            }
        }
    }

    //setlocale(LC_ALL, "en_EN.CP1251");
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
    buffer_size = get_file_size(input);
    buffer_size++;

    char *buffer = calloc(buffer_size, sizeof(char));
    buffer_size = fread(buffer, sizeof(char), buffer_size, input);

    //sometimes fread doesnt set the last char to '0'
    buffer[buffer_size] = '\0';

    int nlines = get_number_of_lines(buffer);
    char **lines = calloc(nlines + 1, sizeof(char*));

    divide_into_lines(lines, nlines, buffer);

    quicksort(lines, 0, nlines, compare_strings_from_end_void, swap_lines);


    for(int i = 0; i < nlines; ++i) {
        my_fprint(lines[i], output);
        fprintf(output, "\n");
    }

    free(lines);
    free(buffer);

    fclose(input);
    fclose(output);
    return 0;
}
