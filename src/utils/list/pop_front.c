/*
** EPITECH PROJECT, 2025
** bootstrap
** File description:
** pop_front
*/

#include "../../../include/corewar.h"

void pop_front(node_t **head)
{
    node_t *to_delete;

    if (*head == NULL)
        return;
    to_delete = *head;
    *head = (*head)->next;
    free(to_delete);
}
