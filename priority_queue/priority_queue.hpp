#include <deque>
#include <algorithm>

template <class T = int> 
class Node: public std::enable_shared_from_this<Node<T>> {
public:
    T value;
    std::shared_ptr<Node<T>> parent;
    std::shared_ptr<Node<T>> left_child;
    std::shared_ptr<Node<T>> right_child;
    bool inq;

    Node(T value_) : value(value_), parent(nullptr), left_child(nullptr), right_child(nullptr), inq(false) {}

    Node() = default;

    // 上调
    void heapify_up() {
        auto cur = this->shared_from_this();
        while (cur->parent != nullptr && cur->parent->value < cur->value) {
            std::swap(cur->value, cur->parent->value);
            cur = cur->parent;
        }
    }

    // 沉底
    void heapify_down() {
        auto cur = this->shared_from_this();
        while (cur->left_child != nullptr) {
            auto& bigger = (cur->right_child != nullptr && cur->right_child->value > cur->left_child->value) ? cur->right_child : cur->left_child;
            if (bigger->value > cur->value) {
                std::swap(cur->value, bigger->value);
                cur = bigger;
            } else {
                break;
            }
        }
    }

    // 简化析构函数，智能指针会自动处理
    ~Node() = default;
};

// 大根堆
template <class T = int>
class PriorityQueue{
public:
    
    PriorityQueue() {
        n = 0;
        root = nullptr;
    }

    int size() { return n; }

    void push(const T& x) {
        n++;
        std::shared_ptr<Node<T>> newnode = std::make_shared<Node<T>>(x);
        if (root == nullptr) {
            root = newnode;
            leave.push_back(newnode);
            newnode->inq = true;
        } 
        else {
            auto leaf = leave.front();
            if (leaf->left_child == nullptr) {
                leaf->left_child = newnode;
                newnode->parent = leaf;
                leave.push_back(newnode);
                newnode->inq = true;
            }
            else if (leaf->right_child == nullptr){
                leaf->right_child = newnode;
                newnode->parent = leaf;
                leave.push_back(newnode);
                newnode->inq = true;
            }
            else {
                throw std::out_of_range("there's not a leaf");
            }

            if (leaf->left_child == nullptr || leaf->right_child == nullptr);
            else {
                leaf->inq = false;
                leave.pop_front();
            }
            newnode->heapify_up();
        }
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Heap is empty, cannot pop.");
        }

        std::swap(root->value, leave.back()->value);
        auto tmp = leave.back();
        leave.pop_back();
        n--;

        if (root == tmp) {
            root = nullptr;
        } 
        else {
            auto parent = tmp->parent;
            if (parent->left_child == tmp) {
                parent->left_child = nullptr;
            } else {
                parent->right_child = nullptr;
            }

            if (parent->inq == false) {
                parent->inq = true;
                leave.push_front(parent);
            }

            root->heapify_down();
        }
    }

    T top() {
        return root->value;
    }

    bool empty() {
        return n == 0;
    }

private:
    size_t n;
    std::shared_ptr<Node<T>> root;
    std::deque<std::shared_ptr<Node<T>>> leave;  // 维护所有叶子结点
};