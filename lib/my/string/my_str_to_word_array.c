/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** my_str_to_word_array
*/

#include "../../Headers/my.h"
#include <stdlib.h>
#include <unistd.h>

static int check_inputs(char const *str, char const *sep)
{
    if (!str) {
        write_error("ERROR: my_str_to_word_array: NULL string\n");
        return -1;
    }
    if (!sep) {
        write_error("ERROR: my_str_to_word_array: NULL separator\n");
        return -1;
    }
    if (sep[0] == '\0') {
        write_error("ERROR: my_str_to_word_array: empty separator\n");
        return -1;
    }
    return 0;
}

static int is_separator(char c, char const *sep)
{
    for (int i = 0; sep[i] != '\0'; i++) {
        if (c == sep[i])
            return 1;
    }
    return 0;
}

int count_words(char const *str, char const *sep)
{
    int in_word = 0;
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (!is_separator(str[i], sep) && !in_word) {
            in_word = 1;
            count++;
        }
        if (is_separator(str[i], sep) && in_word)
            in_word = 0;
    }
    return count;
}

static int word_len(char const *str, char const *sep)
{
    int len = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_separator(str[i], sep))
            break;
        len++;
    }
    return len;
}

static char *dup_word(char const *src, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));

    if (!word) {
        write_error("ERROR: dup_word: malloc failure\n");
        return NULL;
    }
    for (int i = 0; i < len; i++)
        word[i] = src[i];
    word[len] = '\0';
    return word;
}

static void free_word_array(char **arr, int filled)
{
    for (int i = 0; i < filled; i++) {
        if (arr[i])
            free(arr[i]);
    }
    free(arr);
}

static char **alloc_array(int n)
{
    char **arr = malloc(sizeof(char *) * (n + 1));

    if (!arr) {
        write_error("ERROR: alloc_array: malloc failure\n");
        return NULL;
    }
    for (int i = 0; i <= n; i++)
        arr[i] = NULL;
    return arr;
}

static int skip_seps(char const *str, char const *sep)
{
    int i = 0;

    while (str[i] != '\0' && is_separator(str[i], sep))
        i++;
    return i;
}

static char **fill_array(char const *str, char **arr,
    char const *sep, int n)
{
    int pos = 0;
    int len;

    for (int w = 0; w < n; w++) {
        pos += skip_seps(str + pos, sep);
        len = word_len(str + pos, sep);
        if (len <= 0) {
            write_error("ERROR: fill_array: word_len failure\n");
            free_word_array(arr, w);
            return NULL;
        }
        arr[w] = dup_word(str + pos, len);
        if (!arr[w]) {
            free_word_array(arr, w);
            return NULL;
        }
        pos += len;
    }
    arr[n] = NULL;
    return arr;
}

char **my_str_to_word_array(char const *str, char const *sep)
{
    char **arr;
    int n;

    if (check_inputs(str, sep) == -1)
        return NULL;
    n = count_words(str, sep);
    if (n == -1)
        return NULL;
    arr = alloc_array(n);
    if (!arr)
        return NULL;
    return fill_array(str, arr, sep, n);
}
