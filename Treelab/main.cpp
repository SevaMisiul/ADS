#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include <iostream>
#include <string>
#include <memory>

#define max(a, b) ((a) > (b) ? (a) : (b))

struct Node {
    int data;
    size_t str_len;
    Node *left, *right;
    std::string str;
    bool is_r_thread;

    explicit Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        is_r_thread = false;
        str_len = std::to_string(value).length();
    }
};

Node *insert(Node *node, int d) {
    if (node == nullptr)
        return new Node(d);
    if (node->data > d)
        node->left = insert(node->left, d);
    else if (node->data < d)
        node->right = insert(node->right, d);
    return node;
}

Node *arrToTree(Node *node, int *arr, int n) {
    for (int i = 0; i < n; ++i)
        node = insert(node, arr[i]);
    return node;
}

int calcHeight(Node *node) {
    if (node == nullptr)
        return 0;
    return max(calcHeight(node->right), calcHeight(node->left)) + 1;
}

void prettyPrint(Node *node, size_t spaces) {
    if (node == nullptr)
        return;
    prettyPrint(node->right, spaces + node->str_len + 3);
    for (int i = 0; i < spaces; ++i)
        std::cout << " ";
    std::cout << node->data << '\n';
    prettyPrint(node->left, spaces + node->str_len + 3);
}

void printDirect(Node *node) {
    if (node == nullptr)
        return;
    std::cout << node->data << ' ';
    printDirect(node->left);
    printDirect(node->right);
}

void printSymmetric(Node *node) {
    if (node == nullptr)
        return;
    printSymmetric(node->left);
    std::cout << node->data << ' ';
    printSymmetric(node->right);
}

void printReverse(Node *node) {
    if (node == nullptr)
        return;
    printReverse(node->left);
    printReverse(node->right);
    std::cout << node->data << ' ';
}

void rightThread(Node *node, Node *&previous) {
    if (node == nullptr)
        return;
    rightThread(node->left, previous);
    if (previous != nullptr && previous->right == nullptr) {
        previous->right = node;
        previous->is_r_thread = true;
    }
    previous = node;
    rightThread(node->right, previous);
}

Node *findMin(Node *node) {
    if (node->left == nullptr)
        return node;
    return findMin(node->left);
}

Node *removeMin(Node *node) {
    if (node->left == nullptr) {
        return node->right;
    }
    node->left = removeMin(node->left);
    return node;
}

Node *remove(Node *node, int key) {
    if (node == nullptr)
        return nullptr;
    if (key < node->data)
        node->left = remove(node->left, key);
    else if (key > node->data)
        node->right = remove(node->right, key);
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

void deleteThread(Node *node) {
    if (node == nullptr)
        return;
    deleteThread(node->left);
    if (node->is_r_thread) {
        node->is_r_thread = false;
        node->right = nullptr;
    }
    deleteThread(node->right);
}

void printThread(Node *node) {
    while (node != nullptr) {
        while (node->left != nullptr) {
            node = node->left;
        }
        bool flag;
        do {
            if (node->is_r_thread)
                printf("%d->%d ", node->data, node->right->data);
            flag = node->is_r_thread;
            node = node->right;
        } while (flag);
    }
}

void freeTree(Node *node) {
    while (node != nullptr) {
        while (node->left != nullptr) {
            node = node->left;
        }
        bool flag;
        do {
            flag = node->is_r_thread;
            Node *tmp = node->right;
            delete node;
            node = tmp;
        } while (flag);
    }
}

int main() {
    int n, key;
    std::unique_ptr<int[]> arr;
    Node *previous = nullptr;

    std::cout << "Enter arr size:";
    std::cin >> n;
    arr = std::make_unique<int[]>(n);
    std::cout << "Enter arr:";
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];

    Node *tree = nullptr;
    tree = arrToTree(tree, arr.get(), n);

    std::cout << "pretty print:\n";
    prettyPrint(tree, 0);

    std::cout << "\ndirect: ";
    printDirect(tree);

    std::cout << "\nsymmetric: ";
    printSymmetric(tree);

    std::cout << "\nreverse: ";
    printReverse(tree);

    rightThread(tree, previous);

    std::cout << "\nThread before delete: ";
    printThread(tree);

    std::cout << "\nEnter the key to delete:";
    std::cin >> key;

    deleteThread(tree);
    tree = remove(tree, key);

    previous = nullptr;
    rightThread(tree, previous);

    std::cout << "Thread after delete: ";
    printThread(tree);
    freeTree(tree);
}