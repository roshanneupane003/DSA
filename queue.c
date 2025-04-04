#include <stdio.h>
#include <stdlib.h>

// Define structure for a queue node
typedef struct QueueNode
{
    int data;
    struct QueueNode *next;
} QueueNode;

// Define structure for the queue
typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

// Function to create a new node
QueueNode *createQueueNode(int data)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize the queue
Queue *initializeQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue *queue)
{
    return queue->front == NULL;
}

// Function to enqueue an element
void enqueue(Queue *queue, int data)
{
    QueueNode *newNode = createQueueNode(data);
    if (isQueueEmpty(queue))
    {
        queue->front = queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    printf("Enqueued: %d\n", data);
}

// Function to dequeue an element
int dequeue(Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Queue underflow! Cannot dequeue.\n");
        return -1;
    }
    QueueNode *temp = queue->front;
    int dequeuedData = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }
    free(temp);
    return dequeuedData;
}

// Function to peek at the front element
void peek(Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Queue is empty. Nothing to peek.\n");
        return;
    }
    printf("Front element is: %d\n", queue->front->data);
}

// Function to traverse the queue
void traverseQueue(Queue *queue)
{
    if (isQueueEmpty(queue))
    {
        printf("Queue is empty.\n");
        return;
    }
    QueueNode *temp = queue->front;
    printf("Queue elements:\n");
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to clear the queue
void clearQueue(Queue *queue)
{
    while (!isQueueEmpty(queue))
    {
        dequeue(queue);
    }
    free(queue);
    printf("Queue cleared and memory released.\n");
}

// Main function
int main()
{
    Queue *queue = initializeQueue();

    // Example operations
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    printf("Queue after enqueuing elements:\n");
    traverseQueue(queue);

    peek(queue);

    int dequeuedData = dequeue(queue);
    printf("Dequeued element: %d\n", dequeuedData);

    printf("Queue after dequeuing an element:\n");
    traverseQueue(queue);

    clearQueue(queue);

    return 0;
}