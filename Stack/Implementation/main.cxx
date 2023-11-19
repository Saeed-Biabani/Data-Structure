#include <iostream>

#include "Stack.hxx"

using namespace std;

int main(int argc, const char** argv) {
    Stack<int, 10> stack;

    stack.Push(1);
    stack.Push(2);
    stack.Push(3);

    stack.View();

    return 0;
}