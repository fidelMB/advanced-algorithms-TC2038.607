#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct vertex
{
    // d, pi, e index para saber el indice original porque se va a estar moviendo en la fila de prioridad minima
    int d;
    int pi;
    int index;
    
    // operator overloading para que el min priority queue funcione adecuadamente
    bool operator < (const vertex & v) const {
        if (d == v.d) {
            return index > v.index;
        }
        else {
            return d > v.d;
        }
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

// asignar los valores iniciales de 'd' y 'pi' a cada nodo, al nodo inicial se la asigna 0 en 'd'
vector<vertex> initialize_single_source(vector<vector<int>>& adjacencyMatrix, int source) {
    // tabla de d y pi, el índice equivale al nodo    
    vector<vertex> vertices;
    int size = adjacencyMatrix.size();

    // a cada vertice se le asignan los valores iniciales y se agregan al vector 'vertices'
    for (int i = 0; i < size; i++) {
        vertex currentVertex;
        currentVertex.d = INT_MAX;
        currentVertex.index = i;
        currentVertex.pi = -1;

        vertices.push_back(currentVertex);
    }

    // nodo fuente tiene un valor 'd' de 0
    vertices[source].d = 0;

    return vertices;
}

// función para asingar 'd' y 'pi' cuando se encuentre una mejor ruta
void relax(vertex& u, vertex& v, int weight_u_v) {
    // si el valor 'd' del nodo al que se quiere ir es mayor al valor 'd' del nodo fuente mas el peso de u a v, se asignan nuevos valores de 'd' y 'pi'
    // u.d != INT_MAX para evitar overflow de suma
    if (u.d != INT_MAX && v.d > u.d + weight_u_v) {
        v.d = u.d + weight_u_v;
        v.pi = u.index;
    }
}

// función para reconstruir grafo y hacer una matriz de adyacencia a partir del arreglo de vertices con sus valores de 'd' y 'pi'
vector<vector<int>> reconstructGraph(vector<vertex>& vertices, vector<vector<int>>& adjacencyMatrix, int source) {
    vector<vector<int>> newAdjacencyMatrix;
    
    for (vertex v : vertices) {
        // se crea una fila vacia por cada vertice
        vector<int> row(adjacencyMatrix.size(), 0);
        
        // en case de que se este iterando sobre el nodo fuente se debe de agregar una fila llena de 0's
        if (v.index == source) {
            newAdjacencyMatrix.push_back(row);
            continue;
        }

        // destino, origen, y peso del nodo que se va a agregar a la matriz de adyacencia
        int destination = v.index;
        int origin = v.pi;
        int weight = adjacencyMatrix[destination][origin];
        
        // asignar el peso del nodo destino hasta el fuente
        row[v.pi] = weight;

        newAdjacencyMatrix.push_back(row);
    }

    return newAdjacencyMatrix;
}

// encuentra la mejor ruta hacia un nodo a partir de un nodo, regresa un grafo dirigido aciclíco
vector<vector<int>> dijkstra(vector<vector<int>>& adjacencyMatrix, int source) {
    // tabla de d y pi, el índice equivale al nodo
    vector<vertex> vertices = initialize_single_source(adjacencyMatrix, source);

    int size = vertices.size();

    // cola de prioridad minima considerando el valor 'd' de cada vertice
    priority_queue<vertex> Q;

    // se agregan por referencia los nodos a la cola
    for (vertex& v : vertices) {
        Q.push(v);
    }

    while (!Q.empty()) {
        // quitar vértice del top de la cola
        vertex u = Q.top();
        Q.pop();

        // revisar la matriz de adyacencia por cada nodo al que está conectado a 'u'
        for (int i = 0; i < size; i++) {
            // verificar que el peso no sea 0
            if (adjacencyMatrix[u.index][i] != 0) {
                // obtener el vertice actual con referencia, el peso desde u hasta v y el valor actual de 'd' en caso de que este se actualice
                vertex& v = vertices[i];
                int weight_u_v = adjacencyMatrix[u.index][v.index];
                int oldDistance = v.d;

                // funcion de relax desde u hasta v
                relax(u, v, weight_u_v);

                // si el valor de 'd' fue actualizado el vertice se vuelve a insertar a la cola,
                // estos valores nuevos son los que van a ser considerados para las siguientes iteraciones
                if (v.d != oldDistance) {
                    Q.push(v);
                }
            }
        }
    }
    
    // reconstruir grafo en base al arreglo vertices, la matriz de adyacencia y el nodo fuente
    vector<vector<int>> newAdjacencyMatrix = reconstructGraph(vertices, adjacencyMatrix, source);

    return newAdjacencyMatrix;
}

// función para escribir la matriz de adyacencia en un archivo .txt
void writeAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix, string filename) {
    int size = adjacencyMatrix.size();
    ofstream textFile(filename);

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        textFile << adjacencyMatrix[i][j];
        
        if (j < size - 1) {
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

    vector<vector<int>> adjacencyMatrix = generateGraph(filename);
    int size = adjacencyMatrix.size();

    vector<vector<int>> newAdjancencyMatrix = dijkstra(adjacencyMatrix, source_node);

    writeAdjacencyMatrix(newAdjancencyMatrix, output_filename);
}