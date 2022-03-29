#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

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

vector<int> solve(vector<vector<int>> graph) {
    vector<int> vColors(graph.size(), -1);
    for (int i = 0; i < graph.size(); i++) {
        int color = 0;
        for (int j = 0; j < i; j++) {
            if (graph[i][j] == 1) {
                if(vColors[j] == color) {
                    color++;
                }
            }
        }
        vColors[i] = color;
    }
    return vColors;
}

int main () {
    
    // путь до директории с тестами и забил названия файлов из это директории в вектор
    
    string path = "/Users/ivanbockov/tests_1";
    auto it = fs::directory_iterator(path);
    vector<fs::path> array_path;
    copy_if(fs::begin(it), fs::end(it), std::back_inserter(array_path),
        [](const auto& entry) {
            return fs::is_regular_file(entry);
    });
    
    // для каждого файла выполняю тест
    
    for (auto & p : array_path) {
        vector<vector<int>> graph = read_graph(p.string());
        vector<int> colored2 = solve(graph);
        int max = -1;
        for (int i = 0; i < colored2.size(); i++) {
            if (colored2[i] > max) {
                max = colored2[i];
            }
        }
        cout << max + 1 << " " << 0 << endl;
        for (auto i : colored2) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}
