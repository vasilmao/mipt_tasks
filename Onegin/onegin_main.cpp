#include "onegin_functions.h"



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
    struct Text onegin = {};
    initialize_text(onegin);
    read_buffer(&onegin.buffer, &onegin.buffer_size, input_filename, input);
    //fclose(input);

    //-----------------------------
    //разделение буфера на строки |
    //-----------------------------

    onegin.nlines = get_number_of_lines(onegin.buffer);
    divide_lines(&onegin.lines, onegin.nlines, onegin.buffer);

    //----------------
    //сортировка o_O |
    //----------------

    if (sort_mode == SORT_DEFAULT)  {
        qsort    (onegin.lines, onegin.nlines, sizeof(struct MyString), compare_MyStrings);
    } else if (sort_mode == SORT_FROM_END) {
        qsort    (onegin.lines, onegin.nlines, sizeof(struct MyString), compare_MyStrings_from_end);
    } else if (sort_mode == MY_SORT_DEFAULT) {
        quicksort(onegin.lines, onegin.nlines, sizeof(struct MyString), compare_MyStrings);
    } else if (sort_mode == MY_SORT_FROM_END) {
        quicksort(onegin.lines, onegin.nlines, sizeof(struct MyString), compare_MyStrings_from_end);
    }

    //-----------
    //печатание |
    //-----------

    open_file(&output, output_filename, "w");
    fprint_lines(onegin, output);
    fclose(output);

    //----------------
    //и под конец... |
    //----------------

    destroy_text(onegin);

    return 0;
}
