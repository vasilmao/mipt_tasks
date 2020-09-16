#include "task3_functions.h"



int main() {
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

    if (result != 0) {
        printf("Не удалось определить размер файла input.txt");
        return 1;
    }

    char *buffer = calloc(buffer_size, sizeof(char));

    fread(buffer, sizeof(char), buffer_size, input);

    int nlines = get_number_of_lines(buffer, &buffer_size);

    char **lines = calloc(nlines + 1, sizeof(char*));

    divide_into_lines(lines, nlines, buffer, buffer_size);

    quicksort(lines, 0, nlines, compare_strings);

    for(int i = 0; i < nlines; ++i) {
        for(int j = 0; ; ++j) {
            //fprintf(output, "%d\n", lines[i][j]);
            if (lines[i][j] == '\0'){
                break;
            }
        }
        fprintf(output, "%s\n", lines[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}
