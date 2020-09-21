#include "task3_functions.h"


int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    char *output_filename = NULL;

    //---------------------------------------
    //обработка аргументов командной строки |
    //---------------------------------------
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (compare_strings(argv[i], "--test") == 0) {
                test_everything();
                return 0;
            }
            if (compare_strings(argv[i], "-input") == 0) {
                if (i == argc - 1){
                    break;
                }
                i++;
                input_filename = argv[i];
            }

            if (compare_strings(argv[i], "-output") == 0) {
                if (i == argc - 1){
                    break;
                }
                i++;
                output_filename = argv[i];
            }
        }
    }

    if (input_filename == NULL) {
        input_filename = "input.txt";
    }

    if (output_filename == NULL) {
        output_filename = "output.txt";
    }

    //-----------------
    //открытие файлов |
    //-----------------
    //setlocale(LC_ALL, "en_EN.CP1251");
    FILE *input = NULL, *output = NULL;
    input = fopen(input_filename, "r");
    output = fopen(output_filename, "w");

    if (input == NULL) {
        printf("Ошибка чтения файла input.txt\n");
        return 1;
    }

    if (output == NULL) {
        printf("Ошибка чтения файла output.txt\n");
        return 1;
    }

    //----------------
    //чтение в буфер |
    //----------------
    int buffer_size = 0;
    buffer_size = get_file_size(input) + 1;

    char *buffer = calloc(buffer_size, sizeof(char));
    buffer_size = fread(buffer, sizeof(char), buffer_size, input);

    //иногда fread не ставит '\0' в конце
    buffer[buffer_size] = '\0';

    //-----------------------------
    //разделение буфера на строки |
    //-----------------------------
    int nlines = get_number_of_lines(buffer);
    char **lines = calloc(nlines + 1, sizeof(char*));

    divide_lines(lines, nlines, buffer);

    //----------------
    //сортировка o_O |
    //----------------
    quicksort(lines, 0, nlines, compare_strings_from_end_void, swap_lines);


    //-----------
    //печатание |
    //-----------
    for(int i = 0; i < nlines; ++i) {
        my_fprint(lines[i], output);
        fprintf(output, "\n");
    }

    //----------------
    //и под конец... |
    //----------------
    free(buffer);
    free(lines);

    fclose(input);
    fclose(output);
    return 0;
}
