#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> colored (vector<vector<int>>& graph, vector<bool> visited, int& counter) {
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (graph[i][j] == 1) {
                for (int r = 0; r < visited.size(); r++) {
                    visited[r] = true;
                }
                
                for (int k = 0; k < graph.size(); k++) {
                    if (graph[i][k] > 1) {
                        visited[graph[i][k] - 2] = false;
                    }
                    if (graph[j][k] > 1) {
                        visited[graph[j][k] - 2] = false;
                    }
                }
                
                int r;
                for (r = 0; r < visited.size(); r++) {
                    if (visited[r] == true) {
                        graph[i][j] = r + 2;
                        graph[j][i] = r + 2;
                        if (counter < r + 2) {
                            counter = r + 2;
                        }
                        break;
                    }
                }
            }
        }
    }
    return graph;
}

int main () {
    int vertex, edges;
    cin >> vertex >> edges;
    vector <int> v(vertex, 0);
    vector<vector<int>> graph(vertex, v);
    for (int k = 0; k < edges; k++){
        int start, end;
        cin >> start >> end;
        graph[start][end] = 1;
        graph[end][start] = 1;
    }
    vector<bool> visited(graph.size());
    
    
    vector <int> v2(vertex, 0);
    vector<vector<int>> colored_graph(vertex, v2);
    
    int counter = 0;
    colored_graph = colored(graph, visited, counter);
    
    for (int i = 0; i < vertex; i++){
        for (int j = 0; j < vertex; j++){
            cout << colored_graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << counter - 1 << endl;
    return 0;
}
