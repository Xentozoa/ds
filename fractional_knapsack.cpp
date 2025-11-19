#include<iostream>
#include<algorithm>
using namespace std;

struct Item {
    float weight;
    float value;
};

bool compare(Item a, Item b) {
    return (a.value / a.weight) > (b.value / b.weight);
}

float fractionalKnapsack(Item items[], int n, float capacity) {
    sort(items, items + n, compare);

    float totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= capacity) {
            totalValue += items[i].value;
            capacity -= items[i].weight;
        } else {
            float fraction = capacity / items[i].weight;
            totalValue += items[i].value * fraction;
            break;
        }
    }
    return totalValue;
}

int main() {
    int n;
    float capacity;

    cout << "Enter number of items: ";
    cin >> n;

    Item items[n];
    cout << "Enter weight and value of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (weight value): ";
        cin >> items[i].weight >> items[i].value;
    }

    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    float maxValue = fractionalKnapsack(items, n, capacity);
    cout << "\nMaximum value in knapsack = " << maxValue << endl;

    return 0;
}