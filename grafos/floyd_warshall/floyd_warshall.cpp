#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#define INF 99999
using namespace std;

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

vector<vector<int>> createPiMatrix(vector<vector<int>>& adjacencyMatrix) {
    int n = adjacencyMatrix.size();

    vector<vector<int>> pi;

    for (int i = 0; i < n; i++) {
        vector<int> row;

        for (int j = 0; j < n; j++){
            // nulo si i = j o w[i][j] == infinito
            if (i == j || adjacencyMatrix[i][j] == INF) {
                row.push_back(-1);
            }
            // i si i != j y w[i][j] < infinito
            else if ( i != j && adjacencyMatrix[i][j] < INF) {
                row.push_back(i);
            }
        }
        pi.push_back(row);
    }

    return pi;
}

vector<vector<int>> createDp(vector<vector<int>>& adjacencyMatrix) {
    int n = adjacencyMatrix.size();

    vector<vector<int>> dp;

    for (int i = 0; i < n; i++) {
        vector<int> row;

        for (int j = 0; j < n; j++){
            // 0 si i == j
            if (i == j) {
                row.push_back(0);
            }
            // infinito si i != j y (i, j) 
            else if (i != j && adjacencyMatrix[i][j] != 0) {
                row.push_back(adjacencyMatrix[i][j]);
            }
            // w[i][j] si
            else if (i != j && adjacencyMatrix[i][j] == 0) {
                row.push_back(INF);
            }
        }
        dp.push_back(row);
    }

    return dp;   
}


pair<vector<vector<int>>, vector<vector<int>>> floyd_warshall(vector<vector<int>>& adjacencyMatrix) {
    int n = adjacencyMatrix.size();

    vector<vector<int>> pi = createPiMatrix(adjacencyMatrix);
    vector<vector<int>> dp = createDp(adjacencyMatrix);

    cout << "PI:" << endl;
    for (int i = 0; i < pi.size(); i++) {
        cout << i << " : ";
        for (int j = 0; j < pi.size(); j++)
        cout << pi[i][j] << " ";
        cout << "\n";
    }
    
    cout << "DP:" << endl;
    for (int i = 0; i < dp.size(); i++) {
        cout << i << " : ";
        for (int j = 0; j < dp.size(); j++)
        cout << dp[i][j] << " ";
        cout << "\n";
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    pi[i][j] = pi[k][j];
                }
            }
        }
    }

    pair<vector<vector<int>>, vector<vector<int>>> pi_dp = {pi, dp};

    return pi_dp;
}


int main(int argc, char *argv[]) {

    vector<vector<int>> adjacencyMatrix = generateGraph(argv[1]);

    pair<vector<vector<int>>, vector<vector<int>>> pi_dp = floyd_warshall(adjacencyMatrix);

    vector<vector<int>> pi = pi_dp.first;
    vector<vector<int>> dp = pi_dp.second;

    cout << "PI:" << endl;
    for (int i = 0; i < pi.size(); i++) {
        cout << i << " : ";
        for (int j = 0; j < pi.size(); j++)
        cout << pi[i][j] << " ";
        cout << "\n";
    }
    
    cout << "DP:" << endl;
    for (int i = 0; i < dp.size(); i++) {
        cout << i << " : ";
        for (int j = 0; j < dp.size(); j++)
        cout << dp[i][j] << " ";
        cout << "\n";
    }

    
}