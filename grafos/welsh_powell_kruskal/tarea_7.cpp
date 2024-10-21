#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct edge {
    int u;
    int v;
    int w;

    // operator overloading para ordenar las aristas por peso (w)
    bool operator < (const edge& str) const {
        return (w < str.w);
    }
};

// función para generar una matriz de adyacencia en base a un archivo .txt
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

int find(int i, int parent[])
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}
 
// Does union of i and j. It returns
// false if i and j are already in same
// set.
void union1(int i, int j, int parent[])
{
    int a = find(i, parent);
    int b = find(j, parent);
    parent[a] = b;
}
 
vector<edge> kruskal(vector<vector<int>>& G) {

    int parent[G.size()];

    // crear subconjuntos por cada nodo
    for (int i = 0; i < G.size(); i++) {
        parent[i] = i;
    }

    vector<edge> edgeList;

    // añadir todos las aristas a un arreglo para luego ordenarlo y empezar con kruskal
    for (int i = 0; i < G.size(); i++) {
        for (int j = 0; j < G.size(); j++) {
            if (G[i][j] > 0) {
                edge currentEdge;
                currentEdge.u = i;
                currentEdge.v = j;
                currentEdge.w = G[i][j];

                edgeList.push_back(currentEdge);
            }
        }
    }

    // ordenar con la lista de aristas de manera non-decreasing
    sort(edgeList.begin(), edgeList.end());

    // lista de aristas del arbol final
    vector<edge> MST;

    for (edge edge : edgeList) {
        if (find(edge.u, parent) != find(edge.v, parent)) {
            union1(edge.u, edge.v, parent);
            MST.push_back(edge);
        }
    }

    return MST;
}

// funcion para hacer matriz de adyancencia con al lista de aristas que regresa kruskal
vector<vector<int>> createAdjacencyMatrix(vector<edge>& edges, int numNodes) {
    vector<vector<int>> adjMatrix(numNodes, vector<int>(numNodes, 0));

    for (edge edge : edges) {
        adjMatrix[edge.u][edge.v] = edge.w;
        adjMatrix[edge.v][edge.u] = edge.w;
    }

    return adjMatrix;
}

// welsh-powell
vector<int> welsh_powell(vector<vector<int>>& G) {
    int numVertices = G.size();
    vector<int> colors(numVertices, -1);

    vector<pair<int, int>> degreeVertex;
    vector<vector<int>> adjList;

    int currentDegree;

    for (int i = 0; i < G.size(); i++) {

        currentDegree = 0;
        vector<int> row;
        // conseguir grado de este nodo y agregar lo al vector de pares
        for (int j = 0; j < G.size(); j++) {
            if (G[i][j] > 0) {
                currentDegree++;
                row.push_back(j);
            }
        }

        degreeVertex.push_back({currentDegree, i});
        adjList.push_back(row);
    }

    sort(degreeVertex.rbegin(), degreeVertex.rend());

    int currentColor = 0;

    for (pair<int, int>  vertexPair : degreeVertex) {
        int vertex = vertexPair.second;

        if (colors[vertex] != -1) {
            continue;
        }

        colors[vertex] = currentColor;

        for (int neighbor : adjList[vertex]) {
            if (colors[neighbor] == -1) {
                colors[neighbor] = currentColor;
            }
        }

        currentColor++;
    }

    return colors;
}



int main(int argc, char *argv[]) {

    vector<vector<int>> G = generateGraph(argv[1]);

    
    vector<edge> MST = kruskal(G);

    vector<vector<int>> MSTadjacencyMatrix = createAdjacencyMatrix(MST, G.size());

    // Imprimir la matriz de adyacencia del MST
    for (vector<int> row : MSTadjacencyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    vector<int> colors = welsh_powell(G);

    for (int i = 0; i < colors.size(); i++) {
        cout << "Vertex: " << i << " Color: " << colors[i] << endl;
    }

    return 0;
}