#include "task3_functions.h"

const int ARGUMENTSERROR = 3;

int use_cmd_arguments(int argc, char *argv[], char **input_filename, char **output_filename){
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--test") == 0) {
                return test_everything();
            }
            if (strcmp(argv[i], "--input") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
                }
                i++;
                *input_filename = argv[i];
            }

            if (strcmp(argv[i], "-i") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
                }
                i++;
                *input_filename = argv[i];
            }

            if (strcmp(argv[i], "--output") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
                }
                i++;
                *output_filename = argv[i];
            }

            if (strcmp(argv[i], "-o") == 0) {
                if (i == argc - 1){
                    return ARGUMENTSERROR;
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


int compare_strings(char *s1, char *s2) {
    assert(s1);
    assert(s2);
    while (*s1 != '\n' && *s1 != '\0' && !isalpha(*s1)){
        ++s1;
    }
    while (*s2 != '\n' && *s2 != '\0' && !isalpha(*s2)){
        ++s2;
    }
    while (tolower(*s1) == tolower(*s2)) {
        if (*s1 == '\n' || *s1 == '\0') {
            return 0;
        }
        s1++; s2++;
        while (*s1 != '\n' && *s1 != '\0' && !isalpha(*s1)){
            ++s1;
        }
        while (*s2 != '\n' && *s2 != '\0' && !isalpha(*s2)){
            ++s2;
        }
    }
    return tolower(*s1) - tolower(*s2);
}


int compare_strings_from_end(char *s1, int len1, char *s2, int len2) {
    assert(s1);
    assert(s2);
    assert(len1 >= 0);
    assert(len2 >= 0);

    int cnt = 0;
    s1 += len1 - 1;
    s2 += len2 - 1;
    len1--;
    len2--;
    while (1) {
        if (!isalpha(*s1) && len1 >= 0) {
            s1--;
            len1--;
            continue;
        }
        if (!isalpha(*s2) && len2 >= 0) {
            s2--;
            len2--;
            continue;
        }
        if (tolower(*s1) != tolower(*s2)) {
            return tolower(*s1) - tolower(*s2);
        }

        s1--;
        len1--;
        s2--;
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

int compare_my_strings(void *array, int i, int j) {
    assert(array);
    assert(i >= 0);
    assert(j >= 0);
    return compare_strings(((struct my_string *)array + i)->str, ((struct my_string *)array + j) -> str);
}

int compare_my_strings_from_end(void *array, int i, int j) {
    assert(array);
    assert(i >= 0);
    assert(j >= 0);
    struct my_string *s1 = ((struct my_string *)array + i);
    struct my_string *s2 = ((struct my_string *)array + j);
    return compare_strings_from_end(s1->str, s1->length, s2 -> str, s2->length);
}

void swap_my_strings(void *array, int i, int j) {
    assert(array);
    assert(i >= 0);
    assert(j >= 0);

    struct my_string *s1 = ((struct my_string *)array + i);
    struct my_string *s2 = ((struct my_string *)array + j);
    struct my_string tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

void quicksort(void *array, int start, int finish, int (*cmp)(void *array, int i, int j), void (*swap_quicksort)(void *array, int i, int j)){
    assert(start >= 0);
    assert(finish >= 0);
    assert(cmp);
    assert(swap_quicksort);
    assert(array);

    if (finish - start <= 1)
        return ;
    if (finish - start == 2) {
        if (cmp(array, start, finish - 1) > 0) {
            swap_quicksort(array, start, finish - 1);
        }
        return ;
    }
    int m = (start + finish) / 2;
    if (m != finish - 1) {
        swap_quicksort(array, m, finish - 1);
    }
    int place_to_insert = start;
    for (int i = start; i < finish - 1; ++i) {
        if (cmp(array, i, (finish - 1)) < 0) {
            if (i != place_to_insert){
                swap_quicksort(array, i, place_to_insert);
            }
            ++place_to_insert;
        }
    }
    if (finish - 1 != place_to_insert) {
        swap_quicksort(array, finish - 1, place_to_insert);
    }
    quicksort(array, start, place_to_insert, cmp, swap_quicksort);
    quicksort(array, place_to_insert + 1, finish, cmp, swap_quicksort);
}


int get_file_size(char *filename) {
    assert(filename);
    struct stat filestats;
    int res = stat(filename, &filestats);
    if (res != 0){
        printf("Не удалось получить размер файла %s\n", filename);
        assert(res != 0);
    }
    return filestats.st_size;
}

int get_number_of_lines(char *buffer) {
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

void divide_lines(struct my_string *lines, int nlines, char *buffer) {
    assert(lines);
    assert(nlines >= 0);
    assert(buffer);

    lines[0].str = buffer;
    int counter = 1;

    for (int i = 0;; ++i) {
        if (buffer[i] == '\n' || buffer[i] == '\0')  {
            if (counter == nlines) {
                lines[counter - 1].length = buffer + i - lines[counter - 1].str;
                break;
            }
            if (buffer[i + 1] != '\n' && buffer[i + 1] != '\0'){
                lines[counter].str = buffer + i + 1;
                lines[counter - 1].length = lines[counter].str - lines[counter - 1].str;
                counter++;
            }
        }
    }
}

void my_fprint(char *string, FILE *output_file) {
    assert(string);
    assert(output_file);

    for (int i = 0; string[i] != '\n' && string[i] != '\0'; ++i) {
        fputc(string[i], output_file);
    }
}

void my_print(char *string) {
    assert(string);
    for (int i = 0; string[i] != '\n' && string[i] != '\0'; ++i) {
        putc(string[i], stdout);
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
    printf("Все корректно!\n");
    return 2;
}


void test_compare_strings() {
    int n_tests = 3;
    char *tests[][2] = {
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
    char *tests[][2] = {
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
    char *tests[] = {
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
    char *test = "a\nb\n\nc\n";
    char *answer[] = {
        "a\n",
        "b\n",
        "c\n"
    };
    struct my_string *lines = (struct my_string *) calloc(nlines, sizeof(struct my_string));

    divide_lines(lines, nlines, test);


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
