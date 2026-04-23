/*
** EPITECH PROJECT, 2025
** strdup
** File description:
** strdup
*/

#include <stdlib.h>
#include <unistd.h>
#include "../../Headers/my.h"

char *my_strdup(char const *src, int add)
{
    int i;
    char *dest;

    if (src == NULL)
        return NULL;
    i = my_strlen(src);
    dest = malloc(sizeof(char) * (i + 1) + add);
    if (dest == NULL) {
        write(2, "MALLOC FAILURE\n", 15);
        return NULL;
    }
    my_strcpy(dest, src);
    return (dest);
}
