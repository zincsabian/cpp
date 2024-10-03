#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <cstddef>

template <class T>
class UniquePtr {
private:
    T* ptr_;
public:
    UniquePtr() noexcept : ptr_(nullptr) {}
    explicit UniquePtr(T* ptr) noexcept: 
        ptr_(ptr) {}
    ~UniquePtr() {
        delete ptr_;
    }

    // delete copy constructor && assignment operator
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    // Move constructor & assignment operator
    UniquePtr(UniquePtr&& other) noexcept {
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Accessors
    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }

    // checker
    bool operator==(std::nullptr_t) const noexcept { return ptr_ == nullptr; }
    bool operator!=(std::nullptr_t) const noexcept { return ptr_ != nullptr; }

    // Conversion to bool
    explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }

    void reset(T* ptr) {
        if (ptr_ != ptr) {
            delete ptr_;
            ptr_ = ptr;
        } 
    }

    T* get() const { return ptr_; }
};

#endif
