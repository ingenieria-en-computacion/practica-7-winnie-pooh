#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// ----------------------------
// Macro para declarar estructuras y prototipos
// ----------------------------
#define DECLARE_CIRCULAR_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    Node_##TYPE* node_##TYPE##__create(TYPE); \
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##_destroy(List_##TYPE* list); \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data); \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE));

// ----------------------------
// Macro para implementación
// ----------------------------
#define IMPLEMENT_CIRCULAR_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##__create(TYPE data) { \
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        new_node->data = data; \
        new_node->next = NULL; \
        return new_node; \
    } \
    \
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        list->head = NULL; \
        list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    \
    void list_##TYPE##_destroy(List_##TYPE* list) { \
        if (list == NULL) return; \
        Node_##TYPE* current = list->head; \
        if (current != NULL) { \
            Node_##TYPE* temp; \
            do { \
                temp = current->next; \
                free(current); \
                current = temp; \
            } while (current != list->head); \
        } \
        free(list); \
    } \
    \
    bool list_##TYPE##_append(List_##TYPE* list, TYPE data) { \
        Node_##TYPE* new_node = node_##TYPE##__create(data); \
        if (new_node == NULL) return false; \
        \
        if (list->head == NULL) { \
            list->head = new_node; \
            list->tail = new_node; \
            new_node->next = new_node; \
        } else { \
            new_node->next = list->head; \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    \
    void list_##TYPE##_print(const List_##TYPE* list, void (*print_fn)(TYPE)) { \
        if (list == NULL || list->head == NULL) return; \
        Node_##TYPE* current = list->head; \
        printf("Circular List (%zu elements): [", list->length); \
        do { \
            print_fn(current->data); \
            current = current->next; \
            if (current != list->head) printf(", "); \
        } while (current != list->head); \
        printf("]\n"); \
    }
