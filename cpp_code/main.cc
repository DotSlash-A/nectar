#include <iostream>
#include "lines/slope.h"
using namespace std;

int main() {
    cout << "Hello, C++ world" << endl;
    SlopeCoordinates coords = {1.0, 2.0, 3.0, 6.0};
    double slope = slopecoordinates(coords);
    cout << "Slope: " << slope << endl;
    return 0;
}