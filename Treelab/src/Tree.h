#ifndef TREE_H
#define TREE_H

#include <string>
#include <iostream>
#include <format>

template<typename T>
class Tree {
private:
    struct Node {
        T data;
        size_t str_len;
        Node *left, *right;
        std::string strData;

        explicit Node(T value) : data(value), left(nullptr), right(nullptr) {
            strData = std::to_string(value);
            str_len = strData.length();
        }
    };

    Node *tree;

    Node *recInsert(Node *node, T value);

    void recPrettyPrint(Node *node, size_t spaces, std::ostream &output);

    int calcHeight(Node *node);

    void freeTree(Node *node);

    void recToStringDirect(Node *node, std::string &res);

    void recToStringSymmetric(Node *node, std::string &res);

    void recToStringReverse(Node *node, std::string &res);

    Node *findMin(Node *node);

    Node *removeMin(Node *node);

    Node *recRemove(Node *node, T key);

    void recRightThread(Node *node, Node *&previous, std::string &res);

public:
    Tree();

    Tree(T *arr, size_t size);

    ~Tree();

    void insert(T value);

    void prettyPrint(std::ostream &output = std::cout);

    std::string toStringDirect();

    std::string toStringSymmetric();

    std::string toStringReverse();

    void remove(T key);

    std::string getRightThread();

    int height();
};

template<typename T>
Tree<T>::Tree() {
    tree = nullptr;
}

template<typename T>
Tree<T>::Node *Tree<T>::recInsert(Tree::Node *node, T value) {
    if (node == nullptr)
        return new Node(value);
    if (node->data > value)
        node->left = recInsert(node->left, value);
    else if (node->data < value)
        node->right = recInsert(node->right, value);
    return node;
}

template<typename T>
Tree<T>::Tree(T *arr, size_t size) {
    tree = nullptr;
    for (int i = 0; i < size; ++i) {
        tree = recInsert(tree, arr[i]);
    }
}

template<typename T>
int Tree<T>::calcHeight(Tree::Node *node) {
    if (node == nullptr)
        return 0;
    return std::max(calcHeight(node->right), calcHeight(node->left)) + 1;
}

template<typename T>
int Tree<T>::height() {
    return calcHeight(tree);
}

template<typename T>
void Tree<T>::freeTree(Tree::Node *node) {
    if (node == nullptr)
        return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

template<typename T>
Tree<T>::~Tree() {
    freeTree(tree);
    tree = nullptr;
}

template<typename T>
void Tree<T>::insert(T value) {
    tree = recInsert(tree, value);
}

template<typename T>
void Tree<T>::recPrettyPrint(Tree::Node *node, size_t spaces, std::ostream &output) {
    if (node == nullptr)
        return;
    recPrettyPrint(node->right, spaces + node->str_len + 3, output);
    for (int i = 0; i < spaces; ++i)
        output << " ";
    output << node->data << '\n';
    recPrettyPrint(node->left, spaces + node->str_len + 3, output);
}

template<typename T>
void Tree<T>::prettyPrint(std::ostream &output) {
    recPrettyPrint(tree, 0, output);
}

template<typename T>
void Tree<T>::recToStringDirect(Tree::Node *node, std::string &res) {
    if (node == nullptr)
        return;
    res += node->strData + ' ';
    recToStringDirect(node->left, res);
    recToStringDirect(node->right, res);
}

template<typename T>
std::string Tree<T>::toStringDirect() {
    std::string res = {};
    recToStringDirect(tree, res);
    return !res.empty() ? res.substr(0, res.length() - 1) : res;
}

template<typename T>
void Tree<T>::recToStringSymmetric(Tree::Node *node, std::string &res) {
    if (node == nullptr)
        return;
    recToStringSymmetric(node->left, res);
    res += node->strData + ' ';
    recToStringSymmetric(node->right, res);
}

template<typename T>
std::string Tree<T>::toStringSymmetric() {
    std::string res = {};
    recToStringSymmetric(tree, res);
    return !res.empty() ? res.substr(0, res.length() - 1) : res;
}

template<typename T>
void Tree<T>::recToStringReverse(Tree::Node *node, std::string &res) {
    if (node == nullptr)
        return;
    recToStringReverse(node->left, res);
    recToStringReverse(node->right, res);
    res += node->strData + ' ';
}

template<typename T>
std::string Tree<T>::toStringReverse() {
    std::string res = {};
    recToStringReverse(tree, res);
    return !res.empty() ? res.substr(0, res.length() - 1) : res;
}

template<typename T>
Tree<T>::Node *Tree<T>::findMin(Tree::Node *node) {
    if (node->left == nullptr)
        return node;
    return findMin(node->left);
}

template<typename T>
Tree<T>::Node *Tree<T>::removeMin(Tree::Node *node) {
    if (node->left == nullptr) {
        return node->right;
    }
    node->left = removeMin(node->left);
    return node;
}

template<typename T>
Tree<T>::Node *Tree<T>::recRemove(Tree::Node *node, T key) {
    if (node == nullptr)
        return nullptr;
    if (key < node->data)
        node->left = recRemove(node->left, key);
    else if (key > node->data)
        node->right = recRemove(node->right, key);
    else {
        Node *l = node->left;
        Node *r = node->right;
        delete node;
        if (r == nullptr) {
            return l;
        }
        Node *min = findMin(r);
        min->right = removeMin(r);
        min->left = l;
        return min;
    }
    return node;
}

template<typename T>
void Tree<T>::remove(T key) {
    tree = recRemove(tree, key);
}

template<typename T>
void Tree<T>::recRightThread(Tree::Node *node, Tree::Node *&previous, std::string &res) {
    if (node == nullptr)
        return;
    recRightThread(node->left, previous, res);
    if (previous != nullptr && previous->right == nullptr) {
        res += std::format("{}->{} ", previous->data, node->data);
    }
    previous = node;
    recRightThread(node->right, previous, res);
}

template<typename T>
std::string Tree<T>::getRightThread() {
    std::string res = {};
    Node *previous = nullptr;
    recRightThread(tree, previous, res);
    return !res.empty() ? res.substr(0, res.length() - 1) : res;
}


#endif //TREE_H
