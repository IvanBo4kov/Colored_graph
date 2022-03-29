#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
using namespace std;

namespace fs = filesystem;

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

vector<vector<int>> read_graph(string name_file) {
    ifstream fin;
    fin.open(name_file);
    vector<vector<int>> graph;
    int vertex, edges;
    while (!fin.eof()) {
        fin >> vertex >> edges;
        vector <int> v(vertex, 0);
        graph.resize(vertex, v);
        for (int k = 0; k < edges; k++) {
            int start, end;
            fin >> start >> end;
            graph[start][end] = 1;
            graph[end][start] = 1;
        }
    }
    return graph;
}

int main () {
    
    // путь до директории с тестами и забил названия файлов из это директории в вектор
    
    string path = "/Users/ivanbockov/tests";
    auto it = fs::directory_iterator(path);
    vector<fs::path> array_path;
    copy_if(fs::begin(it), fs::end(it), std::back_inserter(array_path),
        [](const auto& entry) {
            return fs::is_regular_file(entry);
    });
    
    // для каждого файла выполняю тест
    
    for (auto & p : array_path) {
        vector<vector<int>> graph = read_graph(p.string());
        vector<bool> visited(graph.size());
        vector <int> v2(graph.size(), 0);
        vector<vector<int>> colored_graph(graph.size(), v2);
        
        int counter = 0;
        colored_graph = colored(graph, visited, counter);
        /*
        for (int i = 0; i < graph.size(); i++){
            for (int j = 0; j < graph.size(); j++){
                cout << colored_graph[i][j] << " ";
            }
            cout << endl;
        }
         */
        cout << counter - 1 << " " << 0 << endl;
    }
    
   /* for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (graph[i][j] != 0) {
                cout << graph[i][j] - 2 << " ";
            }
        }
    }
    cout << endl;
    */
    return 0;
}
