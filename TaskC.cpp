#include <iostream>
#include <fstream>
struct SplayTree {
private:
    struct Node {
        long long value = 0;
        Node* left_child = nullptr;
        Node* right_child = nullptr;
        Node* parent = nullptr;
        long long summ = 0;
        int min = 0;
        Node(long long x) : value(x), min(x) {}
    };

    long long sum_(Node* point) {
        return (point == nullptr ? 0 : point->summ);
    }

    void sumfix(Node* point) {
        if (point != nullptr) point->summ = sum_(point->left_child) + sum_(point->right_child) + 1;
        if (point != nullptr) point->min = (point->left_child == nullptr) ? (point->value) : (point->left_child->min);
    }

    Node* root = nullptr;
public:
    void leftRotation(Node* point, Node*& root) {
        Node* child = point->right_child;
        if (point == root) root = child;
        else if (point->value < point->parent->value) point->parent->left_child = child;
        else if (point->value > point->parent->value) point->parent->right_child = child;
        child->parent = point->parent;
        point->parent = child;
        point->right_child = child->left_child;
        child->left_child = point;
        if (point->right_child != nullptr) point->right_child->parent = point;
        sumfix(point);
        sumfix(child);
    }

    void rightRotation(Node* point, Node*& root) {
        Node* child = point->left_child;
        if (point == root) root = child;
        else if (point->value < point->parent->value) point->parent->left_child = child;
        else if (point->value > point->parent->value) point->parent->right_child = child;
        child->parent = point->parent;
        point->parent = child;
        point->left_child = child->right_child;
        child->right_child = point;
        if (point->left_child != nullptr) point->left_child->parent = point;
        sumfix(point);
        sumfix(child);
    }

    void zig(Node* point, Node*& root) {
        if (point->value < point->parent->value) {
            rightRotation(point->parent, root);
        }
        else leftRotation(point->parent, root);
    }

    void zig_zig(Node* point, Node*& root) {
        if (point->value < point->parent->value) {
            rightRotation(point->parent->parent, root);
            rightRotation(point->parent, root);
        }
        else {
            leftRotation(point->parent->parent, root);
            leftRotation(point->parent, root);
        }
    }

    void zig_zag(Node* point, Node*& root) {
        if (point->value > point->parent->value) {
            leftRotation(point->parent, root);
            rightRotation(point->parent, root);
        }
        else {
            rightRotation(point->parent, root);
            leftRotation(point->parent, root);
        }
    }

    Node* splay(Node* point, Node* root) {
        while (point != root) {
            Node* parent = point->parent;
            if (parent == root) zig(point, root);
            else if ((point->value - parent->value) * (parent->value - parent->parent->value) > 0) zig_zig(point, root);
            else zig_zag(point, root);
        }
        return root;
    }

    void add(long long x) {
        Node* temp = new Node(x);
        Node* search = root;//+ 5 + 6 + 8 + 9 + 7
        while (1) {
            if (root == nullptr) {
                root = temp;
                return;
            }
            if (search->value > x) {
                if (search->left_child == nullptr) {
                    search->left_child = temp;
                    temp->parent = search;
                }
                search = search->left_child;
            }
            else if (search->value < x) {
                if (search->right_child == nullptr) {
                    search->right_child = temp;
                    temp->parent = search;
                }
                search = search->right_child;
            }
            else break;
        }
        if (search != temp) {
            delete temp;
            return; ///УБЕРИ ПОТОМ
        }
        root = splay(search, root);
    }


    Node* next(long long x, Node* point) {
        if (point == nullptr) return nullptr;
        if (point->value > x) {
            Node* to_return = next(x, point->left_child);
            return ((to_return == nullptr || to_return->value < x) ? point : to_return);
        }
        else if (point->value < x) {
            return next(x, point->right_child);
        }
        else return point;
    }

    Node* split(Node*& root, long long x) {
        Node* new_tree = next(x, root);
        if (new_tree == nullptr) return nullptr;
        else root = splay(new_tree, root);
        root = new_tree->left_child;
        new_tree->left_child = nullptr;
        if (root != nullptr) root->parent = nullptr;
        sumfix(new_tree);
        return new_tree;
    }

    Node* findmax(Node* root) {
        return (root == nullptr || root->right_child == nullptr ? root : findmax(root->right_child));
    }

    Node* findmin(Node* root) {
        return (root == nullptr || root->left_child == nullptr ? root : findmin(root->left_child));
    }

    Node* merge(Node* left, Node* right) {
        if (left != nullptr) {
            left->right_child = right;
            if (right != nullptr) right->parent = left;
        }
        else left = right;

        return left;
    }

    void extract(long long x) {
        Node* left = split(root, x);
        Node* right = split(left, x + 1);
        root = splay(findmax(root), root);
        root = merge(root, right);
        delete left;
        sumfix(root);
    }
    
    long long kmax(long long k) {
        Node* search = root;
        while (1) {
            if (sum_(search->right_child) > k) search = search->right_child;
            else if (sum_(search->right_child) == k) return search->right_child->min;
            else if (sum_(search->right_child) + 1 == k) {
                root = splay(search, root);
                return search->value;
            }
            else {
                k -= sum_(search->right_child) + 1;
                search = search->left_child;
            }
        }
    }
};

int main()
{
    SplayTree tree;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    long long n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::string s;
        std::cin >> s;
        long long x;
        std::cin >> x;
        if (s == "+1" || s == "1") {
            tree.add(x);
        }
        else if (s == "-1") {
            tree.extract(x);
        }
        else if (s == "0") {
            std::cout << tree.kmax(x);
            std::cout << "\n";
        }
    }
}