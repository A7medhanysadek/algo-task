#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Edge {
    int src, dest, weight;
};
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}
int findParent(int v, vector<int>& parent) {
    if (v != parent[v])
        parent[v] = findParent(parent[v], parent);
    return parent[v];
}
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}
void kruskalMST(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), compareEdges);
    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; ++i)
        parent[i] = i;

    vector<Edge> mst;
    int mstWeight = 0;
    for (const Edge& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        if (findParent(u, parent) != findParent(v, parent)) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            unionSets(u, v, parent, rank);
        }
    }
    cout << "Edges in the MST:\n";
    for (const Edge& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}
int main() {
    int V = 4;
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };
    kruskalMST(V, edges);
    return 0;
}
