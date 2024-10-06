#include <fstream>
#include <iostream>


using namespace std;

// Definir Tuple como una clase para contener la respuesta, es decir, el mínimo y el máximo del arreglo.
class Tuple {
  public:
    Tuple(int max, int min) {
      this -> max = max;
      this -> min = min;
    }

    int get_max() {
      return max;
    }

    int get_min() {
      return  min;
    }

  private:
    int min = 0;
    int max = 0;
};


Tuple maximin(int *A, int low, int high){

  // casos base, si el arreglo tiene un tamaño de 1, la tupla de max min se regresa con el mismo valor de max y min
  if (low == high) {
    return Tuple(A[low], A[high]);
  }

  // segundo caso sabe, si el arreglo tiene dos elementos se revisa cuál elemento es el mínimo y máximo y esto se regresa como Tuple
  else if (low + 1 == high) {
    int max_value = max(A[low], A[high]);
    int min_value = min(A[low], A[high]);

    return Tuple(max_value, min_value);
  }

  // si el arreglo no cumple con los casos base se debe de dividir en dos
  int mid = (low + high) / 2;

  // llamada recursiva para encontrar Tuple del subarreglo izquierdo y derecho
  Tuple left_subarray = maximin(A, low, mid);
  Tuple right_subarray = maximin(A, mid + 1, high);

  // encontrar el valor máximo y mínimo entre las dos Tuple
  int max_result = max(left_subarray.get_max(), right_subarray.get_max());
  int min_result = min(left_subarray.get_min(), right_subarray.get_min());

  // Regresar la tupla con el valor máximo y mínimo
  Tuple tuple(max_result, min_result);

  return tuple;
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

    Tuple result = maximin(arreglo, 0, n - 1);
    cout << "El mínimo del arreglo es: " << result.get_min() << " y el máximo es: " << result.get_max() << endl;

    return 0;
}
