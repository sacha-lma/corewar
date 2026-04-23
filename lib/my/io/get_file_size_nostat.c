/*
** EPITECH PROJECT, 2025
** RADAR
** File description:
** get_file_size_nostat
*/

#include <fcntl.h>
#include <unistd.h>
#include "../../Headers/my.h"

int get_file_size_no_stat(char const *filepath)
{
    int size = 0;
    char buffer[KB];
    int fd;

    if (filepath == NULL) {
        write(2, "NULL FILEPATH\n", 14);
        return FAILURE;
    }
    fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        write(2, "OPEN FAILURE\n", 13);
        return FAILURE;
    }
    while (read(fd, buffer, 1) > 0)
        size++;
    close(fd);
    return size;
}
