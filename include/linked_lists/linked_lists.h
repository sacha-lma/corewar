/*
** EPITECH PROJECT, 2026
** G-AIA-200-NCE-2-1-cuddle-5
** File description:
** Linked list node structure and manipulation function prototypes
*/
/**
 * @file linked_lists.h
 * @brief Linked list node structure and manipulation function prototypes
 * @author Sacha Le Moign-Avalos && Erwan Lo Presti
 */

#ifndef LINKED_LISTS_H
    #define LINKED_LISTS_H
typedef struct node_s {
    void *data;
    struct node_s *next;
} node_t;
void push_back(node_t **head, void *data);
node_t *merge_sort_lists(node_t **head, int (*cmp_func)(void *, void *));
node_t *merge_sort_merge_list(node_t *left, node_t *right,
    int (*cmp_func)(void *, void *));
void free_list(node_t **head);
node_t *get_to_middle(node_t *head);
#endif
