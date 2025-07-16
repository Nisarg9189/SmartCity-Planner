#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <stack>
#include <climits>
using namespace std;

class GraphApp {
private:
    class Edge {
    public:
        string v;
        int wt;
        Edge(string v, int wt) {
            this->v = v;
            this->wt = wt;
        }
    };

    unordered_map<string, vector<Edge>> graph;

public:
    void electricityMST() {
        unordered_map<string, vector<Edge>> buildings;
        int size;
        cout << "\n-- Electricity Network (MST) --\n";
        cout << "Enter total number of wire connections: ";
        cin >> size;

        for (int i = 0; i < size; i++) {
            string b1, b2;
            int len;
            cout << "Building 1: ";
            cin >> b1;
            cout << "Building 2: ";
            cin >> b2;
            cout << "Wire length: ";
            cin >> len;

            buildings[b1].push_back(Edge(b2, len));
            buildings[b2].push_back(Edge(b1, len));
        }

        vector<tuple<string, string, int>> mstEdges;
        int total = getMSTLength(buildings, mstEdges);

        cout << "\nTotal cable length required: " << total << "\n";
        cout << "Cable should be laid between:\n";
        for (auto& [u, v, wt] : mstEdges) {
            cout << "  " << u << " --(" << wt << ")--> " << v << endl;
        }
    }

    int getMSTLength(unordered_map<string, vector<Edge>>& buildings,
                     vector<tuple<string, string, int>>& mstEdges) {
        unordered_set<string> visited;
        int totalLen = 0;

        for (auto& [node, _] : buildings) {
            if (visited.count(node)) continue;

            priority_queue<pair<int, pair<string, string>>, vector<pair<int, pair<string, string>>>, greater<>> pq;
            pq.push({0, {node, ""}});

            while (!pq.empty()) {
                auto [len, nodes] = pq.top();
                auto [u, parent] = nodes;
                pq.pop();

                if (visited.count(u)) continue;

                visited.insert(u);
                totalLen += len;

                if (!parent.empty()) {
                    mstEdges.push_back({parent, u, len});
                }

                for (auto& edge : buildings[u]) {
                    if (!visited.count(edge.v)) {
                        pq.push({edge.wt, {edge.v, u}});
                    }
                }
            }
        }

        return totalLen;
    }

    void shortestPath() {
        graph.clear();
        int size;
        cout << "\n-- Shortest Path (Dijkstra + TopoSort) --\n";
        cout << "Enter number of roads: ";
        cin >> size;

        for (int i = 0; i < size; i++) {
            string c1, c2;
            int len;
            cout << "City 1: ";
            cin >> c1;
            cout << "City 2: ";
            cin >> c2;
            cout << "Distance: ";
            cin >> len;

            graph[c1].push_back(Edge(c2, len));
            graph[c2].push_back(Edge(c1, len));
        }

        string start, end;
        cout << "\nStart city: ";
        cin >> start;
        cout << "End city: ";
        cin >> end;

        runDijkstra(start, end);
        runTopoSort();
    }

    void runDijkstra(string src, string dest) {
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;

        for (auto& [u, _] : graph)
            dist[u] = INT_MAX;

        dist[src] = 0;
        parent[src] = "#";
        pq.push({0, src});

        while (!pq.empty()) {
            string u = pq.top().second;
            pq.pop();

            for (auto e : graph[u]) {
                if (dist[e.v] > dist[u] + e.wt) {
                    dist[e.v] = dist[u] + e.wt;
                    parent[e.v] = u;
                    pq.push({dist[e.v], e.v});
                }
            }
        }

        if (dist[dest] == INT_MAX) {
            cout << "No path from " << src << " to " << dest << endl;
            return;
        }

        stack<string> path;
        string curr = dest;
        while (curr != "#") {
            path.push(curr);
            curr = parent[curr];
        }

        cout << "\nShortest path from " << src << " to " << dest << " = " << dist[dest] << " units\n";
        cout << "Path: ";
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << endl;
    }

    bool dfs(string node, unordered_set<string>& visited,
             unordered_set<string>& onPath, stack<string>& topoStack) {
        visited.insert(node);
        onPath.insert(node);

        for (Edge& edge : graph[node]) {
            if (onPath.count(edge.v)) return false;
            if (!visited.count(edge.v)) {
                if (!dfs(edge.v, visited, onPath, topoStack)) return false;
            }
        }

        onPath.erase(node);
        topoStack.push(node);
        return true;
    }

    void runTopoSort() {
        stack<string> topoStack;
        unordered_set<string> visited, onPath;

        for (auto& [node, _] : graph) {
            if (!visited.count(node)) {
                if (!dfs(node, visited, onPath, topoStack)) {
                    cout << "\nGraph has a cycle. Topological Sort not possible.\n";
                    return;
                }
            }
        }

        cout << "\nTopological Order (if DAG): ";
        while (!topoStack.empty()) {
            cout << topoStack.top() << " ";
            topoStack.pop();
        }
        cout << endl;
    }
};

int main() {
    GraphApp app;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Electricity Network (MST)\n";
        cout << "2. Shortest Path (Dijkstra + TopoSort)\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        int ch;
        cin >> ch;

        switch (ch) {
            case 1:
                app.electricityMST();
                break;
            case 2:
                app.shortestPath();
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
