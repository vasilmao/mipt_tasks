#include "task3_functions.h"

//2 - норм тестировано
//1 - ошибка аргументов



int main(int argc, char *argv[]) {
    printf("BRUH\n");
    char *input_filename = NULL;
    char *output_filename = NULL;
    int result = 0;
    int sort_mode = SORT_DEFAULT;
    //---------------------------------------
    //обработка аргументов командной строки |
    //---------------------------------------

    result = use_cmd_arguments(argc, argv, &input_filename, &output_filename, &sort_mode);
    if (result == ARGUMENTSERROR){
        printf("Ошибка при считывании аргументов командной строк\n");
        return ARGUMENTSERROR;
    }
    if (result == TESTCORRECT) {
        return 0;
    }

    printf("YAY0\n");

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
    char *buffer;
    read_buffer(&buffer, &buffer_size, input_filename, input);
    //-----------------------------
    //разделение буфера на строки |
    //-----------------------------
    int nlines = get_number_of_lines(buffer);
    struct my_string *lines;
    //struct my_string *lines = (struct my_string *)calloc(nlines + 1, sizeof(struct my_string));
    divide_lines(&lines, nlines, buffer);

    //----------------
    //сортировка o_O |
    //----------------
    /*if (sort_mode == SORT_DEFAULT){
        quicksort(lines, 0, nlines, compare_my_strings, swap_my_strings);
    } else if (sort_mode == SORT_FROM_END) {
        quicksort(lines, 0, nlines, compare_my_strings_from_end, swap_my_strings);
    }*/
    printf("YOY\n");
    quicksort_kek(lines, 0, nlines, sizeof(struct my_string), compare_kek, swap_kek);


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
