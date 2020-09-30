#include "onegin_functions.h"

void initialize_text(Text text) {
    text.buffer = NULL;
    text.buffer_size = 0;
    text.lines = NULL;
    text.nlines = 0;
}

int main(int argc, const char *argv[]) {
    const char *input_filename  = NULL;
    const char *output_filename = NULL;
    FILE *input = NULL, *output = NULL;
    int sort_mode = NO_SORT;

    //setlocale(LC_ALL, "en_EN.CP1251");

    //---------------------------------------
    //обработка аргументов командной строки |
    //---------------------------------------

    int arg_result = analyse_cmd_arguments(argc, argv, &input_filename, &output_filename, &sort_mode);
    if (arg_result == ARGUMENTSERROR){
        printf("Ошибка при считывании аргументов командной строк\n");
        return ARGUMENTSERROR;
    } else if (arg_result == TESTSCORRECT) {
        return 0;
    }


    //-----------------
    //открытие файлов |
    //-----------------

    open_file(&input, input_filename, "r");

    //----------------
    //чтение в буфер |
    //----------------
    struct Text Onegin = {};
    initialize_text(Onegin);
    read_buffer(&Onegin.buffer, &Onegin.buffer_size, input_filename, input);
    //fclose(input);

    //-----------------------------
    //разделение буфера на строки |
    //-----------------------------

    Onegin.nlines = get_number_of_lines(Onegin.buffer);
    divide_lines(&Onegin.lines, Onegin.nlines, Onegin.buffer);

    //----------------
    //сортировка o_O |
    //----------------

    if (sort_mode == SORT_DEFAULT)  {
        qsort    (Onegin.lines, Onegin.nlines,                sizeof(struct my_string), compare_my_strings);
    } else if (sort_mode == SORT_FROM_END) {
        qsort    (Onegin.lines, Onegin.nlines,                sizeof(struct my_string), compare_my_strings_from_end);
    } else if (sort_mode == MY_SORT_DEFAULT) {
        quicksort(Onegin.lines, Onegin.lines + Onegin.nlines, sizeof(struct my_string), compare_my_strings);
    } else if (sort_mode == MY_SORT_FROM_END) {
        quicksort(Onegin.lines, Onegin.lines + Onegin.nlines, sizeof(struct my_string), compare_my_strings_from_end);
    }

    //-----------
    //печатание |
    //-----------

    open_file(&output, output_filename, "w");
    fprint_lines(Onegin, output);
    fclose(output);

    //----------------
    //и под конец... |
    //----------------

    destroy_text(Onegin);

    return 0;
}
