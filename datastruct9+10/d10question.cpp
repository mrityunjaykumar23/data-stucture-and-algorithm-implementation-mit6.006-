#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, unordered_set<int>& ancestors) {
    // Mark the current node as visited and add to ancestors
    visited[node] = true;
    ancestors.insert(node);

    // Explore neighbors
    for (int neighbor : adj[node]) {
        // If neighbor is already visited and in ancestors, it's a back edge
        if (ancestors.find(neighbor) != ancestors.end()) {
            cout << "Back edge found: " << node << " -> " << neighbor << endl;
            return true; // Cycle detected
        }

        // If the neighbor hasn't been visited yet, do a DFS on it
        if (!visited[neighbor]) {
            if (dfs(neighbor, adj, visited, ancestors)) {
                return true; // Cycle detected in the recursion
            }
        }
    }

    // After all neighbors are processed, remove the node from ancestors
    ancestors.erase(node);
    return false;
}

bool detectCycle(vector<vector<int>>& adj, int n) {
    vector<bool> visited(n, false);
    unordered_set<int> ancestors;

    // Perform DFS from every unvisited node
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfs(i, adj, visited, ancestors)) {
                return true; // Cycle detected
            }
        }
    }

    return false; // No cycle detected
}

int main() {
    vector<vector<int>> adj = {{1, 2}, {2}, {0, 3}, {}};  // Example graph
    int n = adj.size();

    if (detectCycle(adj, n)) {
        cout << "Graph contains a cycle" << endl;
    } else {
        cout << "Graph does not contain a cycle" << endl;
    }

    return 0;
}
