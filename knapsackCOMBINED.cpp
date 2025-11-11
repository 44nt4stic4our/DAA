#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Item {
    int value;int weight;double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(int capacity, Item items[], int n) {
    for (int i = 0; i < n; i++)
        items[i].ratio = (double)items[i].value / items[i].weight;

    sort(items, items + n, compare);

    double totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value * ((double)capacity / items[i].weight);
            break;
        }
    }
    return totalValue;
}

int zeroOneKnapsack(int capacity, Item items[], int n) {
    int dp[n + 1][capacity + 1];
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][capacity];
}

int main() {

    int n;
    cout << "Enter number of items: ";
    cin >> n;

    Item *items = new Item[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter value of item " << i + 1 << ": ";
        cin >> items[i].value;
        cout << "Enter weight of item " << i + 1 << ": ";
        cin >> items[i].weight;
    }

    int capacity;
    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    double fracValue = fractionalKnapsack(capacity, items, n);
    int dpValue = zeroOneKnapsack(capacity, items, n);

    cout << fixed << setprecision(2);
    cout << "\nMaximum value (Fractional Knapsack / Greedy) = " << fracValue << endl;
    cout << "Maximum value (0/1 Knapsack / DP) = " << dpValue << endl;

    cout << "\n=> Observation: Fractional Knapsack (Greedy) may give a higher "
            "value, but in 0/1 Knapsack we cannot take fractions of items, "
            "so DP gives the *true optimal solution*."
         << endl;

    delete[] items;
    return 0;
}
