#include <iostream>
#include <vector>

using namespace std;

int max_subarray(vector<int> &numbers) {

    vector<int> dp(numbers.size()); // vector para almacenar la suma de los subarreglos hasta la posición de cada índice
    dp[0] = numbers[0]; 
    int maxSum = dp[0];

    for(int i = 1; i < numbers.size(); i++) {
        dp[i] = max(numbers[i], dp[i - 1] + numbers[i]); // sumar el número actual la suma del subarreglo anterior
        maxSum = max(maxSum, dp[i]); // actualizar la suma máxima
    }

    return maxSum;
}

int main() {
    // prueba de escritorio
    vector<int> numbers = {-3, 10, -2, 4}; 

    cout << max_subarray(numbers) << endl;
    return 0;
}