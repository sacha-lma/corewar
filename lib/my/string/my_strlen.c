/*
** EPITECH PROJECT, 2025
** my_strlen
** File description:
** it's a function that displayes the len
*/

#include "../../Headers/my.h"

int my_strlen(char const *str)
{
    int i;

    if (str == NULL)
        return 0;
    for (i = 0; str[i] != '\0';)
        i++;
    return i;
}
