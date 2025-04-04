#include <stdio.h>
#include <stdlib.h>

// Define structure for a linked list node
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Function to create a new node
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning
Node *insertAtBeginning(Node *head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// Function to insert a node at the end
Node *insertAtEnd(Node *head, int data)
{
    Node *newNode = createNode(data);
    if (head == NULL)
    {
        return newNode;
    }
    Node *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

// Function to insert a node at a specific position
Node *insertAtPosition(Node *head, int data, int position)
{
    Node *newNode = createNode(data);
    if (position == 1)
    {
        newNode->next = head;
        return newNode;
    }
    Node *temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Position out of bounds.\n");
        free(newNode);
        return head;
    }
    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

// Function to delete a node from the beginning
Node *deleteFromBeginning(Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }
    Node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

// Function to delete a node from the end
Node *deleteFromEnd(Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }
    if (head->next == NULL)
    {
        free(head);
        return NULL;
    }
    Node *temp = head;
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    return head;
}

// Function to delete a node at a specific position
Node *deleteAtPosition(Node *head, int position)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return NULL;
    }
    if (position == 1)
    {
        Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    Node *temp = head;
    for (int i = 1; i < position - 1 && temp != NULL; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
    {
        printf("Position out of bounds.\n");
        return head;
    }
    Node *deleteNode = temp->next;
    temp->next = deleteNode->next;
    free(deleteNode);
    return head;
}

// Function to traverse and print the linked list
void traverseList(Node *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to search for an element in the linked list
void searchElement(Node *head, int key)
{
    Node *temp = head;
    int position = 1;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            printf("Element %d found at position %d.\n", key, position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Element %d not found in the list.\n", key);
}

// Function to reverse the linked list
Node *reverseList(Node *head)
{
    Node *prev = NULL, *current = head, *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Main function
int main()
{
    Node *head = NULL;

    // Example operations
    head = insertAtBeginning(head, 10);
    head = insertAtEnd(head, 20);
    head = insertAtPosition(head, 15, 2);

    printf("Linked List after insertion:\n");
    traverseList(head);

    head = deleteFromBeginning(head);
    head = deleteFromEnd(head);

    printf("Linked List after deletion:\n");
    traverseList(head);

    head = insertAtEnd(head, 30);
    head = insertAtEnd(head, 40);
    searchElement(head, 30);

    head = reverseList(head);
    printf("Reversed Linked List:\n");
    traverseList(head);

    return 0;
}