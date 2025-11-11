#include <iostream>
#define INF 9999
using namespace std;

int n, cost[10][10], visited[10], minCost = INF;
int bestPath[10], tempPath[10];

void TSP(int city, int count, int costTillNow) {
    visited[city] = 1;
    tempPath[count - 1] = city;

    if (count == n && cost[city][0] > 0)
    {
        int total = costTillNow + cost[city][0];
        if (total < minCost) {
            minCost = total;
            for (int i = 0; i < n; i++)
                bestPath[i] = tempPath[i];
        }
        visited[city] = 0;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && cost[city][i] > 0) {
            int newCost = costTillNow + cost[city][i];
            if (newCost < minCost)
                TSP(i, count + 1, newCost);
        }
    }
    visited[city] = 0; // backtrack
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter cost matrix (use 9999 if no direct path):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    TSP(0, 1, 0); 

    cout << "\nMinimum cost: " << minCost << endl;
    cout << "Optimal path: ";
    for (int i = 0; i < n; i++)
        cout << bestPath[i] << " -> ";
    cout << "0\n";
    return 0;
}
