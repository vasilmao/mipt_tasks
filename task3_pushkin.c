#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>

#define EPSILON 1e-6
#define MAXLINES 100000
#define MAXLENGTH 1000



//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_strings documentation
//! compares two strings
//!
//! @param [in] char *s1 - pointer to first  string
//! @param [in] char *s2 - pointer to second string
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_strings(char *s1, char *s2);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void quicksort documentation
//! sorts part of array of strings [start, finish) - including start, excluding finish
//!
//! @param [in] char *linrs[MAXLINES] pointer to char array
//! @param [in] int start - first index to sort
//! @param [in] int last - second index to sort (excluding)
//! @param [in] int (*cmp) (char *, char *) - comparatort
//!
//! @note function uses constant MAXLINES = 10^5
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void quicksort(char *lines[MAXLINES], int start, int finish, int (*cmp) (char *, char *));

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void swap documentation
//! in main function there is *lines[] - array of pointers on char.
//! this function swaps two pointers
//!
//! @param [in] **s1 - pointer on first  pointer on char
//! @param [in] **s2 - pointer on second pointer on char
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void swap(char **s1, char **s2);




int main() {
    FILE *input = NULL, *output = NULL;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");

    int nlines = 0;
    if (input == NULL) {
        printf("Ошибка чтения файла input.txt\n");
        return 1;
    }

    if (output == NULL) {
        printf("Ошибка чтения файла output.txt\n");
        return 1;
    }

    struct stat file_stats;
    stat("input.txt", &file_stats);

    int buffer_size = file_stats.st_size + 1;

    char *buffer = calloc(buffer_size, sizeof(char));

    fread(buffer, sizeof(char), buffer_size, input);
    for(int i = 0; i < buffer_size; ++i) {
        if (buffer[i] == '\0') {
            if (i > 0) {
                if (buffer[i - 1] == '\0'){
                    buffer_size = i;
                } else {
                    nlines++;
                    buffer_size = i + 1;
                }
            }
            break;
        }
        if (buffer[i] == '\n') {
            nlines++;
            buffer[i] = '\0';
        }
    }
    char **lines = calloc(nlines + 1, sizeof(char*));

    lines[0] = buffer;
    int counter = 1;


    for(int i = 0; i < buffer_size; ++i) {
        if (buffer[i] == '\0') {
            lines[counter++] = buffer + i + 1;
        }
        if (counter == nlines) {
            break;
        }
    }
    quicksort(lines, 0, nlines, compare_strings);

    for(int i = 0; i < nlines; ++i) {
        fprintf(output, "%s\n", lines[i]);
    }

    fclose(input);
    fclose(output);
    return 0;
}


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
