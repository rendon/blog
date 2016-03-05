#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char *argv[])
{
    string word;
    cin >> word;
    word[0] = toupper(word[0]);
    cout << word << endl;
    return EXIT_SUCCESS;
}
