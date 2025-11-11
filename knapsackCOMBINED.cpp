#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
};

bool cmp(Item a, Item b) {
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

// -------- Fractional Knapsack (Greedy) --------
double fractionalKnapsack(int W, Item items[], int n) {
    sort(items, items + n, cmp);
    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (W >= items[i].weight) {
            W -= items[i].weight;
            totalValue += items[i].value;
        } else {
            totalValue += items[i].value * ((double)W / items[i].weight);
            break;
        }
    }
    return totalValue;
}

// -------- 0/1 Knapsack (Dynamic Programming) --------
int knapsack01(int W, Item items[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (items[i - 1].weight <= w)
                dp[i][w] = max(items[i - 1].value + dp[i - 1][w - items[i - 1].weight], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

// -------- Main Function --------
int main() {
    int n, W, choice;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> W;

    Item items[n];
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++)
        cin >> items[i].value >> items[i].weight;

    do {
        cout << "\n--- KNAPSACK MENU ---\n";
        cout << "1. Fractional Knapsack\n";
        cout << "2. 0/1 Knapsack\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nMaximum value (Fractional Knapsack): "
                     << fractionalKnapsack(W, items, n) << endl;
                break;

            case 2:
                cout << "\nMaximum value (0/1 Knapsack): "
                     << knapsack01(W, items, n) << endl;
                break;

            case 3:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
