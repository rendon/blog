#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

class Archimedes
{
public:
    double approximatePi(int numSides) {
        double pi = acos(-1);
        double angle = 2 * pi / numSides;
        return numSides * sin(angle / 2);
    }
};

int main()
{
    Archimedes archimedes;
    cout << archimedes.approximatePi(4) << endl;
    return 0;
}
