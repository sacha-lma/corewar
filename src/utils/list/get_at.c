/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** get_at — returns the data pointer at a given index in a linked list
*/

#include "../../../include/corewar.h"

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
