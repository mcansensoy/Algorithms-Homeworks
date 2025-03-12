#include "the7.h"

using namespace std;

bool isDAG(const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> in_degree(n, 0);

    for (int i=0; i<n; i++) {
        for (pair<int, int> edge : graph[i]) {
            in_degree[edge.first]++;
        }
    }

    vector<int> queue;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            queue.push_back(i);
        }
    }

    int visited = 0;
    while (!queue.empty()) {
        int node = queue.back();
        queue.pop_back();
        visited++;

        for (pair<int, int> edge : graph[node]) {
            if (--in_degree[edge.first] == 0) {
                queue.push_back(edge.first);
            }
        }
    }

    if(visited == n){
        return true;
    }
    return false;
}

void longestPathBellmanFord(const vector<vector<pair<int, int>>>& graph, int node_count, int start, int end, long& length, vector<int>& path) {
    vector<long> dist(node_count, LONG_MIN); 
    vector<int> prev(node_count, -1);
    vector<bool> in_path(node_count, false);

    dist[start] = 0;
    int v,weight;
    bool isChanged = false;

    for (int i = 0; i < node_count - 1; ++i) {
        isChanged = false;
        for (int u = 0; u < node_count; ++u) {
            if (dist[u] == LONG_MIN) continue;
            for (pair<int, int> edge : graph[u]) {
                v = edge.first;
                weight = edge.second;

                if (dist[u] + weight > dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    isChanged = true;
                }
            }
        }
        if(!isChanged){
            break;
        }
    }

    length = dist[end];
    if (length != LONG_MIN) {
        int current = end;
        while (current != -1) {
            if (in_path[current]) {
                length = LONG_MIN;
                path.clear();
                return;
            }
            in_path[current] = true;
            path.push_back(current);
            current = prev[current];
        }
        reverse(path.begin(), path.end());
    }
}

void exhaustiveSearch(const vector<vector<pair<int, int>>>& graph, int current, int end, long current_length, long& max_length, vector<int>& current_path, vector<int>& best_path, vector<bool>& visited) {
    if (current == end) {
        if (current_length > max_length) {
            max_length = current_length;
            best_path = current_path;
        }
        return;
    }

    visited[current] = true;

    for (pair<int, int> edge : graph[current]) {
        if (!visited[edge.first]) {
            current_path.push_back(edge.first);
            exhaustiveSearch(graph, edge.first, end, current_length + edge.second, max_length, current_path, best_path, visited);
            current_path.pop_back();
        }
    }

    visited[current] = false;
}

vector<int> find_longest_path(const vector<vector<pair<int, int>>>& graph, int starting_node, int destination_node, long& length_of_longest_path) {
    vector<int> path;

    if (isDAG(graph)) {
        longestPathBellmanFord(graph, graph.size(),  starting_node, destination_node, length_of_longest_path, path);
    } else {
        length_of_longest_path = LONG_MIN;
        vector<int> current_path = {starting_node};
        vector<bool> visited(graph.size(), false);
        exhaustiveSearch(graph, starting_node, destination_node, 0, length_of_longest_path, current_path, path, visited);
    }

    return path;
}