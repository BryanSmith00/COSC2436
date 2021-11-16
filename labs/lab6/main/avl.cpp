#include <iostream>
#include <fstream>
#include <string>
#include "avl.h"
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