/*
** EPITECH PROJECT, 2025
** my_getnbr
** File description:
** return a number
*/

#include "../../Headers/my.h"

static int is_num(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return SUCCESS;
}

int my_getnbr(char const *str)
{
    long long int j = 0;
    int signe = 1;
    int a;

    if (!str)
        return 0;
    for (a = 0; is_num(str[a]) == 0 && str[a] != '\0'; a++) {
        if (str[a] == '-')
            signe *= -1;
    }
    for (int i = a; is_num(str[i]) == 1 && str[i] != '\0'; i++) {
        j = (j * 10) + (str[i] - 48);
        if (j * signe > (long long)MAX_INT || j * signe < (long long)MIN_INT)
            return SUCCESS;
    }
    j = j * signe;
    return j;
}
