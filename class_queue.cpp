#include <iostream>
#include <deque>

template <typename T, typename Container = std::deque<T>>
class Queue{
public:
    Container q_;

    T front() const {
        return q_.front();
    }
    T& front() {
        return q_.front();
    }
    void push(T elem) {
        q_.push_back(elem);
    }
    void pop() {
        q_.pop_front();
    }
    int size() const {
        return q_.size();
    }
    bool empty() const {
        return q_.empty();
    }

    bool operator==(const Queue& rhs) const {
        return (rhs.q_ == q_);
    }

    bool operator!=(const Queue& rhs) const {
        return (!(*this == rhs));
    }
};

