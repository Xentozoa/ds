#include <iostream>
using namespace std;

void heapifyMax(int arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyMax(arr, n, largest);
    }
}

void heapifyMin(int arr[], int n, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapifyMin(arr, n, smallest);
    }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapifyMax(arr, n, i);
}

void buildMinHeap(int arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapifyMin(arr, n, i);
}

int main() {
    int marks[100], n, choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Insert Marks\n";
        cout << "2. Find Maximum Marks\n";
        cout << "3. Find Minimum Marks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
        case 1:
            cout << "Enter number of students: ";
            cin >> n;

            cout << "Enter marks:\n";
            for (int i = 0; i < n; i++)
                cin >> marks[i];
            break;

        case 2:
            buildMaxHeap(marks, n);
            cout << "\nMaximum Marks: " << marks[0] << endl;
            break;

        case 3:
            buildMinHeap(marks, n);
            cout << "\nMinimum Marks: " << marks[0] << endl;
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
