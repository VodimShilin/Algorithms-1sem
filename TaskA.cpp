#include <iostream>
#include <string>
#include <set>
#include <ctime>

class AvlTree {
private:
    long long size_ = 0;
    struct Node {
    public:
        Node* parent = nullptr;
        Node* left_child = nullptr;
        Node* right_child = nullptr;
        long long value = 0;
        int height = 1;
        long long count = 0;
        Node(long long value) : value(value) {}
    };
    int height(Node* point) {
        return (point == nullptr) ? (0) : (point->height);
    }

    int bfactor(Node* point) {
        return height(point->left_child) - height(point->right_child);
    }

    void fixHeight(Node* point) {
        point->height = std::max(height(point->left_child), height(point->right_child)) + 1;
    }

    Node* root = nullptr;
public:

    void leftRotation(Node* point) {
        Node* child = point->right_child;
        Node* parent = point->parent;
        if (point == root) {
            root = child;
        }
        else if (point->value < parent->value) {
            parent->left_child = child;
        }
        else {
            parent->right_child = child;
        }
        child->parent = parent;
        point->parent = child;
        point->right_child = child->left_child;
        child->left_child = point;
        if (point->right_child != nullptr) point->right_child->parent = point;
        fixHeight(point);
        fixHeight(child);
    }

    void rightRotation(Node* point) {
        Node* child = point->left_child;
        Node* parent = point->parent;
        if (point == root) {
            root = child;
        }
        else if (point->value < parent->value) {
            parent->left_child = child;
        }
        else {
            parent->right_child = child;
        }
        child->parent = parent;
        point->parent = child;
        point->left_child = child->right_child;
        child->right_child = point;
        if (point->left_child != nullptr) point->left_child->parent = point;
        fixHeight(point);
        fixHeight(child);
    }

    Node* doRotation(Node* point) {
        fixHeight(point);
        if (bfactor(point) == -2) {
            if (bfactor(point->right_child) == 1) rightRotation(point->right_child);
            leftRotation(point);
        }
        else if (bfactor(point) == 2) {
            if (bfactor(point->left_child) == -1) leftRotation(point->left_child);
            rightRotation(point);
        }
        else return point;
        return point->parent;
    }

    void balance(Node* search) {
        while (search != nullptr) {
            fixHeight(search);
            search = doRotation(search);
            search = search->parent;
        }
    }
    /*
    void insert(const long long x) {
        Node* temp = new Node;
        temp->value = x;
        ++temp->count;
        Node* search = root;
        if (search == nullptr) {
            ++size_;
            root = temp;
            return;
        }
        while (search != nullptr) {
            if (x < search->value) {
                if (search->left_child == nullptr) {
                    search->left_child = temp;
                    break;
                }
                search = search->left_child;
            }
            else if (x > search->value) {
                if (search->right_child == nullptr) {
                    search->right_child = temp;
                    break;
                }
                search = search->right_child;
            }
            else {
                delete temp;
                return;
            }
            //++search->parent->height;
        }
        temp->parent = search;
        balance(search);
        ++size_;
        /*search = temp;
        while (search != root) {
            search->parent->height = std::max(search->parent->leftChildHeight(), search->parent->rightChildHeight()) + 1;
            search = search->parent;
            doRotation(search);
        }
        /*
        search = temp;
        while (search != root) {
            search = search->parent;
            doRotation(search);
        }
        
    }   
    */
    void insert(long long x) {
        root = insert(x, root);
    }

    Node* insert(long long x, Node* search) {
        if (search == nullptr) {
            return new Node(x);
        }
        else if (search->value > x) {
            search->left_child = insert(x, search->left_child);
            search->left_child->parent = search;
        }
        else if (search->value < x) {
            search->right_child = insert(x, search->right_child);
            search->right_child->parent = search;
        }
        return doRotation(search);
    }

    bool exists(const long long x) {
        if (root == nullptr) return false;
        Node* search = root;
        while (search->value != x) {
            if (search->value > x) {
                if (search->left_child == nullptr) {
                    return false;
                }
                search = search->left_child;
            }
            else if (search->value < x) {
                if (search->right_child == nullptr) {
                    return false;
                }
                search = search->right_child;
            }
        }
        return true;
    }

    Node* findmin(Node* point) {
        return point->left_child == nullptr ? point : findmin(point->left_child);
    }

    Node* erasemin(Node* point) {
        if (point->left_child == nullptr) return point->right_child;
        else point->left_child = erasemin(point->left_child);
        if (point->left_child != nullptr) point->left_child->parent = point;
        return doRotation(point);
    }

    void extract(long long x) {
        root = extract(x, root);
    }

    Node* extract(long long x, Node* search) {
        if (search == nullptr) return nullptr;
        else if (search->value > x) {
            search->left_child = extract(x, search->left_child);
            if (search->left_child != nullptr) search->left_child->parent = search;
        }
        else if (search->value < x) {
            search->right_child = extract(x, search->right_child);
            if (search->right_child != nullptr) search->right_child->parent = search;
        }
        else {
            Node* parent = search->parent;
            Node* left = search->left_child;
            Node* right = search->right_child;
            delete search;
            if (right == nullptr) return left;
            if (left == nullptr) return right;
            Node* min = findmin(right);
            min->right_child = erasemin(right);
            min->parent = parent;
            min->left_child = left;
            if (min->right_child != nullptr) min->right_child->parent = min;
            if (min->left_child != nullptr) min->left_child->parent = min;
            if (parent == nullptr) root = min;
            else if (min->value > parent->value) parent->right_child = min;
            else parent->left_child = min;
            fixHeight(min);
            return doRotation(min);
        }
        return doRotation(search);
    }
    
    long long next(long long x, bool& exist) {
        Node* search = root;
        long long min = 0;
        while (search != nullptr) {
            if (search->value > x && (exist == false || search->value < min)) {
                min = search->value;
                exist = true;
            }
            search = x < search->value ? search->left_child : search->right_child;
        }
        return min;
    }

    long long prev(long long x, bool& exist) {
        Node* search = root;
        long long max = 0;
        while (search != nullptr) {
            if (search->value < x && (exist == false || search->value > max)) {
                max = search->value;
                exist = true;
            }
            search = x <= search->value ? search->left_child : search->right_child;
        }
        return max;
    }

    void none() {
        std::cout << " ";
    }

    long long size() {
        return size_;
    }
};

int main() {
    AvlTree tree;
     std::string s;
    while (std::cin >> s) {
        long long x;
        std::cin >> x;
        if (s == "insert") {
            tree.insert(x);
        }
        else if (s == "delete") {
            tree.extract(x);
        }
        else if (s == "exists") {
            std::cout << std::boolalpha << tree.exists(x) << std::noboolalpha << "\n" ;

        }
        else if (s == "next") {
            bool exist = false;
            long long to_return = tree.next(x, exist);
            if (exist == false) {
                std::cout << "none" << "\n";
            }
            else std::cout << to_return << "\n";
        }
        else if (s == "prev") {
            bool exist = false;
            long long to_return = tree.prev(x, exist);
            if (exist == false) {
                std::cout << "none" << "\n";
            }
            else std::cout << to_return << "\n";
            
        }
    }
}
