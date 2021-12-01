#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Node
{
    int key;
    Node* left;
    Node* right;
    int height;
};

int height(Node* root)
{
    if (root == nullptr)
        return 0;
    else
        return root->height;
}

Node* rightRotate(Node* root)
{
    Node* newNode1 = root->left;
    Node* node2 = newNode1->right;
    newNode1->right = root;
    root->left = node2;

    root->height = max(height(root->left), height(root->right)) + 1;
    newNode1->height = max(height(newNode1->left), height(newNode1->right)) + 1;

    return newNode1;
}

Node* leftRotate(Node* root)
{
    Node* newNode1 = root->right;
    Node* node2 = newNode1->left;
    newNode1->left = root;
    root->right = node2;

    root->height = max(height(root->left), height(root->right)) + 1;
    newNode1->height = max(height(newNode1->left), height(newNode1->right)) + 1;
    return newNode1;
}

int balanceFactor(Node* root)
{
    if (root == nullptr)
        return 0;
    else
        return (height(root->left) - height(root->right));
}

Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node* insert(Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
        height(node->right));
    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void LevelOrder(Node* root, ofstream& output) {
    queue<Node*> q;
    Node* item;
    q.push(root);
    while (!q.empty()) {
        item = q.front();
        output << item->key << " ";
        if (item->left != NULL)
            q.push(item->left);
        if (item->right != NULL)
            q.push(item->right);
        q.pop();
    }
}