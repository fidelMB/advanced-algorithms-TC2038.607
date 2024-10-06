/*
Autor: Dr. Jesús Guillermo Falcón Cardona
TC2038 Análisis y diseño de algoritmos avanzados
Merge sort
Código para alumnos
Instrucciones: complete las definiciones de las funciones siguientes
de acuerdo con el pseudocódigo de algoritmo Merge Sort. Seguir el
pseudocódigo visto en clase el cual ha sido tomado del libro:
Introduction to algorithms 3rd edition.
*/
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;


// Implementación del pseudocódigo del Cormen
void merge(int A[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = A[p + i];
    }    
    for (int i = 0; i < n2; i++) {
        right[i] = A[r + i + 1];
    }

    int i = 0, j = 0;

    for (int k = p; k < r; i++) {
        if (left[k] <= )
    }
}

void merge_sort(int a[], int inicio, int fin){
    int q = (inicio + fin) / 2;
    merge_sort(a, inicio, q);

    merge_sort(a, q + 1, fin);

    
}

void print_array(int a[], int n){
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
}


int main(int argc, char *argv[])
{
    string filename = argv[1];
    // Leer archivo y construir arreglo.
    /* 
    Recuerde que la primera línea del archivo
    contiene es un número que indica la cantidad
    de elementos a ordenar.
    */
    

    // Imprimir arreglo con los números obtenidos del archivo-
    print_array(arreglo, n);
    
    // Ejecutar merge sort
    cout << "Merge sort" << endl;
    merge_sort(arreglo, 0, n - 1);

    // Imprimir arreglo con los números ordenados.
    print_array(arreglo, n);

}