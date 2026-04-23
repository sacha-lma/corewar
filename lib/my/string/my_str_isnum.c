/*
** EPITECH PROJECT, 2025
** is,um
** File description:
** isnum
*/

#include "../../Headers/my.h"

int my_str_isnum(char const *str)
{
    int i;

    if (str[0] == '\0')
        return FAILURE;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9')
            return FAILURE;
    }
    return SUCCESS;
}
