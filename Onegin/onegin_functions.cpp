#include "onegin_functions.h"

const int ARGUMENTSERROR = 3;
const int TESTSCORRECT = 4;
const int NO_SORT = 0;
const int SORT_DEFAULT = 1;
const int SORT_FROM_END = 2;

void open_file(FILE **file, const char *filename, const char *mode) {
    assert(file);
    assert(filename);
    *file = fopen(filename, mode);
    if (*file == NULL) {
        printf("Ошибка открытия файла %s\n", filename);
    }
    assert(*file);
}

int analyse_cmd_arguments(int argc, const char *argv[], const char **input_filename, const char **output_filename, int *sort_mode){
    assert(argv);
    assert(input_filename);
    assert(output_filename);
    *sort_mode = NO_SORT;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--test") == 0) {
                return test_everything();
            }
             else if (strcmp(argv[i], "--input") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
                }
                i++;
                *input_filename = argv[i];
            }

            else if (strcmp(argv[i], "-i") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
                }
                i++;
                *input_filename = argv[i];
            }

            else if (strcmp(argv[i], "--output") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
                }
                i++;
                *output_filename = argv[i];
            }

            else if (strcmp(argv[i], "-o") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
                }
                i++;
                *output_filename = argv[i];
            } else if (strcmp(argv[i], "--sort") == 0) {
                *sort_mode = SORT_DEFAULT;
            }
            else if (strcmp(argv[i], "--sort_end") == 0) {
                *sort_mode = SORT_FROM_END;
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

void read_buffer(char **buffer, int *buffer_size, const char *input_filename, FILE *input) {
    assert(buffer);
    assert(input_filename);
    assert(input);
    *buffer_size = get_file_size(input_filename) + 1;

    *buffer = (char *) calloc(*buffer_size, sizeof(char));
    *buffer_size = fread(*buffer, sizeof(char), *buffer_size, input);
    fclose(input);
    //fread не ставит '\0' в конце
    (*buffer)[*buffer_size] = '\0';
}


int compare_strings(const char *string1, const char *string2) {
    assert(string1);
    assert(string2);
    while (*string1 != '\n' && *string1 != '\0' && !isalpha(*string1)){
        ++string1;
    }
    while (*string2 != '\n' && *string2 != '\0' && !isalpha(*string2)){
        ++string2;
    }
    while (tolower(*string1) == tolower(*string2)) {
        if (*string1 == '\n' || *string1 == '\0') {
            return 0;
        }
        string1++; string2++;
        while (*string1 != '\n' && *string1 != '\0' && !isalpha(*string1)){
            ++string1;
        }
        while (*string2 != '\n' && *string2 != '\0' && !isalpha(*string2)){
            ++string2;
        }
    }
    return tolower(*string1) - tolower(*string2);
}


int compare_strings_from_end(const char *string1, int len1, const char *string2, int len2) {
    assert(string1);
    assert(string2);
    assert(len1 >= 0);
    assert(len2 >= 0);

    int cnt = 0;
    string1 += len1 - 1;
    string2 += len2 - 1;
    len1--;
    len2--;
    while (1) {
        if (!isalpha(*string1) && len1 >= 0) {
            string1--;
            len1--;
            continue;
        }
        if (!isalpha(*string2) && len2 >= 0) {
            string2--;
            len2--;
            continue;
        }
        if (tolower(*string1) != tolower(*string2)) {
            return tolower(*string1) - tolower(*string2);
        }

        string1--;
        len1--;
        string2--;
        len2--;
        if (len1 < 0 || len2 < 0) {
            if (len1 == 0 && len2 == 0) {
                return 0;
            } else {
                return len1 - len2;
            }
        }
    }
}

int compare_my_strings(void *elem1, void *elem2) {
    assert(elem1);
    assert(elem2);
    struct my_string *string1 = (struct my_string *)elem1;
    struct my_string *string2 = (struct my_string *)elem2;
    return compare_strings(string1->str, string2->str);
}

int compare_my_strings_from_end(void *elem1, void *elem2) {
    assert(elem1);
    assert(elem2);
    struct my_string *string1 = (struct my_string *)elem1;
    struct my_string *string2 = (struct my_string *)elem2;
    return compare_strings_from_end(string1->str, string1->length, string2->str, string2->length);
}

void swap(void *elem1, void *elem2, int size) {
    assert(elem1);
    assert(elem2);
    void *temp = calloc(1, size);
    memcpy(temp, elem1, size);
    memcpy(elem1, elem2, size);
    memcpy(elem2, temp, size);
}


void quicksort(void *start, void *finish, int elem_size, int (*cmp)(void *elem1, void *elem2)){
    assert(start);
    assert(finish);
    assert(elem_size >= 0);
    assert(cmp);
    //assert(swap_quicksort);

    char *left = (char *) start;
    char *right = (char *) finish;
    if (right - left <= elem_size)
        return ;
    if (right - left == 2 * elem_size) {
        if (cmp((void *) left, (void *) (right - elem_size)) > 0) {
            swap((void *) left, (void *)(right - elem_size), elem_size);
        }
        return ;
    }
    char * m = left + ((right - left) / 2) / elem_size * elem_size;
    if (m != right - elem_size) {
        swap((void *)m, (void *)(right - elem_size), elem_size);
    }
    char *place_to_insert = left;
    char *i = left;
    for (; i < right - elem_size; i += elem_size) {
        if (cmp((void *)i, (void *)(right - elem_size)) <= 0) {
            //printf("yiy\n");
            if (i != place_to_insert){
                swap((void *)i, (void *)place_to_insert, elem_size);
            }
            place_to_insert += elem_size;
        }
    }
    if (right - elem_size != place_to_insert) {
        swap((void *)(right - elem_size), (void *) place_to_insert, elem_size);
    }
    quicksort(left, place_to_insert, elem_size, cmp);
    quicksort(place_to_insert + elem_size, right, elem_size, cmp);
}


int get_file_size(const char *filename) {
    assert(filename);
    struct stat filestats;
    int res = stat(filename, &filestats);
    if (res != 0){
        printf("Не удалось получить размер файла %s\n", filename);
        assert(res != 0);
    }
    return filestats.st_size;
}

int get_number_of_lines(const char *buffer) {
    assert(buffer);

    int nlines = 0;
    for (int i = 0; ; ++i) {
        if (buffer[i] == '\n') {
            if (i > 0) {
                if (buffer[i - 1] != '\n') {
                    nlines++;
                }
            }
        }
        if (buffer[i] == '\0') {
            //We met end of buffer. If the last symbol is \n than we have already counted that line.
            //And if buffer doesnt end on \n than we must count the last line
            if (i > 0) {
                if (buffer[i - 1] != '\n') {
                    nlines++;
                }
            }
            break;
        }
    }
    return nlines;
}

void divide_lines(struct my_string **lines, int nlines, char *buffer) {
    assert(lines);
    assert(nlines >= 0);
    assert(buffer);

    *lines = (struct my_string *)calloc(nlines + 1, sizeof(struct my_string));
    (*lines)[0].str = buffer;
    int counter = 1;

    for (int i = 0;; ++i) {
        if (buffer[i] == '\n' || buffer[i] == '\0')  {
            if (counter == nlines) {
                (*lines)[counter - 1].length = buffer + i - (*lines)[counter - 1].str;
                break;
            }
            if (buffer[i + 1] != '\n' && buffer[i + 1] != '\0'){
                (*lines)[counter].str = buffer + i + 1;
                (*lines)[counter - 1].length = (*lines)[counter].str - (*lines)[counter - 1].str;
                counter++;
            }
        }
    }
}

void my_fprint(const char *string, FILE *output_file) {
    assert(string);
    assert(output_file);

    for (int i = 0; string[i] != '\n' && string[i] != '\0'; ++i) {
        fputc(string[i], output_file);
    }
}

void my_print(const char *string) {
    assert(string);
    for (int i = 0; string[i] != '\n' && string[i] != '\0'; ++i) {
        putc(string[i], stdout);
        //printf("%d ", string[i]);
    }
}




//TESTS




int test_everything() {
    printf("Начинаем тестирование...\n");
    test_compare_strings();
    test_compare_strings_from_end();
    test_get_file_size();
    test_get_number_of_lines();
    test_divide_lines();
    test_quicksort();
    printf("Все корректно!\n");
    return TESTSCORRECT;
}


void test_compare_strings() {
    int n_tests = 3;
    const char *tests[][2] = {
        {"abc", "A,B---c"},
        {"AAB", "aac"},
        {"a..Ab", "...,,,aa**a"}
    };

    int answers[] = {
        0,
        -1,
        1
    };

    for (int i = 0; i < n_tests; ++i) {
        int res = compare_strings(tests[i][0], tests[i][1]);
        if (res != answers[i]) {
            printf("Ошибка при тестировании!\nФункция compare_everything\ninput strings: %s\n%s\nожидаемый результат: %d\n полученный результат: %d\n", tests[i][0], tests[i][1], answers[i], res);
        }
        assert(answers[i] == res);
    }
}

void test_compare_strings_from_end() {
    int n_tests = 3;
    const char *tests[][2] = {
        {"cba", "C---B,A"},
        {"BAA", "caa"},
        {"bA..a", "a**aa,,,..."}
    };

    int answers[] = {
        0,
        -1,
        1
    };

    for (int i = 0; i < n_tests; ++i) {
        int res = compare_strings_from_end(tests[i][0], strlen(tests[i][0]), tests[i][1], strlen(tests[i][1]));
        if (res != answers[i]) {
            printf("Ошибка при тестировании!\nФункция compare_strings_from_end\ninput strings: %s\n%s\nОжидаемый результат: %d\nПолученный результат: %d\n", tests[i][0], tests[i][1], answers[i], res);
        }
        assert(answers[i] == res);
    }
}

void test_get_file_size() {
    FILE *file = NULL;
    file = fopen("FILE_SIZE_TESTER.txt", "w");
    fprintf(file, "abcde");
    int answer = 5;
    fclose(file);
    int result = get_file_size("FILE_SIZE_TESTER.txt");
    if (result != answer) {
        printf("Ошибка при тестировании!\nФуникция get_file_size\nОжидаемый результат: %d\nПолученный результат: %d\n", answer, result);
    }
    assert(result == answer);
}

void test_get_number_of_lines() {
    int n_tests = 2;
    const char *tests[] = {
        "a\nb\nc\n",
        "\n\n\na\n\n\n"
    };
    int answers[] = {
        3,
        1
    };

    for (int i = 0; i < n_tests; ++i) {
        int result = get_number_of_lines(tests[i]);
        if (answers[i] != result) {
            printf("Ошибка при тестировании!\nФуникция get_number_of_lines\nОжидаемый результат: %d\nПолученный результат: %d\n", answers[i], result);
        }
        assert(answers[i] == result);
    }
}

void test_divide_lines() {
    int nlines = 3;
    char *test = (char *)calloc(8, sizeof(char));
    strcpy(test, "a\nb\n\nc\n");
    //test[0] = 'a'; test[1] = '\n'; test[2] = 'b'; test[3] = '\n'; test[4] = '\n'; test[5] = 'c'; test[6] = '\n';
    //char *test = "a\nb\n\nc\n";
    const char *answer[] = {
        "a\n",
        "b\n",
        "c\n"
    };
    struct my_string *lines = (struct my_string *) calloc(nlines, sizeof(struct my_string));

    divide_lines(&lines, nlines, test);


    for (int i = 0; i < nlines; ++i) {
        int result = compare_strings(answer[i], lines[i].str);
        if (result != 0) {
            printf("Ошибка при тестировании!\nФуникция divide_lines\nCтрока номер%d\nОжидаемая строка:\n", i);
            my_print(answer[i]);
            printf("\nПолученная строка:\n");
            my_print(lines[i].str);
            printf("\n");
        }
        assert(result == 0);
    }
}

void test_quicksort() {
    int nlines = 3;
    char *test_buffer = (char *)calloc(7, sizeof(char));
    strcpy(test_buffer, "c\na\nb\n");
    struct my_string *lines = (struct my_string *) calloc(nlines, sizeof(struct my_string));

    const char *answer[] = {
        "a\n",
        "b\n",
        "c\n"
    };

    divide_lines(&lines, nlines, test_buffer);

    quicksort(lines, lines + nlines, sizeof(struct my_string), compare_my_strings);

    for(int i = 0; i < nlines; ++i) {
        int result = compare_strings(answer[i], lines[i].str);
        if (result != 0) {
            printf("Ошибка при тестировании!\nФуникция quicksort\nCтрока номер%d\nОжидаемая строка:\n", i);
            my_print(answer[i]);
            printf("\nПолученная строка:\n");
            my_print(lines[i].str);
            printf("\n");
        }
        assert(result == 0);
    }

}
