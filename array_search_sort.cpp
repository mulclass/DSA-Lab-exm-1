// Lab: Array Data Structure - Searching and Sorting
// Iterative binary search, recursive binary search,
// selection sort, bubble sort, insertion sort.

#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

// ---------- Utility functions ----------

void inputArray(int arr[], int n) {
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
}

void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void copyArray(const int src[], int dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// ---------- Searching (array MUST be sorted in ascending order) ----------

// Iterative binary search: returns index of key, or -1 if not found
int binarySearchIterative(const int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        else if (key < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

// Recursive binary search: returns index of key, or -1 if not found
int binarySearchRecursive(const int arr[], int low, int high, int key) {
    if (low > high)                       // base case: not found
        return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == key)                  // base case: found
        return mid;
    else if (key < arr[mid])
        return binarySearchRecursive(arr, low, mid - 1, key);
    else
        return binarySearchRecursive(arr, mid + 1, high, key);
}

// ---------- Sorting (ascending order) ----------

// Selection sort: repeatedly select the minimum of the unsorted part
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        if (minIndex != i)
            swapValues(arr[i], arr[minIndex]);
    }
}

// Bubble sort: swap adjacent out-of-order elements; stops early if no swaps
void bubbleSort(int arr[], int n) {
    for (int pass = 0; pass < n - 1; pass++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - pass; j++) {
            if (arr[j] > arr[j + 1]) {
                swapValues(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Insertion sort: insert each element into its place in the sorted part
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ---------- Main (menu driven) ----------

int main() {
    int original[MAX_SIZE], work[MAX_SIZE];
    int n;

    cout << "Enter number of elements (max " << MAX_SIZE << "): ";
    cin >> n;
    if (n <= 0 || n > MAX_SIZE) {
        cout << "Invalid size." << endl;
        return 1;
    }
    inputArray(original, n);
    copyArray(original, work, n);

    int choice;
    do {
        cout << "\n===== MENU =====\n"
             << "1. Display array\n"
             << "2. Selection sort\n"
             << "3. Bubble sort\n"
             << "4. Insertion sort\n"
             << "5. Binary search (iterative)\n"
             << "6. Binary search (recursive)\n"
             << "7. Reset to original (unsorted) array\n"
             << "0. Exit\n"
             << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Array: ";
            printArray(work, n);
            break;
        case 2:
            selectionSort(work, n);
            cout << "Sorted (selection): ";
            printArray(work, n);
            break;
        case 3:
            bubbleSort(work, n);
            cout << "Sorted (bubble): ";
            printArray(work, n);
            break;
        case 4:
            insertionSort(work, n);
            cout << "Sorted (insertion): ";
            printArray(work, n);
            break;
        case 5:
        case 6: {
            int key;
            cout << "Enter value to search: ";
            cin >> key;
            cout << "Note: array must be sorted for binary search.\n";
            int pos = (choice == 5)
                          ? binarySearchIterative(work, n, key)
                          : binarySearchRecursive(work, 0, n - 1, key);
            if (pos == -1)
                cout << key << " not found." << endl;
            else
                cout << key << " found at index " << pos << endl;
            break;
        }
        case 7:
            copyArray(original, work, n);
            cout << "Array reset: ";
            printArray(work, n);
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
