/*
** EPITECH PROJECT, 2026
** minishell_2
** File description:
** str_to_array_of_word_array
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../Headers/my.h"

static int my_strcspn(char const *str, char const *reject)
{
    int i;
    int j;

    for (i = 0; str[i]; i++)
        for (j = 0; reject[j]; j++)
            if (str[i] == reject[j])
                return i;
    return i;
}

static int my_strspn(char const *str, char const *accept)
{
    int i;
    int j;
    int found;

    for (i = 0; str[i]; i++) {
        found = 0;
        for (j = 0; accept[j]; j++)
            if (str[i] == accept[j]) {
                found = 1;
                break;
            }
        if (!found)
            return i;
    }
    return i;
}

static int check_inputs(char const *str, char const *sep, const char *label)
{
    if (!str) {
        write_error("ERROR: ");
        write_error(label);
        write_error(": NULL string\n");
        return -1;
    }
    if (!sep) {
        write_error("ERROR: ");
        write_error(label);
        write_error(": NULL separator\n");
        return -1;
    }
    if (sep[0] == '\0') {
        write_error("ERROR: ");
        write_error(label);
        write_error(": empty separator\n");
        return -1;
    }
    return 0;
}

static void free_array_of_word_array(char ***arr, int filled)
{
    int i;

    if (!arr)
        return;
    for (i = 0; i < filled; i++) {
        if (arr[i])
            free_array(arr[i]);
    }
    free(arr);
}

static char *dup_segment(char const *str, int len)
{
    char *seg;

    if (!str || len < 0) {
        write_error("ERROR: dup_segment: invalid input\\n");
        return NULL;
    }
    seg = malloc(sizeof(char) * (len + 1));
    if (!seg) {
        write_error("ERROR: dup_segment: malloc failure\n");
        return NULL;
    }
    for (int i = 0; i < len; i++)
        seg[i] = str[i];
    seg[len] = '\0';
    return seg;
}

static char **fill_slot(char const *str, char const *sep_ext,
    char const *sep_int)
{
    char **slot;
    char *seg;
    int len;

    if (!str || !sep_ext || !sep_int) {
        write_error("ERROR: fill_slot: invalid input\\n");
        return NULL;
    }
    len = my_strcspn(str, sep_ext);
    seg = dup_segment(str, len);
    if (!seg)
        return NULL;
    slot = my_str_to_word_array(seg, (char *)sep_int);
    free(seg);
    if (!slot)
        write_error("ERROR: fill_slot: my_str_to_word_array failure\n");
    return slot;
}

static char ***loop_filling(char ***arr, char const *str,
    char const *sep_ext, char const *sep_int)
{
    int n = count_words(str, sep_ext);
    int i;

    if (!arr || !str || !sep_ext || !sep_int) {
        write_error("ERROR: loop_filling: invalid input\\n");
        free_array_of_word_array(arr, 0);
        return NULL;
    }
    str += my_strspn(str, sep_ext);
    for (i = 0; i < n; i++) {
        arr[i] = fill_slot(str, sep_ext, sep_int);
        if (!arr[i]) {
            free_array_of_word_array(arr, i);
            return NULL;
        }
        str += my_strcspn(str, sep_ext);
        str += my_strspn(str, sep_ext);
    }
    arr[n] = NULL;
    return arr;
}

static char ***alloc_array(int n)
{
    char ***arr;

    if (n < 0) {
        write_error("ERROR: alloc_array: invalid size\\n");
        return NULL;
    }
    arr = malloc(sizeof(char **) * (size_t)(n + 1));
    if (!arr) {
        write_error("ERROR: alloc_array: malloc failure\n");
        return NULL;
    }
    for (int i = 0; i <= n; i++)
        arr[i] = NULL;
    return arr;
}

char ***my_str_to_array_of_word_array(char const *str, char const *sep_ext,
    char const *sep_int)
{
    char ***arr;
    int n;

    if (check_inputs(str, sep_ext, "my_str_to_array_of_word_array") == -1)
        return NULL;
    if (check_inputs(str, sep_int, "my_str_to_array_of_word_array") == -1)
        return NULL;
    n = count_words(str, sep_ext);
    if (n == 0) {
        write_error("ERROR: my_str_to_array_of_word_array: no words found\n");
        return NULL;
    }
    arr = alloc_array(n);
    if (!arr)
        return NULL;
    return loop_filling(arr, str, sep_ext, sep_int);
}
