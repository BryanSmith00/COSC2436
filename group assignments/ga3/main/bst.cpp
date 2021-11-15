#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
using namespace std;

void bst::setRoot()
{
    root = nullptr;
}

void bst::setRoot(Node* newRoot)
{
    root = newRoot;
}

Node* bst::getRoot()
{
    return root;
}

Node* bst::insert(Node* root, int val)
{
    if (root == nullptr)
    {
        Node* newNode = new Node(val);
        root = newNode;
        return root;
    }
    else if (val == root->val)
    {
        return root;
    }
    else if (val < root->val)
    {
        root->left = insert(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = insert(root->right, val);
    }

    return root;
}

void bst::preOrder(Node* root, string label, ofstream& output)
{
    if (root != nullptr)
    {
        output << "[" << label << "] " << root->val << endl;
        preOrder(root->left, (label + "l"), output);
        preOrder(root->right, (label + "r"), output);
    }
}