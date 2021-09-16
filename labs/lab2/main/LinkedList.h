#include <string>
using namespace std;

struct Score {
    string name;
    double score;
    Score* next;

    Score() {
        next = nullptr;
    }

    Score(string n, double s) {
        name = n;
        score = s;
        next = nullptr;
    }
};

class LinkedList {
private:
    Score* head;
    Score* tail;
    int size;

public:
    LinkedList();
    const Score* getTail();
    bool isEmpty();
    int getSize();
    bool print();
    void addToFront(string, double);
    void addToEnd(string, double);
    bool addAt(int index, string word, double score);
    Score* at(int index);
    void swap(int index1, int index2);
    void changeValue(int index, string data, double);
    void sort();
    void sortLength();
};