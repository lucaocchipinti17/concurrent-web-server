#include <mutex>
#include <vector>
#include <stdexcept>
#include <list>

template <typename T>
class ConcurrentRingBuffer {
private:
    std::unique_ptr<T[]> buffer;
    size_t capacity;
    uint8_t head;
    uint8_t tail;
    mutable std::mutex mtx;
    std::condition_variable not_empty;
    std::condition_variable not_full;

public:
    explicit ConcurrentRingBuffer(size_t capacity) : capacity(capacity), 
    head(0), tail(0) {
        data = std::make_unique<T[]>(capacity);
    }

    void push(const T& value) {
 
    }

    T pop() {}

    T get(size_t index) const {
        std::lock_guard<std::mutex> lock(mtx);
        if (index >= data.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return data.size();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        data.clear();
    }
};