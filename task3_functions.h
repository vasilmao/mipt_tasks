#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>

extern const int  ARGUMENTSERROR;
extern const int READBUFFERERROR;

struct my_string {
    char *str;
    int length;
} ;

int read_buffer(char *buffer, int *buffer_size, FILE *input, char *input_filename);

int use_cmd_arguments(int argc, char *argv[], char **input_filename, char **output_filename);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void test_everything documentation
//! runs all test functions
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int test_everything();


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
//! int compare_my_strings documentation
//! compares two my_strings, just returns result of compare_strings function
//!
//! @param [in] void *array - array
//! @param [in] int i - first index
//! @param [in] int j - second index
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_my_strings(void *array, int i, int j);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_strings documentation
//! compares two strings from end to start, skipping everything that is not isalpha
//!
//! @param [in] char *s1 - pointer to first  string
//! @param [in] int len1 - length  of first  string
//! @param [in] char *s2 - pointer to second string
//! @param [in] int len2 - length  of second string
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_strings_from_end(char *s1, int len1, char *s2, int len2);

void test_compare_strings_from_end();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_my_strings_from_end documentation
//! compares two my_strings, just returns result of compare_strings_from_end function
//!
//! @param [in] void *array - array
//! @param [in] int i - first index
//! @param [in] int j - second index
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_my_strings_from_end(void *array, int i, int j);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void swap_my_strings documentation
//! swaps to my_string elements in array
//!
//! @param [in] void *array - array
//! @param [in] int i - first  index to swap
//! @param [in] int j - second index to swap
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void swap_my_strings(void *array, int i, int j);

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
//! int get_file_size documentation
//! this function counts file size in bytes using fseek and ftell
//!
//! @param [in] char *filename - file to count size
//!
//! @return file size
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int get_file_size(char *filename);

void test_get_file_size();


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
//! @param [in] struct my_string *lines - array of my_string to save lines
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
