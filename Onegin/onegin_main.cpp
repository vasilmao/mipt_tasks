#include "onegin_functions.h"

//2 - норм тестировано
//1 - ошибка аргументов



int main(int argc, char *argv[]) {
    char *input_filename = NULL;
    char *output_filename = NULL;
    FILE *input = NULL, *output = NULL;
    int result = 0;
    int sort_mode = SORT_DEFAULT;
    //setlocale(LC_ALL, "en_EN.CP1251");
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


    //-----------------
    //открытие файлов |
    //-----------------

    open_file(&input, input_filename, "r");

    //----------------
    //чтение в буфер |
    //----------------
    int buffer_size = 0;
    char *buffer;
    read_buffer(&buffer, &buffer_size, input_filename, input);
    fclose(input);
    //-----------------------------
    //разделение буфера на строки |
    //-----------------------------
    int nlines = get_number_of_lines(buffer);
    struct my_string *lines;
    divide_lines(&lines, nlines, buffer);

    //----------------
    //сортировка o_O |
    //----------------
    /*if (sort_mode == SORT_DEFAULT){
        quicksort(lines, 0, nlines, compare_my_strings, swap_my_strings);
    } else if (sort_mode == SORT_FROM_END) {
        quicksort(lines, 0, nlines, compare_my_strings_from_end, swap_my_strings);
    }*/
    printf("%d\n", sort_mode);
    if (sort_mode == SORT_DEFAULT){
        quicksort(lines, lines + nlines, sizeof(struct my_string), compare_my_strings, swap_my_strings);
    } else if (sort_mode == SORT_FROM_END) {
        quicksort(lines, lines + nlines, sizeof(struct my_string), compare_my_strings_from_end, swap_my_strings);
    }

    //-----------
    //печатание |
    //-----------

    open_file(&output, output_filename, "w");
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

    return 0;
}