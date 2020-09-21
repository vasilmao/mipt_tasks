#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>

struct my_string {
    char *str;
    int length;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void test_everything documentation
//! runs all test functions
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void test_everything();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_strings_void documentation
//! converts void *array to (char **) and compares arr[i] and arr[j]
//!
//! @param [in] void *array - array of strings
//! @param [in] int i - index of first string
//! @param [in] int j - index of second string
//!
//! @return returns result of compare_strings()
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_strings_void(void *array, int i, int j);

int compare_my_strings(void *s1, void *s2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_strings_void documentation
//! converts void *array to (char **) and compares arr[i] and arr[j] from end
//!
//! @param [in] void *array - array of strings
//! @param [in] int i - index of first string
//! @param [in] int j - index of second string
//!
//! @return returns result of compare_strings_from end()
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_strings_from_end_void(void *array, int i, int j);


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

void test_compare_strings();


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

void test_compare_strings_from_end();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void quicksort documentation
//! sorts part of array of anything you want if you have comporator and swapper for this, [start, finish) - including start, excluding finish
//!
//! @param [in] void *array - array of what you want
//! @param [in] int start - first index to sort
//! @param [in] int last - second index to sort (excluding)
//! @param [in] int (*cmp) (void *arr, int i, int j) - compare arr[i] and arr[j] (write by yourself);
//! @param [in] void (*swap_quicksort)(void *array, int i, int j)) - swap array[i] and array[j];
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void quicksort(void *array, int start, int finish, int (*cmp)(void *array, int i, int j), void (*swap_quicksort)(void *array, int i, int j));

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void swap_lines documentation
//! this function converts lines from (void *) to (char **) and ...
//! ... and swaps lines[i] and lines[j] by calling swap_lines function
//!
//! @param [in] void *lines - array of strings
//! @param [in] int i - index of first string to swap
//! @param [in] int j - index of second string to swap
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void swap_lines(void *lines, int i, int j);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void swap_strings documentation
//! this function swaps two strings by pointers
//!
//! @param [in] **s1 - pointer on first  pointer on char
//! @param [in] **s2 - pointer on second pointer on char
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void swap_strings(char **s1, char **s2);

void test_swap_strings();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int get_file_size documentation
//! this function counts file size in bytes using fseek and ftell
//!
//! @param [in] FILE *file - file to count size
//! @param [in] int *file_size - pointer to integer, here file size will br written
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int get_file_size(FILE *input);

void  test_get_file_size();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int get_number_of_lines documentation
//! this function counts number of lines in string
//!
//! @param [in] char *buffer - string to count nlines
//!
//! @return number of lines
//!
//! @note it skips empty lines
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int get_number_of_lines(char *buffer);

void test_get_number_of_lines();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void divide_lines documentation
//! this function divides buffer to lines
//!
//! @param [in] char **lines - array of char* - array to save lines
//! @param [in] int nlines - number of lines to split
//! @param [in] char *buffer - string to count nlines
//!
//! @it skips empty lines like get_number_of_lines function
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void divide_lines(struct my_string *lines, int nlines, char *buffer);

void test_divide_lines();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void my_fprint documentation
//! this function prints string to file (end of string is '\n' or '\0')
//!
//! @param [in] char *string - string
//! @param [in] FILE *output_file - print to this file
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void my_fprint(char *string, FILE *output_file);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void my_print documentation
//! this function prints string to stdout (end of string is '\n' or '\0')
//!
//! @param [in] char *string - string
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void my_print(char *string);
