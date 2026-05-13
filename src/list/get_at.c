/*
** EPITECH PROJECT, 2025
** bootstrap
** File description:
** get_at
*/

#include "../../include/corewar.h"

void *get_at(node_t *head, int pos)
{
    int i = 0;

    if (pos < 0)
        return (NULL);
    for (; head != NULL && i < pos; head = head->next) {
        i++;
    }
    if (head == NULL)
        return (NULL);
    return (head->data);
}
