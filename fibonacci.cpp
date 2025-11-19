#include <iostream>
using namespace std;

// --- Recursive Function ---
int fib(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    return fib(n - 1) + fib(n - 2);
}

int main() {
    int choice, n;

    do {
        cout << "\n--- Fibonacci Menu ---\n";
        cout << "1. Fibonacci using Recursion\n";
        cout << "2. Fibonacci using Iteration\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter number of terms: ";
                cin >> n;

                cout << "Fibonacci Series (Recursion): ";
                for (int i = 0; i < n; i++) {
                    cout << fib(i) << " ";
                }
                cout << endl;
                break;
            }

            case 2: {
                cout << "Enter number of terms: ";
                cin >> n;

                cout << "Fibonacci Series (Iteration): ";
                int a = 0, b = 1, c;

                if (n >= 1) cout << a << " ";
                if (n >= 2) cout << b << " ";

                for (int i = 2; i < n; i++) {
                    c = a + b;
                    cout << c << " ";
                    a = b;
                    b = c;
                }
                cout << endl;
                break;
            }

            case 3:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}