#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = filesystem;

vector<vector<int>> read_graph(const string& name_file, vector<pair<int, int>>& list_edges, vector<int>& edges_counter) {
    ifstream fin;
    fin.open(name_file);
    vector<vector<int>> graph;
    int vertex, edges;
    vector<pair<int, int>> pairs;
    list_edges.clear();
    edges_counter.clear();
    if (fin.is_open()) {
        fin >> vertex >> edges;
        vector <int> v(vertex, 0);
        graph.resize(vertex, v);
        auto zero = make_pair(0, 0);
        pairs.resize(graph.size(), zero);
        for (int k = 0; k < edges; k++) {
            int start, end;
            fin >> start >> end;
            auto p1 = make_pair(start, end);
            list_edges.push_back(p1);
            graph[start][end] = 1;
            graph[end][start] = 1;
            pairs[start].first += 1;
            pairs[end].first += 1;
            pairs[start].second = start;
            pairs[end].second = end;
        }
    } else {
        cout << "file not read" << endl;
    }
    sort(pairs.begin(), pairs.end());
    for(int i = pairs.size()-1;i >= 0; i--){
        edges_counter.push_back(pairs[i].second);
    }
    return graph;
}

vector<int> solve(vector<vector<int>>& graph, const vector<int>& edges_counter) {
    vector<int> vColors(graph.size(), -1);
    for(auto it : edges_counter) {
        int i = it;
        vector<bool> colored(graph.size(), false);
        for (int j = 0; j < graph.size(); j++) {
            if (graph[i][j] == 1) {
                if(vColors[j] > -1){
                    colored[vColors[j]] = true;
                }
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
        vector<int> edges_counter;
        vector<pair<int, int>> edges;
        vector<vector<int>> graph = read_graph(p.string(), edges, edges_counter);
        vector<int> colored2 = solve(graph, edges_counter);
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
        */
        cout << endl;
        for (auto i : edges) {
            if (colored2[i.first] == colored2[i.second]) {
                cout << "Error, colored test: " << p.string() << endl;
                cout << i.first << " " << i.second << endl;
                break;
            }
        }
    }
    return 0;
}
