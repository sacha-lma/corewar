/*
** EPITECH PROJECT, 2026
** organized
** File description:
** merge_sort_merge_list — merges two sorted linked lists with a comparator
*/

#include "../../../include/corewar.h"

node_t *merge_sort_merge_list(node_t *left, node_t *right,
    int (*cmp_func)(void *, void *))
{
    node_t *result = NULL;

    if (left == NULL)
        return right;
    if (right == NULL)
        return left;
    if (cmp_func(left, right) > 0) {
        result = left;
        result->next = merge_sort_merge_list(left->next, right, cmp_func);
    } else {
        result = right;
        result->next = merge_sort_merge_list(left, right->next, cmp_func);
    }
    return result;
}
