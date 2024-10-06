#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct vertex
{
    int d;
    int pi;
    int index;

    bool operator < (const vertex & v) const {
        if (d == v.d) {
            return index > v.index;
        }
        else {
            return d > v.d;
        }
    }
};

vector<vector<int>> generateGraph(string filename) {
    ifstream file(filename);

    vector<vector<int>> adjacencyMatrix;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int value;

        while (ss >> value) {
            row.push_back(value);
        }

        adjacencyMatrix.push_back(row);
    }

    file.close();

    return adjacencyMatrix;
}

vector<vertex> initialize_single_source(vector<vector<int>>& adjacencyMatrix, int source) {
    // tabla de d y pi, el índice equivale al nodo    
    vector<vertex> vertices;
    int size = adjacencyMatrix.size();

    for (int i = 0; i < size; i++) {
        vertex currentVertex;
        currentVertex.d = INT_MAX;
        currentVertex.index = i;
        currentVertex.pi = -1;

        vertices.push_back(currentVertex);
    }

    vertices[source].d = 0;

    return vertices;
}

void relax(vertex& u, vertex& v, int weight_u_v) {
    if (u.d != INT_MAX && v.d > u.d + weight_u_v) {
        v.d = u.d + weight_u_v;
        v.pi = u.index;
    }
}

vector<vector<int>> reconstructGraph(vector<vertex>& vertices, vector<vector<int>>& adjacencyMatrix, int source) {
    vector<vector<int>> newAdjacencyMatrix;
    
    for (vertex v : vertices) {
        vector<int> row(adjacencyMatrix.size(), 0);

        if (v.index == source) {
            newAdjacencyMatrix.push_back(row);
            continue;
        }

        int destination = v.index;
        int origin = v.pi;
        int weight = adjacencyMatrix[destination][origin];

        row[v.pi] = weight;

        newAdjacencyMatrix.push_back(row);
    }

    return newAdjacencyMatrix;
}


vector<vector<int>> dijkstra(vector<vector<int>>& adjacencyMatrix, int source) {
    // tabla de d y pi, el índice equivale al nodo
    vector<vertex> vertices = initialize_single_source(adjacencyMatrix, source);

    int size = vertices.size();

    vector<int> S;

    priority_queue<vertex> Q;

    for (vertex& v : vertices) {
        Q.push(v);
    }

    while (!Q.empty()) {
        // quitar vértice del top de la cola
        vertex u = Q.top();
        Q.pop();

        S.push_back(u.index);

        for (int i = 0; i < size; i++) {
            if (adjacencyMatrix[u.index][i] != 0) {
                vertex& v = vertices[i];
                int weight_u_v = adjacencyMatrix[u.index][v.index];
                int oldDistance = v.d;
                relax(u, v, weight_u_v);

                if (v.d != oldDistance) {
                    Q.push(v);
                }
            }
        }
    }

    vector<vector<int>> newAdjacencyMatrix = reconstructGraph(vertices, adjacencyMatrix, source);

    return newAdjacencyMatrix;
}

void writeAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix, string filename) {
    int size = adjacencyMatrix.size();
    ofstream textFile(filename);

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        textFile << adjacencyMatrix[i][j] << " ";
      }
      textFile << "\n";
    }

    textFile.close();
}


int main(int argc, char *argv[]) {

    vector<vector<int>> adjacencyMatrix = generateGraph("grafo1.txt");
    int size = adjacencyMatrix.size();

    vector<vector<int>> newAdjancencyMatrix = dijkstra(adjacencyMatrix, 1);

    writeAdjacencyMatrix(newAdjancencyMatrix, "grafo1dijkstra.txt");
}