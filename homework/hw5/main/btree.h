#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node
{
public:
    int* keys;  // An array of keys
    int degree;
    Node** C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false

    Node(int _t, bool _leaf);   // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, Node* y);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in the subtree rooted with this node.
    Node* search(int k);   // returns NULL if k is not present.

// Make BTree friend of this so that we can access private members of this
// class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
public:
    Node* root; // Pointer to root node
    int degree;  // Minimum degree
    int count;

    int getCount() { return count; }

    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;  degree = _t, count = 0;
    }

    // function to traverse the tree
    void traverse()
    {
        if (root != NULL) root->traverse();
    }

    // function to search a key in this tree
    Node* search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k)
    {
        // If tree is empty
        if (root == NULL)
        {
            // Allocate memory for root
            root = new Node(degree, true);
            root->keys[0] = k;  // Insert key
            root->n = 1;  // Update number of keys in root
            count++;
        }
        else // If tree is not empty
        {
            // If root is full, then tree grows in height
            if (root->n == 2 * degree - 1)
            {
                // Allocate memory for new root
                Node* s = new Node(degree, false);

                // Make old root as child of new root
                s->C[0] = root;

                // Split the old root and move 1 key to the new root
                s->splitChild(0, root);

                // New root has two children now.  Decide which of the
                // two children is going to have new key
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);

                // Change root
                root = s;
                count++;
            }
            else  // If root is not full, call insertNonFull for root
            {
                count++;
                root->insertNonFull(k);
            }
        }
    }
};