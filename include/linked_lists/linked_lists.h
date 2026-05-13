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
#endif
