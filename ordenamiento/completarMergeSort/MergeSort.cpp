#include <fstream>
#include <iostream>
#include <limits>
#include <chrono>
#include <string>
#include <vector>

using namespace std;

// Implementación del pseudocódigo del Cormen
void merge(int A[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1 + 1], R[n2 + 1];
    for(int i = 0; i < n1; i++){
        L[i] = A[p + i];
    }
    for(int i = 0; i < n2; i++){
        R[i] = A[q + i + 1];
    }
    L[n1]= numeric_limits<int>::max();
    R[n2] = numeric_limits<int>::max();

    int i = 0, j = 0;
    for(int k = p; k <= r; k++){
        if(L[i] <= R[j]){
            A[k] = L[i];
            i = i + 1;
        }else{
            A[k] = R[j];
            j = j + 1;
        }
    }
}

void merge_sort(int a[], int inicio, int fin){
    int mitad;
    if (inicio < fin){
        mitad = (inicio + fin) / 2;
        merge_sort(a, inicio, mitad); // Procesa el subarreglo izquierdo
        merge_sort(a, mitad + 1, fin); // Procesa el subarreglo derecho
        merge(a, inicio, mitad, fin); // Unir 
    }
}

void print_array(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
}

// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
    int i, j; 
    for (i = 0; i < n - 1; i++) 
  
        // Last i elements are already 
        // in place 
        for (j = 0; j < n - i - 1; j++) 
            if (arr[j] > arr[j + 1]) 
                swap(arr[j], arr[j + 1]); 
} 

// Function to check if the array is sorted
bool isSorted(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Stupid Sort algorithm
void stupid_sort(int arr[], int size) {
    // Seed the random number generator
    std::srand(std::time(0));
    
    while (!isSorted(arr, size)) {
        // Shuffle the array by randomly swapping elements
        for (int i = 0; i < size; ++i) {
            int j = std::rand() % size;
            std::swap(arr[i], arr[j]);
        }
    }
}

int partition(int a[], int inicio, int fin){
    int x = a[fin];
    int i = inicio - 1;
    for(int j = inicio; j < fin; j++){
        if(a[j] <= x){
            i = i + 1;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[fin]);
    return i + 1;
}

void quick_sort(int a[], int inicio, int fin){
    int q;
    if(inicio < fin){
        q = partition(a, inicio, fin);
        quick_sort(a, inicio, q - 1);
        quick_sort(a, q + 1, fin);
    }
}

int main(int argc, char *argv[])
{
    string s;
    vector<string> archivos{"numbers_10.txt", "numbers_20.txt", "numbers_50.txt", "numbers_100.txt", "numbers_1000.txt", "numbers_10000.txt", "numbers_100000.txt"}; 
    vector<int> n{10, 20, 50, 100, 1000, 100000, 1000000};
    ofstream out;

    // merge sort
    cout << "Merge Sort" << endl;
    out.open("merge_sort_time.csv");
    for (auto archivo : archivos) {
        ifstream in(archivo);
        getline(in, s);
        int n = stoi(s);
        int i = 0;
        int *arregloMergeSort = new int[n];

        if (in.is_open()) {
            while (getline(in, s))
            {
                arregloMergeSort[i] = stoi(s);
                i++;
            }
            in.close();
        }

        auto start = chrono::high_resolution_clock::now();
        merge_sort(arregloMergeSort, 0, n - 1);
        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << archivo << ": " << duration.count() << " micro segundos" << endl;
        out << duration.count() << ",";

        delete[] arregloMergeSort;
        arregloMergeSort = nullptr;
    }

    out.close();


    // bubble sort
    cout << "Bubble Sort" << endl;
    out.open("bubble_sort_time.csv");
    for (auto archivo : archivos) {
        ifstream in(archivo);
        getline(in, s);
        int n = stoi(s);
        int i = 0;
        int *arregloBubbleSort = new int[n];

        if (in.is_open()) {
            while (getline(in, s))
            {
                arregloBubbleSort[i] = stoi(s);
                i++;
            }
            in.close();
        }

        auto start = chrono::high_resolution_clock::now();
        bubbleSort(arregloBubbleSort, n);
        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << archivo << ": " << duration.count() << " micro segundos" << endl;
        out << duration.count() << ",";

        delete[] arregloBubbleSort;
        arregloBubbleSort = nullptr;
    }

    out.close();

    // quick sort
    cout << "Quick Sort" << endl;
    out.open("quick_sort_time.csv");
    for (auto archivo : archivos) {
        ifstream in(archivo);
        getline(in, s);
        int n = stoi(s);
        int i = 0;
        int *arregloQuickSort = new int[n];

        if (in.is_open()) {
            while (getline(in, s))
            {
                arregloQuickSort[i] = stoi(s);
                i++;
            }
            in.close();
        }

        auto start = chrono::high_resolution_clock::now();
        quick_sort(arregloQuickSort, 0, n - 1);
        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << archivo << ": " << duration.count() << " micro segundos" << endl;
        out << duration.count() << ",";

        delete[] arregloQuickSort;
        arregloQuickSort = nullptr;
    }

    out.close();

    // stupid sort
    cout << "Stupid Sort" << endl;
    out.open("stupid_sort_time.csv");
    for (auto archivo : archivos) {
        ifstream in(archivo);
        getline(in, s);
        int n = stoi(s);
        int i = 0;
        int *arregloStupidSort = new int[n];

        if (in.is_open()) {
            while (getline(in, s))
            {
                arregloStupidSort[i] = stoi(s);
                i++;
            }
            in.close();
        }

        auto start = chrono::high_resolution_clock::now();
        stupid_sort(arregloStupidSort, n);
        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        cout << archivo << ": " << duration.count() << " micro segundos" << endl;
        out << duration.count() << ",";

        delete[] arregloStupidSort;
        arregloStupidSort = nullptr;
    }

    out.close();

    return 0;
}