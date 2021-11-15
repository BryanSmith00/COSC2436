#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    Node(int val) : val(val), left(nullptr), right(nullptr) {}
};

class bst
{
private:
    Node* root;
    int size;

public:
    void setRoot();
    void setRoot(Node*);
    Node* getRoot();
    Node* insert(Node* root, int val);
    void preOrder(Node* root, string label, ofstream& output);
};