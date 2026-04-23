/*
** EPITECH PROJECT, 2025
** strndup
** File description:
** strndup
*/

#include <stdlib.h>
#include <unistd.h>
#include "../../Headers/my.h"

char *my_strndup(char const *src, int n)
{
    char *dest;

    if (src == NULL)
        return NULL;
    dest = malloc(sizeof(char) * (n + 1));
    if (dest == NULL) {
        write(2, "MALLOC FAILURE\n", 15);
        return NULL;
    }
    my_strncpy(dest, src, n);
    dest[n] = '\0';
    return (dest);
}
