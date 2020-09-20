#include "task3_functions.h"


int compare_strings(char *s1, char *s2) {
    while (*s1 != '\n' && !isalpha(*s1)){
        ++s1;
    }
    while (*s2 != '\n' && !isalpha(*s2)){
        ++s2;
    }
    while (tolower(*s1) == tolower(*s2)) {
        if (*s1 == '\n') {
            return 0;
        }
        s1++; s2++;
        while (*s1 != '\n' && !isalpha(*s1)){
            ++s1;
        }
        while (*s2 != '\n' && !isalpha(*s2)){
            ++s2;
        }
    }
    return tolower(*s1) - tolower(*s2);

}

int compare_strings_void(void *string1, void *string2) {
    char *s1 = *((char **) string1);
    char *s2 = *((char **) string2);
    return compare_strings(s1, s2);
}

int compare_strings_from_end_void(void *string1, void *string2) {
    char *s1 = *((char **) string1);
    char *s2 = *((char **) string2);
    return compare_strings_from_end(s1, s2);
}


int compare_strings_from_end(char *s1, char *s2) {
    int len1 = 0, len2 = 0;
    while (*s1 != '\n') {
        len1++;
        s1++;
    }
    while (*s2 != '\n') {
        len2++;
        s2++;
    }
    int cnt = 0;
    while (1) {
        if (!isalpha(*s1) && len1 >= 0) {
            s1--;
            len1--;
            continue;
        }
        if(!isalpha(*s2) && len2 >= 0) {
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

void quicksort(void *lines[], int start, int finish, int (*cmp)(void *, void *), void (*swap_quicksort)(void *lines, int x1, int x2)){
    assert(isfinite(start));
    assert(isfinite(finish));
    assert(cmp != NULL);
    assert(lines != NULL);
    if (finish - start <= 1)
        return ;
    int m = (start + finish) / 2;
    if (m != finish - 1) {
        swap_quicksort(lines, m, finish - 1);
    }
    int place_to_insert = start;
    for (int i = start; i < finish - 1; ++i) {
        if (cmp(lines + i, lines + (finish - 1)) <= 0) {
            if (i != place_to_insert){
                swap_quicksort(lines, i, place_to_insert);
            }
            ++place_to_insert;
        }
    }
    if (finish - 1 != place_to_insert) {
        swap_quicksort(lines, finish - 1, place_to_insert);
    }
    quicksort_1(lines, start, place_to_insert, cmp, swap_quicksort);
    quicksort_1(lines, place_to_insert + 1, finish, cmp, swap_quicksort);
}

void swap_lines(void *lines, int x1, int x2) {

    swap((char **) lines + x1, (char **) lines + x2);
}


void swap(char **s1, char **s2) {
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void get_file_size(FILE *input, int *file_size) {
    fseek(input, 0, SEEK_END);
    *file_size = ftell(input);
    fseek(input, 0, SEEK_SET);
}

int get_number_of_lines(char *buffer) {
    int nlines = 0;
    for (int i = 0; ; ++i) {
        if (buffer[i] == '\0') {
            if (i > 0) {
                if (buffer[i - 1] != '\n') {
                    nlines++;
                }
            }
            break;
        }
        if (buffer[i] == '\n' && buffer[i + 1] != '\n') {
            nlines++;
        }
    }
    return nlines;
}

void divide_into_lines(char **lines, int nlines, char *buffer) {
    lines[0] = buffer;
    int counter = 1;

    for(int i = 0;; ++i) {
        if (counter == nlines) {
            break;
        }
        if (buffer[i] == '\n')  {
            if (buffer[i + 1] != '\n'){
                lines[counter++] = buffer + i + 1;
            }
        }
    }
}

void my_fprint(char *string, FILE *output_file) {
    for(int i = 0; string[i] != '\n'; ++i) {
        fputc(string[i], output_file);
    }
}

void my_print(char *string) {
    for(int i = 0; string[i] != '\n' && string[i] != '\0'; ++i) {
        printf("%c", string[i]);
    }
}
