#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Initial capacity for the dynamic stack
#define INITIAL_CAPACITY 5

// Stack structure definition using a dynamic array
typedef struct Stack
{
    int *array;   // Pointer to the dynamic array holding stack elements
    int capacity; // Current capacity of the stack array
    int top;      // Index of the top element (-1 indicates an empty stack)
} Stack;

// Function to create and initialize a stack with a given capacity
Stack *createStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        printf("Memory allocation for stack structure failed.\n");
        exit(1);
    }
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(capacity * sizeof(int));
    if (!stack->array)
    {
        printf("Memory allocation for stack array failed.\n");
        free(stack);
        exit(1);
    }
    return stack;
}

// Check if the stack is empty
bool isEmpty(Stack *stack)
{
    return (stack->top == -1);
}

// Check if the stack is full (before resizing)
bool isFull(Stack *stack)
{
    return (stack->top == stack->capacity - 1);
}

// Function to auto-resize the stack when it is full
void resizeStack(Stack *stack)
{
    int newCapacity = stack->capacity * 2;
    int *newArray = (int *)realloc(stack->array, newCapacity * sizeof(int));
    if (!newArray)
    {
        printf("Stack resizing failed due to memory allocation error.\n");
        free(stack->array);
        free(stack);
        exit(1);
    }
    stack->array = newArray;
    stack->capacity = newCapacity;
    printf("Stack resized: new capacity is %d.\n", stack->capacity);
}

// Push an element onto the stack (with automatic resizing if needed)
void push(Stack *stack, int data)
{
    if (isFull(stack))
    {
        printf("Stack is full. Resizing before pushing new element...\n");
        resizeStack(stack);
    }
    stack->array[++(stack->top)] = data;
    printf("Pushed %d onto the stack.\n", data);
}

// Pop an element from the stack and return its value
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow! Cannot pop from an empty stack.\n");
        return -1; // Return a sentinel value (could also exit or handle error differently)
    }
    int poppedValue = stack->array[(stack->top)--];
    return poppedValue;
}

// Peek at the top element of the stack without removing it
int peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty! Nothing to peek.\n");
        return -1;
    }
    return stack->array[stack->top];
}

// Display all elements of the stack from top to bottom
void displayStack(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty! Nothing to display.\n");
        return;
    }
    printf("Stack elements (top to bottom):\n");
    for (int i = stack->top; i >= 0; i--)
    {
        printf("%d", stack->array[i]);
        if (i > 0)
        {
            printf(" -> ");
        }
    }
    printf("\n");
}

// Return the current number of elements in the stack
int size(Stack *stack)
{
    return stack->top + 1;
}

// Search for an element in the stack; returns the index if found or -1 otherwise
int searchStack(Stack *stack, int element)
{
    for (int i = stack->top; i >= 0; i--)
    {
        if (stack->array[i] == element)
        {
            return i; // Index position in the array (0 is bottom; top is highest index)
        }
    }
    return -1;
}

// Reverse the order of the stack in place
void reverseStack(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty! Nothing to reverse.\n");
        return;
    }
    int start = 0;
    int end = stack->top;
    while (start < end)
    {
        int temp = stack->array[start];
        stack->array[start] = stack->array[end];
        stack->array[end] = temp;
        start++;
        end--;
    }
    printf("Stack reversed.\n");
}

// Clear the stack by resetting the 'top' index (the allocated memory remains for future use)
void clearStack(Stack *stack)
{
    stack->top = -1;
    printf("Stack cleared.\n");
}

// Free the memory allocated for the stack
void freeStack(Stack *stack)
{
    if (stack)
    {
        free(stack->array);
        free(stack);
    }
}

// Menu-driven interface to interact with the Stack
int main()
{
    Stack *stack = createStack(INITIAL_CAPACITY);
    int choice, value, searchValue, result;

    while (1)
    {
        printf("\n========== Stack Operations Menu ==========\n");
        printf("1. Push an element\n");
        printf("2. Pop an element\n");
        printf("3. Peek at the top element\n");
        printf("4. Display the stack\n");
        printf("5. Get stack size\n");
        printf("6. Clear the stack\n");
        printf("7. Search for an element\n");
        printf("8. Reverse the stack\n");
        printf("9. Exit\n");
        printf("Enter your choice (1-9): ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number between 1 and 9.\n");
            // Clear invalid input
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("Enter the element to push: ");
            if (scanf("%d", &value) != 1)
            {
                printf("Invalid input. Please enter an integer.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            push(stack, value);
            break;

        case 2:
            value = pop(stack);
            if (value != -1)
            { // assuming -1 indicates error / empty stack
                printf("Popped element: %d\n", value);
            }
            break;

        case 3:
            value = peek(stack);
            if (value != -1)
            {
                printf("Top element: %d\n", value);
            }
            break;

        case 4:
            displayStack(stack);
            break;

        case 5:
            printf("Current stack size: %d\n", size(stack));
            break;

        case 6:
            clearStack(stack);
            break;

        case 7:
            printf("Enter the element to search: ");
            if (scanf("%d", &searchValue) != 1)
            {
                printf("Invalid input. Please enter an integer.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            result = searchStack(stack, searchValue);
            if (result != -1)
            {
                printf("Element %d found at index %d (0 = bottom, %d = top).\n", searchValue, result, stack->top);
            }
            else
            {
                printf("Element %d not found in the stack.\n", searchValue);
            }
            break;

        case 8:
            reverseStack(stack);
            displayStack(stack);
            break;

        case 9:
            freeStack(stack);
            printf("Exiting the program. Goodbye!\n");
            exit(0);

        default:
            printf("Invalid choice. Please select an option between 1 and 9.\n");
            break;
        }
    }

    return 0;
}