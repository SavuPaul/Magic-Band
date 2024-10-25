/* SAVU Paul Cristian - 311CD */

// struct for UNDO / REDO stacks
typedef struct stack {
    void *data;
    struct stack *next;
} *TStack;

// initialises the stack
TStack initStack(void *data) {
    TStack s = malloc(sizeof(struct stack));
    s->data = data;
    s->next = NULL;
    return s;
}

// initialises an empty stack
TStack initS() {
    return NULL;
}

// checks if stack is empty
int isEmpty(TStack s) {
    if (s == NULL) {
        return 1;
    }
    return 0;
}

// adds a new operation to the stack
TStack push(TStack s, TList data) {
    TStack top;
    if (isEmpty(s)) {
        return initStack(data);
    }
    top = initStack(data);
    top->next = s;
    return top;
}

// removes the element from the top of the stack
TStack pop(TStack s) {
    TStack tmp;
    if (isEmpty(s)) {
        return s;
    }
    tmp = s;
    s = s->next;
    free(tmp);
    return s;
}

// returns the value from the top of the stack
TList top(TStack s) {
    if (isEmpty(s)) {
        exit(1);
    }
    return s->data;
}

// deallocates the memory of the stack
TStack freeStack(TStack s) {
    while (!isEmpty(s)) {
        s = pop(s);
    }
    return NULL;
}