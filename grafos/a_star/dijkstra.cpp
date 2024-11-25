#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct vertex {
    float d; 
    int pi;  
    int index; 

    bool operator<(const vertex &v) const {
        if (d == v.d) {
            return index > v.index;
        } else {
            return d > v.d;
        }
    }
};

vector<vector<float>> generateGraph(string filename) {
    ifstream file(filename);
    vector<vector<float>> adjacencyMatrix;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<float> row;
        float value;

        while (ss >> value) {
            row.push_back(value);
        }

        adjacencyMatrix.push_back(row);
    }

    file.close();
    return adjacencyMatrix;
}

vector<vertex> initialize_single_source(vector<vector<float>> &adjacencyMatrix, int source) {
    vector<vertex> vertices;
    int size = adjacencyMatrix.size();

    for (int i = 0; i < size; i++) {
        vertex currentVertex;
        currentVertex.d = numeric_limits<float>::infinity();
        currentVertex.index = i;
        currentVertex.pi = -1;

        vertices.push_back(currentVertex);
    }

    vertices[source].d = 0.0f;
    return vertices;
}

void relax(vertex &u, vertex &v, float weight_u_v) {
    if (u.d != numeric_limits<float>::infinity() && v.d > u.d + weight_u_v) {
        v.d = u.d + weight_u_v;
        v.pi = u.index;
    }
}

vector<vector<float>> reconstructGraph(vector<vertex> &vertices, vector<vector<float>> &adjacencyMatrix, int source) {
    vector<vector<float>> newAdjacencyMatrix(adjacencyMatrix.size(), vector<float>(adjacencyMatrix.size(), 0.0f));

    for (const vertex &v : vertices) {
        if (v.index != source && v.pi != -1) {
            newAdjacencyMatrix[v.pi][v.index] = adjacencyMatrix[v.pi][v.index];
        }
    }

    return newAdjacencyMatrix;
}

vector<vector<float>> dijkstra(vector<vector<float>> &adjacencyMatrix, int source) {
    vector<vertex> vertices = initialize_single_source(adjacencyMatrix, source);
    priority_queue<vertex> Q;

    for (vertex &v : vertices) {
        Q.push(v);
    }

    while (!Q.empty()) {
        vertex u = Q.top();
        Q.pop();

        for (int i = 0; i < adjacencyMatrix.size(); i++) {
            if (adjacencyMatrix[u.index][i] > 0.0f) {
                vertex &v = vertices[i];
                float weight_u_v = adjacencyMatrix[u.index][i];
                float oldDistance = v.d;

                relax(u, v, weight_u_v);

                if (v.d != oldDistance) {
                    Q.push(v);
                }
            }
        }
    }

    return reconstructGraph(vertices, adjacencyMatrix, source);
}

void writeAdjacencyMatrix(vector<vector<float>> &adjacencyMatrix, string filename) {
    ofstream textFile(filename);

    for (const auto &row : adjacencyMatrix) {
        for (size_t j = 0; j < row.size(); j++) {
            textFile << row[j];
            if (j < row.size() - 1) {
                textFile << " ";
            }
        }
        textFile << "\n";
    }

    textFile.close();
}

int main(int argc, char *argv[]) {
    string filename = argv[1];
    int source_node = stoi(argv[2]);
    string output_filename = argv[3];

    vector<vector<float>> adjacencyMatrix = generateGraph(filename);
    vector<vector<float>> newAdjacencyMatrix = dijkstra(adjacencyMatrix, source_node);

    writeAdjacencyMatrix(newAdjacencyMatrix, output_filename);
}
