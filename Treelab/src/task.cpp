#pragma ide diagnostic ignored "misc-no-recursion"

#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "Tree.h"

template<typename T>
void input(T &variable, const std::string &promptStr, char delim) {
    bool isWrongInput;
    do {
        std::cout << promptStr;
        std::cin >> variable;

        isWrongInput = std::cin.fail();
        if (isWrongInput) {
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), delim);
        isWrongInput = isWrongInput || std::cin.gcount() > 1;
    } while (isWrongInput);
}

int main() {
    int n, key;

    input(n, "Enter arr size:", '\n');
    auto arr = std::make_unique<int[]>(n);
    for (int i = 0; i < n; ++i)
        input(arr[i], "Enter arr[" + std::to_string(i) + "]:", '\n');

    auto tree = Tree(arr.get(), n);

    std::cout << "pretty print:\n";
    tree.prettyPrint();

    std::cout << "\ndirect: " << tree.toStringDirect();

    std::cout << "\nsymmetric: " << tree.toStringSymmetric();

    std::cout << "\nreverse: " << tree.toStringReverse();

    std::cout << "\nThread before delete: " << tree.getRightThread();

    input(key, "\nEnter the key to delete:", '\n');

    tree.remove(key);

    std::cout << "Thread after delete: " << tree.getRightThread();
}