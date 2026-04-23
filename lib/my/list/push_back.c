/*
** EPITECH PROJECT, 2025
** bootstrap
** File description:
** push_back
*/

#include <stdlib.h>
#include <unistd.h>
#include "../../Headers/linked_lists.h"

void push_back(node_t **head, void *data)
{
    node_t *new_node;
    node_t *temp;

    if (head == NULL)
        return;
    new_node = malloc(sizeof(node_t));
    if (new_node == NULL) {
        write(2, "MALLOC FAILURE\n", 15);
        return;
    }
    new_node->data = data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    temp = *head;
    for (; temp->next != NULL; temp = temp->next);
    temp->next = new_node;
}
