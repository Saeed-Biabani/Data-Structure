#include <iostream>

#include "Sparse.hxx"

using namespace std;

int main(int argc, const char** argv) {
    Sparse<int> sparse;

    sparse.LoadMatrixFromFile("Input.txt");
    sparse.View();

    auto trandpose = sparse.Transpose();
    trandpose.View();

    return 0;
}