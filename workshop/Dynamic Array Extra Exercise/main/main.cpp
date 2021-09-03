#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* arr;
    int max;
    int count;

public:

    //Constructor with size value passed in
    DynamicArray(int size):max(size), arr(new int[max]), count(0) {
        max = size;
        arr = new int[max];
        count = 0;

    }

    //Default constructor
    DynamicArray() {
        max = 20;
        count = 0;
        arr = new int[max];
    }

    //Dynamically adds a value to the end of the array
    void add_to_end(int x) {
        if (count >= max) {

            max *= 2;
            int* newArr = new int[max];

            for (int i = 0; i < count; i++) {
                newArr[i] = arr[i];
            }

            delete arr;
            arr = newArr;

            arr[count] = x;
            count++;


        }else{
            arr[count] = x;
            count++;
        }
    }

    void add_to_begin(int x) {
        if (count >= max) {

            max *= 2;
            int* newArr = new int[max];

            for (int i = 0; i < count; i++) {
                newArr[i+1] = arr[i];
            }

            delete arr;
            arr = newArr;

            arr[0] = x;
            count++;

        }
        else {
            int* newArr = new int[max];

            for (int i = 0; i < count; i++) {
                newArr[i + 1] = arr[i];
            }

            delete arr;
            arr = newArr;

            newArr[0] = x;
            count++;
        }
    }

    //Prints out the entire array
    void print() {
        for (int i = 0; i < count; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl << "Size: " << max << endl << endl;
    }
};

int main() {
    DynamicArray da(5);
    da.add_to_end(2);
    da.print();
    da.add_to_end(3);
    da.print();
    da.add_to_end(4);
    da.print();
    da.add_to_begin(1);
    da.print();
    da.add_to_begin(0);
    da.print();
    da.add_to_begin(-1);
    da.print();
    da.add_to_end(5);
    da.print();
    da.add_to_end(6);
    da.print();
    da.add_to_end(7);
    da.print();
    da.add_to_end(8);
    da.print();
    da.add_to_end(9);
    da.print();
    da.add_to_end(10);
    da.print();

}