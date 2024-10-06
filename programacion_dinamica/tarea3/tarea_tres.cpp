#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Solución bottom up
vector<int> findCoinCount(vector<int> coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX); // vector de memoización bottom up para saber la cantidad de monedas necesarias para cada cantidad desde 0 hasta amount
    vector<vector<int>> coinCount(amount + 1, vector<int>(coins.size(), 0)); // vector para saber la cantidad de cada moneda para cada cantidad desde 0 hasta amount

    dp[0] = 0; // para la cantidad 0 se necesitan 0 monedas

    // iterar desde la cantidad de 1 hasta amount para encontrar la mínima cantidad de monedas para cada valor y las monedas que se utilizarán para cada valor
    for (int i = 1; i <= amount; i++) {
        // revisa cada moneda
        for (int j = 0; j < coins.size(); j++) {
            // condición para verificar que la resta no dará un número negativo
            if (i >= coins[j] && dp[i - coins[j]] != INT_MAX) {
                // revisar si la suma con esta moneda da una menor cantidad de monedas utilizadas
                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                    coinCount[i] = coinCount[i - coins[j]]; // copia el vector de monedas utilizadas de la solución i
                    coinCount[i][j]++; // se le suma uno a la moneda que se está utilizando
                }
            }
        }
    }

    // regresar un vector vacío si no se encuentra una solución
    if (dp[amount] == INT_MAX) {
        return {};
    }

    return coinCount[amount];
}

int main(int argc, char *argv[]) {

    // leer precio del objeto y las monedas que da el usuario
    int price_product = stoi(argv[1]);
    int coins_given = stoi(argv[2]);

    int amount = coins_given - price_product;

    // leer archivo de entrada con las monedas
    ifstream file(argv[3]);
    int numCoins;
    file >> numCoins;

    vector<int> coins(numCoins);

    for (int i = 0; i < numCoins; i++) {
        file >> coins[i];
    }

    file.close();

    sort(coins.begin(), coins.end());

    vector<int> coinCount = findCoinCount(coins, amount);

    for (int coin : coinCount) {
        cout << coin << endl;
    }

    if (coinCount.empty()) {
        cout << "No existe solucion" << endl;
        return 1;
    }

    ofstream outputFile("output.txt");

    for (int i = 0; i < coins.size(); i++) {
        outputFile << coins[i] << " " << coinCount[i] << endl;
    }

    outputFile.close();
    return 0;
}