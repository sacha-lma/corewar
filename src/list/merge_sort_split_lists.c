/*
** EPITECH PROJECT, 2025
** organized
** File description:
** merge_sort_list
*/

#include "../../include/corewar.h"

node_t *merge_sort_lists(node_t **head, int (*cmp_func)(void *, void *))
{
    node_t *midle;
    node_t *left;
    node_t *right;

    if (head == NULL || (*head)->next == NULL)
        return *head;
    midle = get_to_middle(*head);
    left = *head;
    right = midle->next;
    midle->next = NULL;
    left = merge_sort_lists(&left, cmp_func);
    right = merge_sort_lists(&right, cmp_func);
    return merge_sort_merge_list(left, right, cmp_func);
}
