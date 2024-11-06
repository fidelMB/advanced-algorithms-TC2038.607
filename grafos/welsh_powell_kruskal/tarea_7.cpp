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

// función para encontrar si dos nodos ya se encuentran en el mismo conjunto
int find(int i, int parent[])
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}
 
// unir dos conjuntos para que dos nodos estén en el mismo conjunto
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

// función para hacer matriz de adyancencia con al lista de aristas que regresa kruskal
vector<vector<int>> createAdjacencyMatrix(vector<edge>& edges, int numNodes) {
    vector<vector<int>> adjMatrix(numNodes, vector<int>(numNodes, 0));

    for (edge edge : edges) {
        adjMatrix[edge.u][edge.v] = edge.w;
        adjMatrix[edge.v][edge.u] = edge.w;
    }

    return adjMatrix;
}

// welsh powell, regresa un vector con los colores de cada nodo
vector<int> welsh_powell(vector<vector<int>>& G) {
    int numVertices = G.size();
    vector<int> colors(numVertices, -1);

    vector<pair<int, int>> degreeVertex;
    vector<vector<int>> notNeighbors;
    vector<vector<int>> neighbors;

    int currentDegree;

    for (int i = 0; i < G.size(); i++) {

        currentDegree = 0;
        vector<int> rowNotNeighbors;
        vector<int> rowNeighbors;
        // conseguir grado de este nodo y agregarlo al vector de pares
        for (int j = 0; j < G.size(); j++) {
            if (G[i][j] > 0) {
                currentDegree++;
                rowNeighbors.push_back(j);
            }
            else {
                rowNotNeighbors.push_back(j);
            }

        }

        degreeVertex.push_back({currentDegree, i});
        notNeighbors.push_back(rowNotNeighbors);
        neighbors.push_back(rowNeighbors);
    }

    sort(degreeVertex.rbegin(), degreeVertex.rend());

    int currentColor = 0;

    for (pair<int, int>  vertexPair : degreeVertex) {
        int vertex = vertexPair.second;

        if (colors[vertex] != -1) {
            continue;
        }

        colors[vertex] = currentColor;

        for (int notNeighbor : notNeighbors[vertex]) {

            bool neighborFlag = true;
            // revisar si algún nodo vecino del nodo notNeighbor esta pintado con el color actual
            for (int neighbor : neighbors[notNeighbor]) {
                if (colors[neighbor] == currentColor) {
                    neighborFlag = false;
                }
            }

            if (colors[notNeighbor] == -1 && neighborFlag) {
                colors[notNeighbor] = currentColor;
            }
        }

        currentColor++;
    }

    return colors;
}



int main(int argc, char *argv[]) {

    // generar matriz de adyacencia con el archivo de texto
    vector<vector<int>> G = generateGraph(argv[1]);

    // Imprimir la matriz de adyacencia del grafo original
    cout << "Grafo original:" << endl;
    for (vector<int> row : G) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // crear el árbol recurridor mínimo
    vector<edge> MST = kruskal(G);
    vector<vector<int>> MSTadjacencyMatrix = createAdjacencyMatrix(MST, G.size());

    // Imprimir la matriz de adyacencia del MST
    cout << "\nMatriz de adyacnecia del arbol recurridor minimo:" << endl;
    for (vector<int> row : MSTadjacencyMatrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    // se obtiene el arreglo de colores con welsh powell
    vector<int> colors = welsh_powell(G);

    cout << "\nColo de cada nodo usando welsh powell:" << endl;
    for (int i = 0; i < colors.size(); i++) {
        cout << "Nodo: " << i << " Color: " << colors[i] << endl;
    }

    return 0;
}

// GeeksforGeeks. (2023, 20 marzo). Kruskal’s Algorithm (Simple Implementation for Adjacency Matrix). GeeksforGeeks. https://www.geeksforgeeks.org/kruskals-algorithm-simple-implementation-for-adjacency-matrix/ 

// Singh, A. (2023, 14 julio). Welsh Powell Graph Colouring Algorithm. https://www.tutorialspoint.com/welsh-powell-graph-colouring-algorithm