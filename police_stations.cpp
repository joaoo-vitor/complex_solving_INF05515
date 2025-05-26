#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int findIndexEdge(vector<pair<int,int>> roads, int orig, int dst){
    for(int i=0; i<roads.size(); i++){
        if(roads[i].first==orig && roads[i].second ==dst) return i+1;
        if(roads[i].first==dst && roads[i].second ==orig) return i+1;
    }
}

void removeEdge(vector<vector<int>>& graph, vector<int> removableEdges, vector<pair<int,int>> roads, int orig, int dst){
    // Remove destiny node from list of adjencies of origin node and vice versa
    graph[orig].erase(remove(graph[orig].begin(), graph[orig].end(), dst));
    graph[dst].erase(remove(graph[dst].begin(), graph[dst].end(), orig));
    
    // Add the index of this edge to the removableEdges list
    removableEdges.push_back(findIndexEdge(roads, orig, dst));
}

int main(){
    int n, k, d, entrada;
    cin >> n >> k >> d;
    vector<vector<int>> graph(n+1);
    vector<bool> visited;
    vector<int> cities_with_police;
    vector<pair<int,int>> roads;
    vector<int> removableEdges;
    
    // Create list of nodes with police
    for (int i=0; i<k; i++){
        cin >> entrada;
        cities_with_police.push_back(entrada);
    }

    // Create graph
    for (int j = 0; j < n-1; ++j) {
        int orig, dst;
        cin >> orig >> dst;
        
        // Register the index of this edge (road)
        roads.push_back({orig, dst});

        // Create connection on the adjecency list
        graph[orig].push_back(dst);
        graph[dst].push_back(orig);
        
    }

    // Make a bfs starting from all the police stations at once
    queue<int> queue_bfs;
    for(int city: cities_with_police) queue_bfs.push(city);
    while(!queue_bfs.empty()){
        int current_city = queue_bfs.front();
        queue_bfs.pop();
        for (int neighbor : graph[current_city]){
            // Visit each neighbor city 
            if(!visited[neighbor]){
                visited[neighbor]=true;
                queue_bfs.push(neighbor);
            }else{
                removeEdge(graph, removableEdges, roads, current_city, neighbor);
            }
        }
    }
}