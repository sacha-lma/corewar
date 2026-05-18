/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** pop_front — unlinks and frees the head node of a linked list
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
