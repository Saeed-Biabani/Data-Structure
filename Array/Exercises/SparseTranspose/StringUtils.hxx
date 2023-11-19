#include <iostream>
#include <vector>

using namespace std;

template <typename _T>
vector<_T> Split(string str, const char delim, size_t part) {
    vector<_T> bag;
    int indx;

    for (int i = 0; i < part; i++) {
        indx = str.find(delim);
        bag.push_back(stoi(str.substr(0, indx)));
        str = str.substr(indx + 1, str.length());
    }

    return bag;
}