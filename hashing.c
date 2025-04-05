#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the size of the hash table
#define TABLE_SIZE 10

// Define a structure for hash table nodes
typedef struct Node
{
    int key;
    char value[100];
    struct Node *next;
} Node;

// Create a hash table
Node *hashTable[TABLE_SIZE];

// Function to generate a hash code
int hashCode(int key)
{
    return key % TABLE_SIZE;
}

// Function to insert a key-value pair into the hash table
void insert(int key, char *value)
{
    int index = hashCode(key);
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->value, value);
    newNode->next = NULL;

    if (hashTable[index] == NULL)
    {
        hashTable[index] = newNode;
    }
    else
    {
        Node *temp = hashTable[index];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Inserted key %d with value '%s' at index %d\n", key, value, index);
}

// Function to search for a key in the hash table
void search(int key)
{
    int index = hashCode(key);
    Node *temp = hashTable[index];
    while (temp != NULL)
    {
        if (temp->key == key)
        {
            printf("Key %d found with value '%s'\n", key, temp->value);
            return;
        }
        temp = temp->next;
    }
    printf("Key %d not found\n", key);
}

// Function to delete a key from the hash table
void delete(int key)
{
    int index = hashCode(key);
    Node *temp = hashTable[index];
    Node *prev = NULL;

    while (temp != NULL && temp->key != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Key %d not found for deletion\n", key);
        return;
    }

    if (prev == NULL)
    {
        hashTable[index] = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    free(temp);
    printf("Key %d deleted from index %d\n", key, index);
}

// Main function to demonstrate the hashing operations
int main()
{
    // Initialize the hash table
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i] = NULL;
    }

    // Insert key-value pairs
    insert(10, "Alice");
    insert(20, "Bob");
    insert(30, "Charlie");
    insert(40, "Dave");
    insert(15, "Eve");

    // Search for keys
    search(20);
    search(25);

    // Delete a key
    delete (30);

    // Search again after deletion
    search(30);

    return 0;
}