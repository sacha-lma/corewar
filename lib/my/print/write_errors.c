/*
** EPITECH PROJECT, 2026
** minishel_2
** File description:
** write_errors
*/

#include "../../Headers/my.h"
#include <unistd.h>

void write_error(const char *msg)
{
    write(2, msg, my_strlen(msg));
}
