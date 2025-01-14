#include<vector>
#include <iostream>
#include <unordered_map>
using namespace std;      //unordered map works like hashtable
int main() {
    // Define the adjacency list for W1
    unordered_map<int, unordered_map<int, int>> W1;
    W1[0] = {{1, -2}};
    W1[1] = {{2, 0}};
    W1[2] = {{0, 1}};
    W1[3] = {{4, 3}};
    W1[4] = {{0, -1}};

    // Define the adjacency list for W2
    unordered_map<int, unordered_map<int, int>> W2;
    W2[0] = {{1, 1}, {3, 2}, {4, -1}};
    W2[1] = {{2, 0}, {0, 1}};
    W2[2] = {{0, 1}, {3, 0}};
    W2[3] = {{4, 3}, {0, 2}, {2, 0}};
    W2[4] = {{0, -1}};

    // Print W1 adjacency list
    cout << "W1 adjacency list:" << endl;
    for (const auto& src : W1) {
        cout << src.first << ": ";
        for (const auto& dest : src.second) {
            cout << "{" << dest.first << ": " << dest.second << "} ";
        }
        cout << endl;
    }

    // Print W2 adjacency list
    cout << "W2 adjacency list:" << endl;
    for (const auto& src : W2) {
        cout << src.first << ": ";
        for (const auto& dest : src.second) {
            cout << "{" << dest.first << ": " << dest.second << "} ";
        }
        cout << endl;
    }

    return 0;
}
