/* SAVU Paul Cristian - 311CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct for a node
typedef struct node {
    T value;
    struct node *next;
    struct node *prev;
} Node, *TList;

// struct for a list
typedef struct list {
    Node *sentinel;
    Node *first;
    Node *last;
    Node *crt;
} List;

// creating a new node
TList createNode(T value) {
    TList node = malloc(sizeof(Node));
    node->next = NULL;
    node->prev = NULL;
    node->value = value;
    return node;
}

TList initList() {
    TList sentinel = calloc(1, sizeof(Node));
    return sentinel;
}

// creates the list (banda magica)
List *createList(TList sentinel) {
    List *list = malloc(sizeof(struct list));
    TList head = createNode('#');
    list->sentinel = sentinel;
    list->sentinel->next = head;
    head->prev = list->sentinel;
    list->crt = head;
    list->first = list->last = head;
    return list;
}

// deallocates the memory of the list
List *freeList(List *list) {
    if (list == NULL) {
        return list;
    }
    Node *iter, *temp;
    iter = list->sentinel;
    while (iter != NULL) {
        temp = iter;
        iter = iter->next;
        free(temp);
    }
    free(list);
    return NULL;
}

/******************************************
----IMPLEMENTATION OF UPDATE OPERATIONS----
******************************************/

// MOVE_LEFT operation
void MOVE_LEFT(List *list, int *moving) {
    TList crt_node = list->crt;

    // checks if crt->node is the first
    if (crt_node->prev != list->sentinel) {
        list->crt = crt_node->prev;
        *moving = 1;
    } else {
        *moving = 0;
    }
}

// crt cell is the last one & MOVE_RIGHT(_CHAR) is called
void addRight(List *list) {
    TList node = createNode('#');
    node->prev = list->last;
    node->next = NULL;
    list->last->next = node;
    list->last = node;
} 

// MOVE_RIGHT operation
void MOVE_RIGHT(List *list) {
    TList crt_node = list->crt;
    if (crt_node != list->last) {
        list->crt = crt_node->next;
    } else {
        addRight(list);
        list->crt = list->last;
    }
}

// MOVE_LEFT_CHAR <C> operation
void MOVE_LEFT_CHAR(T value, List *list, int *moving, FILE* ptr2) {
    TList iterator = list->crt;
    while (iterator->value != value) {
        iterator = iterator->prev;
        if (iterator == list->sentinel) {
            *moving = 0;
            fprintf(ptr2, "ERROR\n");
            return;
        }
    }
    *moving = 1;
    list->crt = iterator;
}

// MOVE_RIGHT_CHAR <C> operation
void MOVE_RIGHT_CHAR(T value, List *list) {
    TList iterator = list->crt;
    while (iterator->value != value) {
        if (iterator == list->last) {
            addRight(list);
            list->crt = list->last;
            return;
        }
        iterator = iterator->next;
    }
    list->crt = iterator;
}

// WRITE <C> operation
void WRITE(T value, List *list) {
    list->crt->value = value;
}

// INSERT_LEFT <C> operation
void INSERT_LEFT(T value, List *list, FILE *ptr2) {
    if (list->crt == list->first) {
        fprintf(ptr2, "ERROR\n");
        return;
    }
    // aux = node for reestablishing the connections among cells
    TList aux = list->crt->prev;
    TList node = createNode(value);
    node->next = list->crt;
    node->prev = aux;
    aux->next = node;
    list->crt->prev = node;
    list->crt = node;
}

// INSERT_RIGHT <C> operation
void INSERT_RIGHT(T value, List *list, FILE *ptr2) {
    if (list->crt == list->last) {
        addRight(list);
        list->last->value = value;
        list->crt = list->last;
        return;
    }
    TList aux = list->crt->next;
    TList node = createNode(value);
    node->next = aux;
    node->prev = list->crt;
    list->crt->next = node;
    aux->prev = node;
    list->crt = node;
}

/*****************************************
----IMPLEMENTATION OF QUERY OPERATIONS----
*****************************************/

// SHOW_CURRENT operation
void SHOW_CURRENT(List *list, FILE *ptr2) {
    fprintf(ptr2, "%c\n", list->crt->value);
}

// SHOW operation
void SHOW(List* list, FILE *ptr2) {
    TList iterator = list->first;
    while (iterator != NULL) {
        if (iterator == list->crt) {
            fprintf(ptr2, "|%c|", iterator->value);
        } else {
            fprintf(ptr2, "%c", iterator->value);
        }
        iterator = iterator->next;
    }
    fprintf(ptr2, "\n");
}