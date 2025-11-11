#include <iostream>
#include <climits>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Edge edges[E];
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    int dist[V];
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Relax edges |V| - 1 times
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].w;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].w;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "\nGraph contains negative weight cycle\n";
            return 0;
        }
    }

    cout << "\nShortest distances from vertex " << src << ":\n";
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            cout << "INF ";
        else
            cout << dist[i] << " ";
    }
    cout << endl;

    return 0;
}
