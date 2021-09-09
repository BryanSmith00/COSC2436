struct nb {
    int n;
    nb* next;
    int size;
};

class list {
private:
    nb* head;

public:
    list();
    nb* gethead();
    bool isEmpty();
    int getSize();
    void print();
    void addToFront(int);
    void addToEnd(int);
    void addAt(int index, int value);
    void removeFromFront();
    void removeFromEnd();
    void removeAt(int index);
    ~list();

};