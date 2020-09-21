#include "task3_functions.h"


int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    char *output_filename = NULL;

    //---------------------------------------
    //обработка аргументов командной строки |
    //---------------------------------------
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--test") == 0) {
                test_everything();
                return 0;
            }
            if (strcmp(argv[i], "--input") == 0) {
                if (i == argc - 1){
                    break;
                }
                i++;
                input_filename = argv[i];
            }

            if (strcmp(argv[i], "--output") == 0) {
                if (i == argc - 1){
                    break;
                }
                i++;
                output_filename = argv[i];
            }
        }
    }

    if (!input_filename) {
        input_filename = "input.txt";
    }

    if (!output_filename) {
        output_filename = "output.txt";
    }

    //-----------------
    //открытие файлов |
    //-----------------
    //setlocale(LC_ALL, "en_EN.CP1251");
    //FILE *input = NULL, *output = NULL;
    FILE* input  = fopen(input_filename,  "r");
    FILE* output = fopen(output_filename, "w");

    if (!input) {
        printf("Ошибка чтения файла %s\n", input_filename);
        return 1;
    }

    if (output == NULL) {
        printf("Ошибка чтения файла %s\n", output_filename);
        return 1;
    }

    //----------------
    //чтение в буфер |
    //----------------
    int buffer_size = get_file_size(input) + 1;

    char *buffer = calloc(buffer_size, sizeof(char));
    buffer_size  = fread (buffer,      sizeof(char), buffer_size, input);

    //иногда fread не ставит '\0' в конце
    buffer[buffer_size] = '\0';

    //-----------------------------
    //разделение буфера на строки |
    //-----------------------------
    int nlines = get_number_of_lines(buffer);
    struct my_string *lines = calloc(nlines + 1, sizeof(struct my_string));

    divide_lines(lines, nlines, buffer);

    //----------------
    //сортировка o_O |
    //----------------
    quicksort(lines, 0, nlines, compare_my_strings, swap_lines);


    //-----------
    //печатание |
    //-----------
    for(int i = 0; i < nlines; ++i) {
        my_fprint(lines[i].str, output);
        fprintf(output, "\n");
    }

    //----------------
    //и под конец... |
    //----------------
    free(buffer); buffer = NULL;
    free(lines);

    fclose(input);
    fclose(output);
    return 0;
}
