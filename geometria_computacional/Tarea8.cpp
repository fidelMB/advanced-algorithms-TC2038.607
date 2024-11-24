#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <stack>

using namespace std;

struct point {
    float x;
    float y;
    float theta;
    int index;

    point(float x_val, float y_val, int index_val) {
        x = x_val;
        y = y_val;
        theta = 0;
        index = index_val;
    }
};

// consigue el next to top del stack
point next_to_top(stack<point> S) {
    point top = S.top();
    S.pop();

    point next_to_top = S.top();
    S.push(top);

    return next_to_top;
}

// función para usarla en sort y ordenar el vector 
bool is_smaller_theta(const point& point1, const point& point2) { return point1.theta < point2.theta; }

// returns rotating angle from p0 towards p2
string getRotatingDirection(point p0, point p1, point p2) {
    string direction = "";

    point p0p2(p2.x - p0.x, p2.y - p0.y, 0);

    point p0p1(p1.x - p0.x, p1.y - p0.y, 0);

    // P0P2 X P0P1
    float result = (p0p2.x * p0p1.y) - (p0p2.y * p0p1.x);

    if (result < 0) {
        direction = "left";
    }
    else if (result > 0) {
        direction = "right";
    }
    else {
        direction = "collinear";
    }

    return direction; 
}

// calcula el ángulo polar (en radianes) entre el punto fuente y otro punto
void calculatePolarAngle(point& sourcePoint, point& targetPoint) {
    float theta = atan2((targetPoint.y - sourcePoint.y), (targetPoint.x - sourcePoint.x));

    targetPoint.theta = theta;
}

// lee el archivo de texto, consigue el punto pivote (el que tenga el valor de y más pequeño y si hay empate el que tenga el más pequeño de x)
// consigue el ángulo polar desde el punto pivote hacia los demás puntos y se ordena el vector de menor a mayor ángulo
vector<point> readAndSortPoints(string filename) {
    ifstream file(filename);
    vector<point> pointList;
    string line;

    int index = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        float x, y;

        if (ss >> x && ss.ignore(1) && ss >> y) {
            point currentPoint(x, y, index);
            pointList.push_back(currentPoint);
        }

        index++;
    }

    file.close();

    float minY = INT_MAX;
    int minYIndex;

    // obtener el punto pivote inicial, se obtiene el punto con el menor valor de Y, si hay un empate se escoge el que tenga 
    // el valor de X más pequeño
    for (int i = 0; i < pointList.size(); i++) {
        if (pointList[i].y < minY) {
            minY = pointList[i].y;
            minYIndex = i;
        }
        else if (pointList[i].y == minY) {
            if (pointList[i].x < pointList[minYIndex].x) {
                minY = pointList[i].y;
                minYIndex = i;
            }
        }
    }

    // conseguir el ángulo theta de cada punto respecto al punto pivote
    for (int i = 0; i < pointList.size(); i++) {
        if (pointList[i].index == minYIndex) {
            continue;
        }

        calculatePolarAngle(pointList[minYIndex], pointList[i]);
    }

    // ordernar los puntos por su valor de theta respecto al punto pivote
    sort(pointList.begin(), pointList.end(), is_smaller_theta);


    return pointList;
}

// graham scan, regresa el stack con los puntos que forman el cierre convexo
stack<point> grahamScan(string filename) {
    vector<point> points = readAndSortPoints(filename);
    stack<point> S;

    if (points.size() < 2) {
        return stack<point>();
    }
    else {
        S.push(points[0]);
        S.push(points[1]);
        S.push(points[2]);

        for (int i = 3; i < points.size(); i++) {
            // mientras la direccion de rotacion que forma el angulo de los 3 puntos sea a la derecha se hace pop del stack
            while (getRotatingDirection(next_to_top(S), S.top(), points[i]) == "right") {
                S.pop();
            }
            // push del punto actual
            S.push(points[i]);
        }

    }

    return S;
}

int main(int argc, char *argv[]) {

    //llamar graham scan
    stack<point> pointStack = grahamScan(argv[1]);

    // escribir los puntos de la pila en un .txt
    ofstream outputFile(argv[2]);

    point startPoint = pointStack.top();

    while (!pointStack.empty()) {
        point p = pointStack.top();
        pointStack.pop();
        outputFile << p.x << "," << p.y << endl;
    }
    outputFile << startPoint.x << "," << startPoint.y;

    outputFile.close();
    
    return 0;
}