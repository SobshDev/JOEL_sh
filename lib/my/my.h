/*
** EPITECH PROJECT, 2024
** day07
** File description:
** day07
*/


#ifndef MY_HEADER
    #define MY_HEADER
    #include <stddef.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <stdarg.h>
    #include <dirent.h>
    #include <stdbool.h>
typedef struct formatting {
    int left_justify;
    int show_sign;
    int space;
    int zero_padding;
    int width;
    int precision;
    int hexa_prefix;
    char c;
    int total_chars;
    bool star;
} formatting_t;
typedef struct my_printf {
    char *flag;
    int (*display)(va_list params, formatting_t *formatting);
} my_printf_t;
int my_print_percent(void);
void my_putchar(char c);
int my_isneg(int nb);
void my_swap(int *a, int *b);
void my_putchar(char c);
int my_putstr(char const *str);
int my_strlen(char const *str);
int my_getnbr(char const *str);
int my_getnbr_custom(char const *str);
void my_sort_int_array(int *array, int size);
int my_pow(int nb, int p);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_find_prime_sup(int nb);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
char *my_revstr(char *str);
char *my_strstr(char *str, char const *to_find);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strupcase(char *str);
char *my_strlowcase(char *str);
char *my_strcapitalize(char *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);
int my_str_isprintable(char const *str);
int my_showstr(char const *str);
int my_showmem(char const *str, int size);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int nb);
int my_show_word_array(char const **tab);
char **my_str_to_word_array(char const *str, char const *sep);
int my_put_nbr(int nb);
char *my_strdup(char const *src);
int check_negative(char const *str);
int check_overflow(int new_nbr);
void hardcoded(void);
void char_swap(char *a, char *b);
int swapping_values(int *array, int j, int is_swapped);
int is_lower(char c);
int is_letter(char c);
int is_num(char c);
int is_upper(char c);
int is_alphanum(char c);
int *count_word_lengths(char const *str, int word_count);
int count_words(char const *str);
int is_alphanumeric(char c);
char *my_strcapitalize_bis(char *str, int i);
int compare_logic(char *str, char const *to_find, int i);
int my_printf(char const *format, ...);
int my_put_nbr_printf(va_list params, formatting_t *formatting);
int space_flag(formatting_t *formatting, int number);
int left_padding_putnbr(int total, formatting_t *formatting,
    int padding_chars);
int zero_padding(int *number, formatting_t *formatting, int total,
    int *padding_chars);
int space_padding(int total, formatting_t *formatting, int padding_chars);
int put_nbr_printf(int nb, int prev_count, formatting_t *formatting,
    int is_display);
int my_putstr_printf(va_list params, formatting_t *formatting);
int my_putchar_printf(va_list params, formatting_t *formatting);
int my_print_percent_printf(va_list params, formatting_t *formatting);
int my_decimal_to_base(unsigned long long number, int base, char c, int
    display);
int my_decimal_to_base_printf(va_list params, formatting_t *formatting);
int print_current_chars(va_list params, formatting_t *formatting);
int my_put_float(double number, int precision, char c, int is_display);
int my_sci_notation(double number, char e, int precision, int is_display);
int my_put_float_printf(va_list params, formatting_t *formatting);
int my_strncmp_printf(char const *s1, char const *s2, int n);
void get_formatting(char const *format, int *i, formatting_t *formatting,
    va_list params);
int get_width(char const *format, int *i);
int my_put_unsigned_nbr(long long unsigned int nb, int prev_count);
int my_put_unsigned_nbr_printf(va_list params, formatting_t *formatting);
int my_sci_notation_printf(va_list params, formatting_t *formatting);
int my_put_pointer_printf(va_list params, formatting_t *formatting);
int flag_g(double number, int precision, char e, int hashtag);
int flag_g_printf(va_list params, formatting_t *formatting);
int hardcode(double number, int precision, int hashtag, char e);
int flag_g_bis_with_hashtag(double number, int precision, int hashtag, char e);
int flag_g_bis_no_hashtag(double number, int precision, int hashtag, char e);
int space_formatting_g(int total_chars, int padding_chars,
    formatting_t *formatting);
void zero_padding_g(formatting_t *formatting, int total_chars,
    int *padding_chars, double *value);
int flag_a(double number, int precision, char caps);
int count_digits(int nb);
void my_putstr_err(char const *str);
#endif
