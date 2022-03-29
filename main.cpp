#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

vector<vector<int>> read_graph(const string& name_file, vector<pair<int, int>>& list_edges) {
    ifstream fin;
    fin.open(name_file);
    vector<vector<int>> graph;
    int vertex, edges;
    list_edges.clear();
    if (fin.is_open()) {
//    while (!fin.eof()) {
        fin >> vertex >> edges;
        vector <int> v(vertex, 0);
        graph.resize(vertex, v);
        for (int k = 0; k < edges; k++) {
            int start, end;
            fin >> start >> end;
            auto p1 = make_pair(start, end);
            list_edges.push_back(p1);
            graph[start][end] = 1;
            graph[end][start] = 1;
        }
    } else {
        cout << "file not read" << endl;
    }
//    }
    return graph;
}

vector<int> solve(vector<vector<int>>& graph) {
    vector<int> vColors(graph.size(), -1);
    for (int i = 0; i < graph.size(); i++) {
        int color = 0;
        vector<bool> colored(graph.size(), false);
        for (int j = 0; j < i; j++) {
            if (graph[i][j] == 1) {
                colored[vColors[j]] = true;
            }
        }
        for (int k = 0; k < graph.size(); k++) {
            if (!colored[k]) {
                vColors[i] = k;
                break;
            }
        }
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
        vector<pair<int, int>> edges;
        vector<vector<int>> graph = read_graph(p.string(), edges);
        vector<int> colored2 = solve(graph);
        int max = -1;
        for (int i = 0; i < colored2.size(); i++) {
            if (colored2[i] > max) {
                max = colored2[i];
            }
        }
        cout << p.string() << " " << max + 1 << endl;
       /* cout << max + 1 << " " << 0 << endl;
        for (auto i : colored2) {
            cout << i << " ";
        }
        cout << endl;
        */
        /*
        for (auto i : edges) {
            if (colored2[i.first] == colored2[i.second]) {
                cout << "Error, colored test: " << p.string() << endl;
                cout << i.first << " " << i.second << endl;
                break;
            }
        }
         */
         
    }
    return 0;
}
