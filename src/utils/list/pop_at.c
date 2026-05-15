/*
** EPITECH PROJECT, 2025
** bootstrap
** File description:
** pop_choosen
*/

#include "../../../include/corewar.h"

void pop_at(node_t **head, int pos)
{
    node_t *temp = *head;
    node_t *to_delete;

    if (*head == NULL)
        return;
    if (pos == 0) {
        pop_front(head);
        return;
    }
    for (int i = 0; temp != NULL && i < pos - 1; i++)
        temp = temp->next;
    if (temp == NULL || temp->next == NULL)
        return;
    to_delete = temp->next;
    temp->next = to_delete->next;
    free(to_delete);
}
