/*
** EPITECH PROJECT, 2026
** G-AIA-200-NCE-2-1-cuddle-5
** File description:
** Utility function prototypes for string, math, memory and I/O operations
*/
/**
 * @file my.h
 * @brief Function prototypes for string, math, memory and I/O utilities
 * @author Sacha Le Moign-Avalos && Erwan Lo Presti
 */

#ifndef LIB_H
    #define LIB_H

    #include "defines.h"
    #include "linked_lists.h"
    #include <stdlib.h>
int my_strlen(char const *str);
int my_strcmp(char *s1, char *s2);
char *my_strdup(char const *src, int add);
char *my_strndup(char const *src, int n);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
int my_str_isnum(char const *str);
int my_getnbr(char const *str);
char **my_str_to_word_array(char const *str, char const *separator);
void free_array(char **array);
int get_file_size_no_stat(char const *filepath);
char *openator(char const *filepath);
void write_error(const char *msg);
char ***my_str_to_array_of_word_array(char const *str, char const *sep_ext,
    char const *sep_int);
int count_words(char const *str, char const *sep);
void free_array_of_word_arrays(char ***arr);

#endif
