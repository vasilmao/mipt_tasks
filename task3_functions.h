#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>

#define EPSILON 1e-6

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_strings documentation
//! compares two strings, skipping everything that is not isalpha
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
//! sorts part of array of anything you want if you have comporator and swapper for this, [start, finish) - including start, excluding finish
//!
//! @param [in] void *array - array of what you want
//! @param [in] int start - first index to sort
//! @param [in] int last - second index to sort (excluding)
//! @param [in] int (*cmp) (void *arr, int i, int j) - compare arr[i] and arr[j] (write by yourself);
//! @param [in] void (*swap_quicksort)(void *array, int i, int j)) - swap array[i] and array[j]
//! @note function uses constant MAXLINES = 10^5
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void quicksort(void *array, int start, int finish, int (*cmp)(void *array, int i, int j), void (*swap_quicksort)(void *array, int i, int j));

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


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int get_file_size documentation
//!
//! this function counts file size in bytes using <sys/stat.h> and writes the size into second argument
//!
//! @param [in] FILE *file - file to count size
//! @param [in] int *file_size - pointer to integer, here file size will br written
//!
//! @return 0 if everything is correct, -1 if not (same return as stat() function from <sys/stat.h>)
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void get_file_size(FILE *input, int *file_size);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int get_number_of_lines documentation
//!
//! this function counts number of lines in string
//!
//! @param [in] char *buffer - string to count nlines
//!
//! @return number of lines
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int get_number_of_lines(char *buffer);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void divide_into_lines documentation
//!
//! this function divides buffer to lines
//!
//! @param [in] char **lines - array of char* - array to save lines
//! @param [in] int nlines - number of lines to split
//! @param [in] char *buffer - string to count nlines
//!
//! @return number of lines
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void divide_into_lines(char **lines, int nlines, char *buffer);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void my_fprint documentation
//!
//! this function prints string to file (end of string is '\n', not '\0')
//!
//! @param [in] char *string - string
//! @param [in] FILE *output_file - print to this file
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void my_fprint(char *string, FILE *output_file);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void my_print documentation
//!
//! this function prints string to stdout (end of string is '\n', not '\0')
//!
//! @param [in] char *string - string
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void my_print(char *string);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_strings documentation
//! compares two strings from end to start, skipping everything that is not isalpha
//!
//! @param [in] char *s1 - pointer to first  string
//! @param [in] char *s2 - pointer to second string
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_strings_from_end(char *s1, char *s2);

int compare_strings_void(void *array, int i, int j);

int compare_strings_from_end_void(void *array, int i, int j);

void swap_lines(void *lines, int x1, int x2);
