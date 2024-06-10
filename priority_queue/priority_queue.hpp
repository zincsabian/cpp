#include <vector>
#include <deque>
#include <iostream>
#include <functional>
#include <algorithm>

template <class T = int> 
class Node {
public:
    T value;
    Node<T>* parent;
    Node<T>* left_child;
    Node<T>* right_child;
    bool inq;

    Node(T value_) : value(value_){
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
        inq = false;
    };
    Node() = default;

    // 上调
    void heapify_up() {
        auto* cur = this;
        for(; cur->parent != nullptr; ) {
            if (cur->parent->value < cur->value)
                std::swap(cur->value, cur->parent->value);
            else 
                break; 
            cur = cur->parent;
        }
    }

    // 沉底
    void heapify_down() {
        auto* cur = this;
        for(; cur->left_child != nullptr; ) {
            auto* bigger = cur->left_child; 
            if (cur->right_child != nullptr && cur->right_child->value > bigger->value) { 
                bigger = cur->right_child;
            }
            if (bigger->value > cur->value) { 
                std::swap(bigger->value, cur->value); 
                cur = bigger; 
            }
            else {
                break;
            }
        }
    }

    ~Node() {
        auto* cur = this;
        cur->parent = nullptr;
        cur->left_child = nullptr;
        cur->right_child = nullptr;
        inq = false;
    }
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
        Node<T>* newnode = new Node<T>(x);
        if (root == nullptr) {
            root = newnode;
            leave.push_back(newnode);
            newnode->inq = true;
        } 
        else {
            auto* leaf = leave.front();
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
        auto* tmp = leave.back();
        leave.pop_back();
        n--;

        if (root == tmp) {
            delete root;
            root = nullptr;
        } 
        else {
            auto* parent = tmp->parent;
            if (parent->left_child == tmp) {
                parent->left_child = nullptr;
            } else {
                parent->right_child = nullptr;
            }

            if (parent->inq == false) {
                parent->inq = true;
                leave.push_front(parent);
            }

            delete tmp;
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
    Node<T>* root;
    std::deque<Node<T>*> leave;  // 维护所有叶子结点
};