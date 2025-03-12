#include "the5.h"

void manualSort(std::vector<int>& vec) {
    int k = vec.size();
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (vec[j] < vec[i]) {
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
        }
    }
}

void dfs(int u, const std::vector<std::vector<int>>& adjList, std::vector<bool>& visited, std::vector<int>& disc, std::vector<int>& low, std::vector<bool>& inStack, std::vector<int>& stack, int& time, std::vector<std::vector<int>>& sccs) {
    visited[u] = true;
    disc[u] = low[u] = time++;
    stack.push_back(u);
    inStack[u] = true;

    for (int v : adjList[u]) {
        if (!visited[v]) {
            dfs(v, adjList, visited, disc, low, inStack, stack, time, sccs);
            low[u] = std::min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        std::vector<int> scc;
        while (true) {
            int v = stack.back();
            stack.pop_back();
            inStack[v] = false;
            scc.push_back(v);
            if (u == v) break;
        }
        manualSort(scc);
        sccs.push_back(scc);
    }
}

std::vector<std::vector<int>> find_work_order(const std::vector<std::vector<bool>>& dependencies) {
    int n = dependencies.size();
    std::vector<std::vector<int>> adjList(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dependencies[i][j]) {
                adjList[i].push_back(j);
            }
        }
    }

    std::vector<bool> visited(n, false);
    std::vector<int> disc(n, -1), low(n, -1);
    std::vector<bool> inStack(n, false);
    std::vector<int> stack;
    std::vector<std::vector<int>> sccs;
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, adjList, visited, disc, low, inStack, stack, time, sccs);
        }
    }

    std::vector<int> sccId(n, -1);
    int sccsSize = sccs.size();
    for (int i = 0; i < sccsSize; i++) {
        for (int node : sccs[i]) {
            sccId[node] = i;
        }
    }

    std::vector<std::vector<int>> condensedGraph(sccsSize);
    for (int u = 0; u < n; u++) {
        for (int v : adjList[u]) {
            if (sccId[u] != sccId[v]) {
                condensedGraph[sccId[u]].push_back(sccId[v]);
            }
        }
    }

    std::vector<int> inDegree(sccsSize, 0);
    int cGsize = condensedGraph.size();
    for (int u = 0; u < cGsize; u++) {
        for (int v : condensedGraph[u]) {
            inDegree[v]++;
        }
    }

    std::vector<std::vector<int>> result;
    std::vector<int> zeroInDegree;
    int iDsize = inDegree.size();
    for (int i = 0; i < iDsize; i++) {
        if (inDegree[i] == 0) zeroInDegree.push_back(i);
    }

    while (!zeroInDegree.empty()) {
        int smallest = zeroInDegree[0];
        int smallestIndex = 0;
        int ziDsize = zeroInDegree.size();
        for (int i = 1; i < ziDsize; i++) {
            if (zeroInDegree[i] < smallest) {
                smallest = zeroInDegree[i];
                smallestIndex = i;
            }
        }
        zeroInDegree.erase(zeroInDegree.begin() + smallestIndex);

        result.push_back(sccs[smallest]);

        for (int v : condensedGraph[smallest]) {
            inDegree[v]--;
            if (inDegree[v] == 0) zeroInDegree.push_back(v);
        }
    }

    return result;
}