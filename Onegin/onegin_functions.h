#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include <math.h>
#include <locale.h>
#include <ctype.h>

extern const int ARGUMENTSERROR;
extern const int TESTSCORRECT;
extern const int NO_SORT;
extern const int SORT_DEFAULT;
extern const int SORT_FROM_END;
extern const int MY_SORT_DEFAULT;
extern const int MY_SORT_FROM_END;

struct MyString {
    char *str;
    int length;
} ;

struct Text {
    char *buffer;
    int buffer_size;
    struct MyString *lines;
    int nlines;
} ;

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! frees buffer and lines
//!
//! @param[in] text - text
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void destroy_text(Text text);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! opens file
//!
//! @param[in] file     - file
//! @param[in] filename - file name
//! @param[in] mode     - mode (like r, w)
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void open_file(FILE **file, const char *filename, const char *mode);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! reads from input file to buffer
//!
//! @param[in] buffer         - buffer to write
//! @param[in] buffer_size    - variable to write buffer size
//! @param[in] input_filename - input file name
//! @param[in] input          - input file
//!
//! @return ARGUMENTSERROR if wrong cmd arguments, TESTCORRECT if programm is in test mode and all testings are ok
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void read_buffer(char **buffer, int *buffer_size, const char *input_filename, FILE *input);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! checks cmd arguments:\n
//! --input <file name>        - change input  filename \n
//! --i <file name>            - same\n
//! --output <file name>       - change output filename\n
//! --o <file name>            - same\n
//! --sort                     - sort from begin of strings
//! --sort_end                      - sort from end   of strings\n
//! --test                     - testing mode\n
//!
//! @param[in] argc            - number of  command line arguments
//! @param[in] argv            - command line arguments
//! @param[in] input_filename  - input file name
//! @param[in] output_filename - output file name
//! @param[in] sort_mode       - sort mode
//!
//! @return ARGUMENTSERROR if wrong cmd arguments, TESTCORRECT if programm is in test mode and all testings are ok
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int analyse_cmd_arguments(int argc, const char *argv[], const char **input_filename, const char **output_filename, int *sort_mode);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! runs all test functions
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int test_everything();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! compares two strings, skipping everything that is not isalpha
//!
//! @param[in] string1 - pointer to first  string
//! @param[in] string2 - pointer to second string
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_strings(const char *string1, const char *string2);

void test_compare_strings();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! compares two MyStrings, just returns result of compare_strings function
//!
//! @param [in] elem1 - first  MyString
//! @param [in] elem2 - second MyString
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_MyStrings(const void *elem1, const void *elem2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! compares two strings from end to start, skipping everything that is not isalpha
//!
//! @param [in] string1 -  pointer to first  string
//! @param [in] len1    - length of first  string
//! @param [in] string2 -  pointer to second string
//! @param [in] len2    - length of second string
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_strings_from_end(const char *string1, int len1, const char *string2, int len2);

void test_compare_strings_from_end();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! compares two MyStrings, just returns result of compare_strings_from_end function
//!
//! @param [in] elem1 - first  MyString
//! @param [in] elem2 - second MyString
//!
//! @return -1 if first is less than second / 0 if strings are equal / 1 if second is less than first
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int compare_MyStrings_from_end(const void *elem1, const void *elem2);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! swaps two elements
//!
//! @param [in] elem1 - first element
//! @param [in] elem2 - second element
//! @param [in] size  - elements byte size
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void swap(void *elem1, void *elem2, int size);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! sorts array of anything you want if you have comporator and swapper for this
//!
//! @param [in] start          - array start
//! @param [in] finish         - array end (excluding)
//! @param [in] elem_size      - elememt size
//! @param [in] cmp            - comporator
//! @param [in] swap_quicksort - swapper
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void quicksort(void *start, int length, int elem_size, int (*cmp)(const void *elem1, const void *elem2));

void test_quicksort();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! this function counts file size in bytes using fseek and ftell
//!
//! @param [in] char *filename - file to count size
//!
//! @return file size
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int get_file_size(const char *filename);

void test_get_file_size();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! this function counts number of lines in string
//!
//! @param [in] char *buffer - string to count nlines
//!
//! @return number of lines
//!
//! @note it skips empty lines
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int get_number_of_lines(const char *buffer);

void test_get_number_of_lines();


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! this function divides buffer to lines
//!
//! @param [in] lines  - array of MyString to save lines
//! @param [in] nlines - number of lines to split
//! @param [in] buffer - string to count nlines
//!
//! @note it skips empty lines like get_number_of_lines function
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void divide_lines(struct MyString **lines, int nlines, char *buffer);

void test_divide_lines();

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! this function prints string to file (end of string is '\n' or '\0')
//!
//! @param [in] string      - string
//! @param [in] output_file - print to this file
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void my_fprint(const char *string, FILE *output_file);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! this function prints string to stdout (end of string is '\n' or '\0')
//!
//! @param [in] char *string - string
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void my_print(const char *string);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! prints lines in text
//!
//! @param [in] text - text with lines
//! @param [in] file - file to print lines
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void fprint_lines(Text text, FILE *file);

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! initializes text structure
//!
//! @param [in] text - text structure
//!
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
void initialize_text(Text text);
