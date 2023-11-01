#include <iostream>
#include <cmath>
#include <string>

#define max(a, b) (a > b ? a : b)

struct Node {
    int data, str_len;
    Node *left, *right;
    std::string str;
    bool is_r_thread;

    explicit Node(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
        str = std::to_string(d);
        str_len = str.length();
        is_r_thread = false;
    }
};

Node *insert(Node *curr, int d) {
    if (curr == nullptr)
        return new Node(d);
    if (curr->data > d)
        curr->left = insert(curr->left, d);
    else if (curr->data < d)
        curr->right = insert(curr->right, d);
    return curr;
}

Node *init_tree(Node *node, int *arr, int n) {
    for (int i = 0; i < n; ++i)
        node = insert(node, arr[i]);
    return node;
}

int calc_height(Node *node) {
    if (node == nullptr)
        return 0;
    return max(calc_height(node->right), calc_height(node->left)) + 1;
}

void pprint(Node *n, int spaces) {
    if (n == nullptr)
        return;
    pprint(n->right, spaces + n->str_len + 3);
    for (int i = 0; i < spaces; ++i)
        printf(" ");
    printf("%d\n", n->data);
    pprint(n->left, spaces + n->str_len + 3);
}

void print_direct(Node *root) {
    if (root == nullptr)
        return;
    printf("%d ", root->data);
    print_direct(root->left);
    print_direct(root->right);
}

void print_symmetric(Node *root) {
    if (root == nullptr)
        return;
    print_symmetric(root->left);
    printf("%d ", root->data);
    print_symmetric(root->right);
}

void print_reverse(Node *root) {
    if (root == nullptr)
        return;
    print_reverse(root->left);
    print_reverse(root->right);
    printf("%d ", root->data);
}

Node *pr = nullptr;

void symmetric_thread(Node *root) {
    if (root == nullptr)
        return;
    symmetric_thread(root->left);
    if (pr != nullptr && pr->right == nullptr) {
        pr->right = root;
        pr->is_r_thread = true;
    }
    pr = root;
    symmetric_thread(root->right);
}

Node *find_min(Node *n) {
    if (n->left == nullptr)
        return n;
    return find_min(n->left);
}

Node *remove_min(Node *n) {
    if (n->left == nullptr)
        return n->right;
    n->left = remove_min(n->left);
    return n;
}

Node *remove(Node *n, int key) {
    if (n == nullptr)
        return nullptr;
    if (key < n->data)
        n->left = remove(n->left, key);
    else if (key > n->data)
        n->right = remove(n->right, key);
    else {
        Node *l = n->left;
        Node *r = n->right;
        if (r == nullptr)
            return l;
        Node *min = find_min(r);
        min->right = remove_min(r);
        min->left = l;
        return min;
    }
    return n;
}

void delete_threading(Node *root) {
    if (root == nullptr)
        return;
    delete_threading(root->left);
    if (root->is_r_thread) {
        root->is_r_thread = false;
        root->right = nullptr;
    }
    delete_threading(root->right);
}

void print_threading(Node *root) {
    Node *head = root;
    do {
        while (root->left != nullptr) {
            root = root->left;
        }
        bool flag = true;
        do {
            if (root->is_r_thread)
                printf("%d->%d ", root->data, root->right->data);
            flag = root->is_r_thread;
            root = root->right;
        } while (flag);
    } while (root != nullptr);
}

int main() {
    int n, *arr, key;
    printf_s("Enter arr size:");
    scanf_s("%i", &n);
    arr = new int[n];
    printf_s("Enter arr:");
    for (int i = 0; i < n; ++i)
        scanf_s("%i", &arr[i]);

    Node *tree = nullptr;
    tree = init_tree(tree, arr, n);

    pprint(tree, 0);

    printf_s("direct: ");
    print_direct(tree);

    printf_s("\nsymmetric: ");
    print_symmetric(tree);

    printf_s("\nreverse: ");
    print_reverse(tree);

    symmetric_thread(tree);

    printf_s("\nThread before delete: ");
    print_threading(tree);

    printf_s("\nEnter the key to delete: ");
    scanf_s("%d", &key);

    delete_threading(tree);
    tree = remove(tree, key);
    pr = nullptr;
    symmetric_thread(tree);

    printf_s("\nThread after delete: ");
    print_threading(tree);

    delete[] arr;
}
