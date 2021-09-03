#include <iostream>
using namespace std;

void bubbleSort(int[]);

int main() {

	int arr[] = {1, 5, 2, 10, 3, 8, 4};

	bubbleSort(arr);

	for (int i = 0; i < sizeof(arr); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void bubbleSort(int arr[]) {

	int temp;

	for (int i = 0; i <sizeof(arr) - 2; i++)
	{
		if (arr[i] > arr[i+1]) {

			temp = arr[i + 1];
			arr[i + 1] = arr[i];
			arr[i] = temp;
		}
	}
}