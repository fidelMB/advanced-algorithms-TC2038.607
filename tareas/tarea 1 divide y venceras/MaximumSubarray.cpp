#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

class Result{
    private:
        int low;
        int high;
        int sum;
    public:
        // constructor, índices bajos y altos del subarreglo y la suma del subarreglo
        Result(int low, int high, int sum) {
            this -> low = low;
            this -> high = high;
            this -> sum = sum;
        }

        int get_sum() {
            return sum;
        }
};

Result find_max_crossing_subarray(int *A, int low, int mid, int high){
    
    // encontrar suma del subarreglo izquierdo
    int sum = 0;
    int left_sum = INT_MIN;
    int max_left = 0;

    for (int i = mid; i >= low; i--) {
        sum+= A[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    // encontrar suma del subarreglo derecho
    sum = 0;
    int right_sum = INT_MIN;
    int max_right = 0;
    
    for (int j = mid + 1; j <= high; j++) {
        sum+= A[j];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }

    // regresar la suma de los dos subarreglos
    return Result(max_left, max_right, left_sum + right_sum);
}

Result find_maximum_subarray(int *A, int low, int high){
    // caso base, cuando solamente hay un elemento en el subarreglo
    if (high == low) {
        return Result(low, high, A[low]);
    }   
    else {
        // calcular mitad para dividir el arreglo
        int mid = (low + high) / 2;

        // econtrar el sub arreglo izquierdo derecho y cruzado
        Result result_left_subarray = find_maximum_subarray(A, low, mid);
        Result result_right_subarray = find_maximum_subarray(A, mid + 1, high);
        Result result_crossing_subarray = find_max_crossing_subarray(A, low, mid ,high);

        // comparar los resultados de los subarreglos y regregar el subarreglo con la suma más grande
        int left_sum = result_left_subarray.get_sum();
        int right_sum = result_right_subarray.get_sum();
        int cross_sum = result_crossing_subarray.get_sum();

        if (left_sum >= right_sum && left_sum >= cross_sum) {
            return result_left_subarray;
        }
        else if (right_sum >= left_sum && right_sum >= cross_sum) {
            return result_right_subarray;
        }
        else {
            return result_crossing_subarray;
        }

    }
}

int main(int argc, char *argv[]){
    int n, i;
    string s;
    ifstream in(argv[1]);
    getline(in, s);
    n = stoi(s);
    int *arreglo = new int[n];
    i = 0;
    while (getline(in, s))
    {
        arreglo[i] = stoi(s);
        cout << arreglo[i] << endl;
        i++;
    }

    Result result = find_maximum_subarray(arreglo, 0, n - 1);
    cout << "La suma del máximo subarray es: " << result.get_sum() << endl;

    return 0;
}