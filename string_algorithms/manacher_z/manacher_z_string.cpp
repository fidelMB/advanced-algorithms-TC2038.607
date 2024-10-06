#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;

vector<int> computeZArray(string S) {
    int n = S.size();

    vector<int> Z(n);
    
    int l, r, k = 0;

    for (int i = 1; i < n; i++) {
        // Caso 1: en caso de que i este fuera de la "Z box"
        if (i > r) {
            l = i;
            r = i;

            while (r < n && S[r - l] == S[r]) {
                r = r + 1;
            }

            Z[i] = r - l;
            r = r - 1;
        }
        // si i está dentro de la Z box
        else {
            k = i - l;

            // Caso 2: el tamaño del substring actual dentro de la z box es MAYOR al valor z en la posición k, esto
            // significa que NO ES posible que haya un prefijo más grande después de la z box
            if (Z[k] < r - i + 1) {
                Z[i] = Z[k];
            }
            // Caso 3: el tamaño del substring actual dentro de la z box es MENOR O IGUAL al valor z en la posición k, esto
            // significa que ES posible que haya un prefijo más grande después de la z box
            else if (Z[k] >= r - i + 1) {
                l = i;

                while (r < n && S[r - l] == S[r]) {
                    r = r + 1;
                }

                Z[i] = r - l;
                r = r - 1;
            }
        }
    }

    return Z;
}

unordered_set<int> Z(string T, string P) {
    // crear vector que almacena los índices en donde se encuentra el patrón dado
    unordered_set<int> indexes;


    string S = P + "$" + T;

    int n = S.size();
    int Psize = P.size();

    vector<int> Z = computeZArray(S);

    for (int i = 0; i < n; i++) {
        if (Z[i] == Psize) {
            indexes.insert(i - Psize - 1);
        }
    }

    return indexes;
}

string computeManacherString(string T) {
    string manacherString = "";
    
    for (int i = 0; i < T.size(); i++) {
        manacherString = manacherString + "#" + T[i];
    }

    manacherString =  "@" + manacherString + "#&";

    return manacherString;
}

string longestPalindromicSubstring(string T) {
    string manacherString = computeManacherString(T);

    vector<int> P(manacherString.size());

    int C, R = 0;
    int maxIndex, maxSize = 0;

    // encontrar el centro de la subcadena palíndromo más grande
    for (int i = 1; i < manacherString.size() - 1; i++) {
        int mirror = 2 * C - i;

        if (i < R) {
            P[i] = min(R - i, P[mirror]);
        }

        while (manacherString[i + (1 + P[i])] == manacherString[i - (1 + P[i])]) {
            P[i]++;
        }

        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }

        // revisar si el centro actual es el más grande
        if (P[i] > maxSize) {
            maxIndex = i;
            maxSize = P[i];
        }
    }

    // reconstruir string en base al centro
    int iter = maxSize / 2;
    string palindrome(1, manacherString[maxIndex]);
    int rightIndex, leftIndex;

    for (int i = 1; i <= iter; i++) {
        rightIndex = maxIndex + (2 * i);
        leftIndex = maxIndex - (2 * i);

        palindrome = manacherString[leftIndex] + palindrome + manacherString[rightIndex];    
    }

    return palindrome;
}

void generateHighlightedHTML(const string& input, unordered_set<int> indexes, const string& filename, int stringSize) {
    ofstream htmlFile(filename, ios::trunc);
    
    htmlFile << "<!DOCTYPE html>\n";
    htmlFile << "<html>\n";
    htmlFile << "<head>\n";
    htmlFile << "<style>\n";
    htmlFile << ".highlight { background-color: yellow; }\n";
    htmlFile << "</style>\n";
    htmlFile << "<title>Highlighted String</title>\n";
    htmlFile << "</head>\n";
    htmlFile << "<body>\n";
    htmlFile << "<p>\n";

    int i = 0;
    while (i < input.size()) {
        if (indexes.count(i)) {
            htmlFile << "<span class='highlight'>";
            
            for (int j = 0; j < stringSize && (i + j) < input.size(); j++) {
                htmlFile << input[i + j];
            }
            
            htmlFile << "</span>";
            i += stringSize;
        } else {
            htmlFile << input[i];
            i++;
        }
    }

    htmlFile << "</p>\n";
    htmlFile << "</body>\n";
    htmlFile << "</html>\n";

    htmlFile.close();
    
    cout << "HTML file generated successfully and rewritten from scratch: " << filename << endl;
}


int main(int argc, char *argv[]) {

    // abrir archivo
    ifstream file(argv[1]);

    // almacenar texto del archivo en una variable tipo string
    stringstream buffer;
    buffer << file.rdbuf();
    string text = buffer.str();
    file.close();
    
    // encontrar palíndromo y los índices en donde se encuentra
    string palindrome = longestPalindromicSubstring(text);
    unordered_set<int> indexes = Z(text, palindrome);
    
    // genera archivo HTML con el palíndromo subrayado dentro del texto
    generateHighlightedHTML(text, indexes, "output.html", palindrome.size());
}