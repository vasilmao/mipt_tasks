#include "task3_functions.h"

//2 - норм тестировано
//1 - ошибка аргументов

int user_cmd_arguments(int argc, char *argv[], char **input_filename, char **output_filename){
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--test") == 0) {
                return test_everything();
            }
            if (strcmp(argv[i], "--input") == 0) {
                if (i == argc - 1){
                    return 1;
                }
                i++;
                *input_filename = argv[i];
            }

            if (strcmp(argv[i], "-i") == 0) {
                if (i == argc - 1){
                    return 1;
                }
                i++;
                *input_filename = argv[i];
            }

            if (strcmp(argv[i], "--output") == 0) {
                if (i == argc - 1){
                    return 1;
                }
                i++;
                *output_filename = argv[i];
            }

            if (strcmp(argv[i], "-o") == 0) {
                if (i == argc - 1){
                    return 1;
                }
                i++;
                *output_filename = argv[i];
            }
        }
    }

    if (*input_filename == NULL) {
        *input_filename = "input.txt";
    }

    if (*output_filename == NULL) {
        *output_filename = "output.txt";
    }
    return 0;
}


int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    char *output_filename = NULL;
    int result = 0;
    //---------------------------------------
    //обработка аргументов командной строки |
    //---------------------------------------

    result = user_cmd_arguments(argc, argv, &input_filename, &output_filename);
    if (result == 1){
        printf("Ошибка при считывании аргументов командной строки\n");
        return 0;
    }
    if (result == 2) {
        return 0;
    }

    //-----------------
    //открытие файлов |
    //-----------------
    //setlocale(LC_ALL, "en_EN.CP1251");
    FILE *input = NULL, *output = NULL;
    input = fopen(input_filename, "r");

    if (input == NULL) {
        printf("Ошибка открытия файла %s\n", input_filename);
        return 1;
    }


    //----------------
    //чтение в буфер |
    //----------------
    int buffer_size = 0;
    buffer_size = get_file_size(input_filename) + 1;

    char *buffer = calloc(buffer_size, sizeof(char));
    buffer_size = fread(buffer, sizeof(char), buffer_size, input);
    fclose(input);
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
    quicksort(lines, 0, nlines, compare_my_strings_from_end, swap_my_strings);


    //-----------
    //печатание |
    //-----------
    output = fopen(output_filename, "w");
    if (output == NULL) {
        printf("Ошибка открытия файла %s\n", output_filename);
        return 1;
    }
    for(int i = 0; i < nlines; ++i) {
        my_fprint(lines[i].str, output);
        fprintf(output, "\n");
    }
    fclose(output);

    //----------------
    //и под конец... |
    //----------------
    free(buffer);
    free(lines);

    fclose(input);
    fclose(output);
    return 0;
}
