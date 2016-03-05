#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> M;
    set<int>::iterator it;
    int i, sum = 0;

    for (i = 3; i < 1000; i += 3) {
        M.insert(i);
    }

    for (i = 5; i < 1000; i += 5) {
        M.insert(i);
    }

    for (it = M.begin(); it != M.end(); it++) {
        sum += *it;
    }

    cout << sum << endl;
    return 0;
}
