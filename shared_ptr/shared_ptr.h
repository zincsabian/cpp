#include <atomic>

template <class T>
class SharedPtr {
public:
    SharedPtr(T* ptr = nullptr):
        ptr_(ptr) {
            if (ptr_ == nullptr) {
                count_ = nullptr;
            } else {
                count_ = new std::atomic<size_t>(1);
            }
        };
    
    SharedPtr(const SharedPtr& other):
        ptr_(other.ptr_), count_(other.count_) {
            if (count_) {
                ++(*count_);
            }
        }
    
    SharedPtr(SharedPtr&& other) noexcept
        {
            ptr_ = other.ptr_;
            count_ = other.count_;
            other.ptr_ = nullptr;
            other.count_ = nullptr;
        }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            SharedPtr(other).swap(*this);
            // 构造一个other实例， 在其生命周期结束的时候对原指针引用计数-1
        }
        return *this;
    } 

    SharedPtr& operator=(SharedPtr&& other) noexcept{
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            count_ = other.count_;
            other.ptr_ = nullptr;
            other.count_ = nullptr;
        }
    }

    ~SharedPtr() {
        release();
    }

    T& operator *() const { return *ptr_; }
    T* operator ->() const { return ptr_; }
    T* get() const { return ptr_; }
    size_t use_count() const { return count_ == nullptr ? 0 : count_->load(); }

    void swap(SharedPtr& other) noexcept {
        std::swap(ptr_, other.ptr_);
        std::swap(count_, other.count_);
    }

    void reset(T* ptr = nullptr) {
        SharedPtr(ptr).swap(*this);
    }
    
private:

    void release() {
        if (count_ && --(*count_) == 0) {
            delete ptr_;
            delete count_;
        }
    }

    T* ptr_;
    std::atomic<size_t>* count_ = nullptr;
};
