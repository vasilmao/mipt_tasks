#include "task3_functions.h"

int compare_strings(char *s1, char *s2) {
    while (*s1 != '\0' && !isalpha(*s1)){
        ++s1;
    }
    while (*s2 != '\0' && !isalpha(*s2)){
        ++s1;
    }
    while (tolower(*s1) == tolower(*s2)) {
        if (*s1 == '\0') {
            return 0;
        }
        s1++; s2++;
        while (*s1 != '\0' && !isalpha(*s1)){
            ++s1;
        }
        while (*s2 != '\0' && !isalpha(*s2)){
            ++s2;
        }
    }

    return *s1 - *s2;

}

void quicksort(char *lines[MAXLINES], int start, int finish, int (*cmp) (char *, char *)) {
    assert(isfinite(start));
    assert(isfinite(finish));
    assert(cmp != NULL);
    if (finish - start <= 1)
        return ;
    int m = (start + finish) / 2;
    swap(&lines[m], &lines[finish - 1]);
    int place_to_insert = start;
    for (int i = start; i < finish - 1; ++i) {
        if (cmp(lines[i], lines[finish - 1]) <= 0) {
            if (i != place_to_insert){
                swap(&lines[i], &lines[place_to_insert]);
            }
            ++place_to_insert;
        }
    }
    swap(&lines[finish - 1], &lines[place_to_insert]);
    quicksort(lines, start, place_to_insert, cmp);
    quicksort(lines, place_to_insert + 1, finish, cmp);
}

void swap(char **s1, char **s2) {
    char *temp = NULL;
    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

int get_file_size(char* filename, int *file_size) {
    struct stat file_stats;
    int result = stat(filename, &file_stats);
    if (result != 0) {
        return result;
    }
    //printf("%d kek\n", file_stats.st_ino);
    *file_size = file_stats.st_size;
    return result;
}

int get_number_of_lines(char *buffer, int *buffer_size) {
    int nlines = 0;
    for(int i = 0; i < *buffer_size; ++i) {
        if (buffer[i] == '\0') {
            if (i > 0) {
                if (buffer[i - 1] == '\n'){
                    *buffer_size = i;
                } else {
                    nlines++;
                    *buffer_size = i + 1;
                }
            }
            break;
        }
        if (buffer[i] == '\n') {
            nlines++;
        }
    }
    return nlines;
}

void divide_into_lines(char **lines, int nlines, char *buffer, int buffer_size) {
    lines[0] = buffer;
    int counter = 1;


    for(int i = 0; i < buffer_size; ++i) {
        printf("%d %d\n", buffer[i], i);
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (counter == nlines) {
                break;
            }
            lines[counter++] = buffer + i + 1;
        }
    }
}
