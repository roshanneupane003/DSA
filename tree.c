#include <stdio.h>
#include <stdlib.h>

// Structure for tree nodes
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Helper function to create a new node
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Binary Tree Traversals
void inorder(Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Insert into a Binary Search Tree
Node *insertBST(Node *root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }
    if (data < root->data)
    {
        root->left = insertBST(root->left, data);
    }
    else
    {
        root->right = insertBST(root->right, data);
    }
    return root;
}

// Search in a Binary Search Tree
Node *searchBST(Node *root, int key)
{
    if (root == NULL || root->data == key)
    {
        return root;
    }
    if (key < root->data)
    {
        return searchBST(root->left, key);
    }
    else
    {
        return searchBST(root->right, key);
    }
}

// Check height of the tree (used for AVL balance check)
int height(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Check if a tree is balanced (AVL property demonstration)
int isBalanced(Node *root)
{
    if (root == NULL)
    {
        return 1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    int balanceFactor = abs(leftHeight - rightHeight);

    return balanceFactor <= 1 && isBalanced(root->left) && isBalanced(root->right);
}

// Main function to demonstrate tree operations
int main()
{
    Node *root = NULL;

    // Insert nodes into BST
    root = insertBST(root, 50);
    root = insertBST(root, 30);
    root = insertBST(root, 70);
    root = insertBST(root, 20);
    root = insertBST(root, 40);
    root = insertBST(root, 60);
    root = insertBST(root, 80);

    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");

    // Search for a key in BST
    int key = 40;
    Node *searchResult = searchBST(root, key);
    if (searchResult != NULL)
    {
        printf("Key %d found in BST.\n", key);
    }
    else
    {
        printf("Key %d not found in BST.\n", key);
    }

    // Check if the tree is balanced
    if (isBalanced(root))
    {
        printf("The tree is balanced.\n");
    }
    else
    {
        printf("The tree is not balanced.\n");
    }

    return 0;
}