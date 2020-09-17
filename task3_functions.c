#include "task3_functions.h"

int compare_strings(char *s1, char *s2) {
    printf("comparing: ");
    for(int i = 0; *(s1 + i) != '\n'; ++i) {
        printf("%c", s1[i]);
    }
    printf(" and ");
    for(int i = 0; *(s2 + i) != '\n'; ++i) {
        printf("%c", s2[i]);
    }
    printf("\n");
    while (*s1 != '\n' && !isalpha(*s1)){
        ++s1;
    }
    while (*s2 != '\n' && !isalpha(*s2)){
        ++s2;
    }
    while (tolower(*s1) == tolower(*s2)) {
        if (*s1 == '\n') {
            //printf("0\n");
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
    //printf("%d\n", *s1 - *s2);
    return *s1 - *s2;

}

int compare_from_end(char *s1, char *s2) {
    /*printf("comparing: \n");
    my_print(s1);
    printf(" --- ");
    my_print(s2);
    printf("\n");*/
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    char *s3 = calloc(n1, sizeof(char));
    char *s4 = calloc(n2, sizeof(char));
    char *s11 = calloc(n1, sizeof(char));
    char *s22 = calloc(n2, sizeof(char));
    int cnt = 0;
    while (*s1 != '\n') {
        if (isalpha(*s1)){
            *(s3 + cnt) = *s1;
            cnt++;
        }
        s1++;
    }
    *(s3+cnt) = '\n';


    for(int i = cnt - 1; i >= 0; --i) {
        *(s11 + (cnt - i - 1)) = *(s3 + i);
    }

    *(s11 + cnt) = '\n';

    cnt = 0;


    while (*s2 != '\n') {
        if (isalpha(*s2)){
            *(s4 + cnt) = *s2;
            cnt++;
        }
        s2++;
    }
    *(s4+cnt) = '\n';

    for(int i = cnt - 1; i >= 0; --i) {
        *(s22 + (cnt - i - 1)) = *(s4 + i);
    }

    *(s22 + cnt) = '\n';

    /*printf("reworked into: ");
    my_print(s11);
    printf(" --- ");
    my_print(s22);
    printf("\n");*/
    free(s3);
    free(s4);
    int res = compare_strings(s11, s22);
    free(s11);
    free(s22);
    return res;
}

void quicksort(char *lines[MAXLINES], int start, int finish, int (*cmp) (char *, char *)) {
    //printf("%d %d\n", start, finish);
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
    *file_size = file_stats.st_size;
    return result;
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
        if (buffer[i] == '\n') {
            nlines++;
        }
    }
    return nlines;
}

void divide_into_lines(char **lines, int nlines, char *buffer) {
    lines[0] = buffer;
    int counter = 1;

    for(int i = 0;; ++i) {
        //printf("%d %d\n", buffer[i], i);
        if (counter == nlines) {
            break;
        }
        if (buffer[i] == '\n')  {
            if (counter < nlines) {
            }
            lines[counter++] = buffer + i + 1;
        }
    }
}

void my_fprint(char *string, FILE *output_file) {
    for(int i = 0; string[i] != '\n'; ++i) {
        fputc(string[i], output_file);
    }
}

void my_print(char *string) {
    for(int i = 0; string[i] != '\n'; ++i) {
        putc(string[i], stdout);
    }
}
