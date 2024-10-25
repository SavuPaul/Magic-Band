/* SAVU Paul Cristian - 311CD */

// structs for EXECUTE queue
typedef struct cell {
    char *operation;
    struct cell *next;
} Cell;

typedef struct queue {
    Cell *head, *tail;
    int size;
} *TQueue;

// initialises a cell
Cell *initCell(char *operation) {
    Cell *cell = malloc(sizeof(struct cell));
    cell->operation = operation;
    cell->next = NULL;
    return cell;
}

// deallocates a cell
void *freeCell(Cell *cell) {
    if (cell) {
        free(cell);
    }
    return NULL;
}

// initialises a queue
TQueue initQueue(char *operation) {
    TQueue queue = malloc(sizeof(struct queue));
    queue->head = queue->tail = initCell(operation);
    queue->size = 1;
    return queue;
}

// initialises an empty queue
TQueue init() {
    return NULL;
}

// checks if the queue is empty
int isEmptyQueue(TQueue queue) {
    return queue == NULL || queue->head == NULL || queue->size == 0;
}

// adds a new element to the queue (at the end)
TQueue enqueue(TQueue queue, char *operation) {
    Cell *cell;
    if (isEmptyQueue(queue)) {
        if (queue == NULL) {
            return initQueue(operation);
        }
        free(queue);
        return initQueue(operation);
    }
    cell = initCell(operation);
    queue->tail->next = cell;
    queue->tail = cell;
    queue->size++;
    return queue;
}

// removes an element from the queue (from the start)
TQueue dequeue(TQueue queue) {
    Cell *tmp;
    if (!isEmptyQueue(queue)) {
        tmp = queue->head;
        queue->head = queue->head->next;
        freeCell(tmp);
        queue->size--;
    }
    return queue;
}

// returns the front element from the queue
char *front(TQueue queue) {
    if (!isEmptyQueue(queue)) {
        return queue->head->operation;
    } else {
        exit(1);
    }
}

// deallocates the memory of the queue
TQueue freeQueue(TQueue queue) {
    while (!isEmptyQueue(queue)) {
        queue = dequeue(queue);
    }
    if (queue) {
        free(queue);
    }
    return NULL;
}