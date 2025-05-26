#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX_EMPLOYEES = 105;
const int MAX_LANGUAGES = 105;

vector<int> graph[MAX_EMPLOYEES + MAX_LANGUAGES];
bool visited[MAX_EMPLOYEES + MAX_LANGUAGES];

// Dfs starting from a node
void dfs(int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor])
            dfs(neighbor);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    bool someoneSpeaks = false;

    // Create graph based on the inputs 
    // Check if at least one person speaks a language
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;

        if (k > 0)
            someoneSpeaks = true;

        for (int j = 0; j < k; ++j) {
            int lang;
            cin >> lang;

            // Connect employee i to language lang (offset language index by n)
            graph[i].push_back(n + lang);
            graph[n + lang].push_back(i);
        }
    }

    // See how many connected components there are starting from the employee nodes
    int components = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i);
            components++;
        }
    }

    if (!someoneSpeaks)
        cout << n << endl;
    else
        cout << components - 1 << endl;

    return 0;
}
