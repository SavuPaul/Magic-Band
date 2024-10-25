C-Implementation of a doubly-linked list with a sentinel node on which various operations can be performed.
---
> After implementing the structures and functions for the list, stack, and queue, I included the header files in tema.c.

Functionality
---
First, I read the number of instructions that will be executed. I used a loop (while) to execute each instruction in turn.

According to the examples, I divided the commands into two categories:
* Without any parameters
* With a parameter

Thus, I stored the instruction itself in the "command" variable, and based on its name (using strcmp), I continued reading from the file to store the command's parameter (if it exists) in the "argument" variable.

If the command is a query type, the display function is called based on the content of the "command" variable (SHOW / SHOW_CURRENT). For SHOW_CURRENT, only the character value is displayed at the list->crt position (the "finger"), while for SHOW, I iterate through the entire list, displaying all values and checking if the current position is where the "finger" is, in order to add "| |".

If the command is not a query or execute type, it is added to the queue (enqueue). If it also has a parameter, then the parameter is also added to the queue immediately after the command itself. To simplify things, I associated a number with each command, as follows:

* MOVE_LEFT = 1
* MOVE_RIGHT = 2
* MOVE_LEFT_CHAR <C> = 3
* MOVE_RIGHT_CHAR <C> = 4
* INSERT_LEFT <C> = 5
* INSERT_RIGHT <C> = 6
* WRITE <C> = 7

If the command is "EXECUTE", then I extract the first element from the queue (front) and store the current position in an auxiliary variable (aux) to remember where the "finger" is (in case the command will be a move type). Then, the function "execute_correspondence" is called.

The "execute_correspondence" function maps the operation code (as numbered above) to the corresponding function that needs to be called. After each command is executed, it is removed from the queue (dequeue), along with its parameter (if it has one).

Among the function parameters is "moving," initialized to 0, which has two roles:
* If it becomes 1, it means the move operation was executed successfully;
* If it remains 0, then the move operation was not successful.

We know that the right move operation (MOVE_RIGHT) will always succeed, so moving will become 1 each time it's extracted from the queue. On the other hand, the left move operation cannot be executed if we're at position 1, so we pass the moving variable forward as a parameter to the left move function to check if the operation was successful. If moving is 1 when exiting the function, we can add the address contained in the aux variable to the undo stack.

Another function parameter is writing, initialized to 0, which becomes 1 if the last operation was a write (write or insert left/right). If it becomes 1 after exiting the function, the undo and redo stacks are emptied.

For an undo or redo command, we proceed as explained in the assignment statement, transferring addresses between stacks as needed based on the desired operation.

Finally, the allocated memory is freed.

TEST SCORES:
---
Total: 100.0/100
Valgrind: 20/20
