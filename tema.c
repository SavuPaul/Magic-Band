/* SAVU Paul Cristian - 311CD */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char T;

#include "doubleLinkedList.h"
#include "stack.h"
#include "queue.h"

#define SIZE 100

// makes the correspondence between the operation and its code
void execute_correspondence(char *op, List *list, 
TQueue queue, int *moving, int *writing, FILE *ptr2) {
    
    /* MOVE_LEFT = 1
    MOVE_RIGHT = 2
    MOVE_LEFT_CHAR <C> = 3
    MOVE_RIGHT_CHAR <C> = 4
    INSERT_LEFT <C> = 5
    INSERT_RIGHT <C> = 6
    WRITE <C> = 7 */

    char parameter;

    if (op == "1") {
        // 'moving' changes value in MOVE_LEFT function
        MOVE_LEFT(list, moving);
        queue = dequeue(queue);
        return;
    }

    if (op == "2") {
        *moving = 1;
        MOVE_RIGHT(list);
        queue = dequeue(queue);
        return;
    }

    if (op[0] == '3') {
        queue = dequeue(queue);
        parameter = *(front(queue));
        // 'moving' changes value in MOVE_LEFT_CHAR function
        MOVE_LEFT_CHAR(parameter, list, moving, ptr2);
        queue = dequeue(queue);
        return;
    }

    if (op[0] == '4') {
        *moving = 1;
        queue = dequeue(queue);
        parameter = *(front(queue));
        MOVE_RIGHT_CHAR(parameter, list);
        queue = dequeue(queue);
        return;
    }

    if (op[0] == '5') {
        *writing = 1;
        queue = dequeue(queue);
        parameter = *(front(queue));
        INSERT_LEFT(parameter, list, ptr2);
        queue = dequeue(queue);
        return;
    }

    if (op[0] == '6') {
        *writing = 1;
        queue = dequeue(queue);
        parameter = *(front(queue));
        INSERT_RIGHT(parameter, list, ptr2);
        queue = dequeue(queue);
        return;
    }

    if (op[0] == '7') {
        *writing = 1;
        queue = dequeue(queue);
        parameter = *(front(queue));
        WRITE(parameter, list);
        queue = dequeue(queue);
        return;
    }
}

int main() {
    FILE* ptr1, *ptr2;

    // creates the list
    TList sentinel = initList();
    List *list = createList(sentinel);

    // creates the queue
    TQueue queue = init();

    // creates the 2 stacks
    TStack undo = initS();
    TStack redo = initS();

    // node that helps with undo / redo
    TList aux = NULL;

    // Opening file in reading mode
    ptr1 = fopen("tema1.in", "r");
    ptr2 = fopen("tema1.out", "w");

    // reads the number of instructions
    int instructions = 0;
    fscanf(ptr1, "%d", &instructions);
    
    // executes the instructions
    char *command = malloc(SIZE * sizeof(command));
    char *argument = malloc(SIZE * sizeof(argument));
    int i = 0, moving = 0, writing = 0;

    while (instructions > 0) {
        fscanf(ptr1, "%s", command);

        // becomes 1 if the command is of type MOVE
        moving = 0;

        // becomes 1 if the command is of type WRITE
        writing = 0;

        // UNDO operation
        if (strcmp(command, "UNDO") == 0) {
            redo = push(redo, list->crt);
            list->crt = top(undo);
            undo = pop(undo);
        }

        // REDO operation
        if (strcmp(command, "REDO") == 0) {
            undo = push(undo, list->crt);
            list->crt = top(redo);
            redo = pop(redo);
        }

        // QUERY INSTRUCTIONS
        if (strcmp(command, "SHOW") == 0) {
            SHOW(list, ptr2);
        }

        if (strcmp(command, "SHOW_CURRENT") == 0) {
            SHOW_CURRENT(list, ptr2);
        }

        // EXECUTE operation
        if (strcmp(command, "EXECUTE") == 0) {
            char *op = front(queue);
            aux = list->crt;
            execute_correspondence(op, list, queue, &moving, 
            &writing, ptr2);
            if (moving == 1) {
                undo = push(undo, aux);
            }
            if (writing == 1) {
                undo = freeStack(undo);
                redo = freeStack(redo);
            }
        }
        
        // instruction type (with or without parameters) + enqueue
        if (strcmp(command, "MOVE_LEFT") == 0) {
            queue = enqueue(queue, "1");
        }

        if (strcmp(command, "MOVE_RIGHT") == 0) {
            queue = enqueue(queue, "2");
        }

        if (strcmp(command, "MOVE_LEFT_CHAR") == 0) {
            fscanf(ptr1, "%s", &argument[i]);
            queue = enqueue(queue, "3");
            queue = enqueue(queue, &argument[i]);
            i++;
        }

        if (strcmp(command, "MOVE_RIGHT_CHAR") == 0) {
            fscanf(ptr1, "%s", &argument[i]);
            queue = enqueue(queue, "4");
            queue = enqueue(queue, &argument[i]);
            i++;
        }

        if (strcmp(command, "INSERT_LEFT") == 0) {
            fscanf(ptr1, "%s", &argument[i]);
            queue = enqueue(queue, "5");
            queue = enqueue(queue, &argument[i]);
            i++;
        }

        if (strcmp(command, "INSERT_RIGHT") == 0) {
            fscanf(ptr1, "%s", &argument[i]);
            queue = enqueue(queue, "6");
            queue = enqueue(queue, &argument[i]);
            i++;
        }

        if (strcmp(command, "WRITE") == 0) {
            fscanf(ptr1, "%s", &argument[i]);
            queue = enqueue(queue, "7");
            queue = enqueue(queue, &argument[i]);
            i++;
        }

        instructions--;
    }

    // closes the files
    fclose(ptr1);
    fclose(ptr2);

    // frees the allocated memory
    free(argument);
    free(command);
    undo = freeStack(undo);
    redo = freeStack(redo);
    queue = freeQueue(queue);
    list = freeList(list);
    return 0;
}