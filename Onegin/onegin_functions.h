#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys\stat.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>

extern const int ARGUMENTSERROR;
extern const int TESTCORRECT;
extern const int SORT_DEFAULT;
extern const int SORT_FROM_END;

struct my_string {
    char *str;
    int length;
} ;

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! opens file
//!
//! @param [in] file     - file
//! @param [in] filename - file name
//! @param [in] mode     - mode (like r, w)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void open_file(FILE **file, char *filename, const char *mode);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! reads from input file to buffer
//!
//! @param [in] buffer         - buffer to write
//! @param [in] buffer_size    - variable to write buffer size
//! @param [in] input_filename - input file name
//! @param [in] input          - input file
//!
//! @return ARGUMENTSERROR if wrong cmd arguments, TESTCORRECT if programm is in test mode and all testings are ok
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void read_buffer(char **buffer, int *buffer_size, char *input_filename, FILE *input);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! checks cmd arguments:
//! --input <file name>  - change input  filename
//! --i <file name>      - same
//! --output <file name> - change output filename
//! --o <file name>      - same
//! --END                - sort from end of strings
//! --test               - testing mode
//!
//! @param [in] argc - number of  command line arguments
//! @param [in] argv            - command line arguments
//! @param [in] input_filename  - input file name
//! @param [in] output_filename - output file name
//! @param [in] sort_mode       - sort mode
//!
//! @return ARGUMENTSERROR if wrong cmd arguments, TESTCORRECT if programm is in test mode and all testings are ok
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int use_cmd_arguments(int argc, char *argv[], char **input_filename, char **output_filename, int *sort_mode);


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
//! @param [in] s1 - pointer to first  string
//! @param [in] s2 - pointer to second string
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
//! @param [in] x1 - first  my_string
//! @param [in] x2 - second my_string
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_my_strings(void *x1, void *x2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int compare_strings documentation
//! compares two strings from end to start, skipping everything that is not isalpha
//!
//! @param [in] s1 -  pointer to first  string
//! @param [in] len1 - length of first  string
//! @param [in] s2 -  pointer to second string
//! @param [in] len2 - length of second string
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
//! @param [in] x1 - first  my_string
//! @param [in] x2 - second my_string
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_my_strings_from_end(void *x1, void *x2);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void swap_my_strings documentation
//! swaps two my_strings
//!
//! @param [in] x1 - first my_string
//! @param [in] x2 - second my_string
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void swap_my_strings(void *x1, void *x2);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void quicksort documentation
//! sorts array of anything you want if you have comporator and swapper for this
//!
//! @param [in] start - array start
//! @param [in] finish - array end (excluding)
//! @param [in] elem_size - elememt size
//! @param [in] cmp - comporator
//! @param [in] swap_quicksort - swapper
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void quicksort(void *start, void *finish, int elem_size, int (*cmp)(void *x1, void *x2), void (*swap_quicksort)(void *x1, void *x2));


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
//! @param [in] lines - array of my_string to save lines
//! @param [in] nlines - number of lines to split
//! @param [in] buffer - string to count nlines
//!
//! @note it skips empty lines like get_number_of_lines function
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void divide_lines(struct my_string **lines, int nlines, char *buffer);

void test_divide_lines();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! void my_fprint documentation
//! this function prints string to file (end of string is '\n' or '\0')
//!
//! @param [in] string - string
//! @param [in] output_file - print to this file
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
