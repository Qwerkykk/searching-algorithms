#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H


#include <iostream>
#include <memory>
#include <cassert>

template<typename T>
class Queue {
public:
    using ValueType = T;

    Queue() : size_(0), head_(nullptr) , tail_(nullptr){}

    T& Front() {
        assert(Empty() != true && "Queue is empty");
        return *(head_->data);
    }

    T& Back() {
        assert(Empty() != true && "Queue is empty");
        return *(tail_->data);
    }

    void Push(ValueType&& data) {

        Push(std::forward<ValueType&>(data));
    }

    void Push(ValueType& data) {
        std::shared_ptr<struct Node> node = std::make_shared<struct Node>();

        node->data = std::make_shared<ValueType>(data);
        node->nextNode = nullptr;


        if (Empty()) {
            head_ = node;
            tail_ = node;
            size_++;
            return;
        }

        tail_->nextNode = node;
        tail_ = tail_->nextNode;
        size_++;
    }


    void Pop() {
        assert(Empty() != true && "Queue is empty");

        head_ = head_->nextNode;
        if(size_ == 1)
            tail_ = nullptr;
        size_--;
    }

    bool Contains(ValueType&& data) {

        return Contains(std::forward<T&>(data));
    }

    bool Contains(ValueType& data){
        auto it = head_;

        while (it!= nullptr){
            if(data == *(it->data))
                return true;
            it = it->nextNode;
        }

        return false;
    }

    bool Empty() {
        if (size_ == 0)
            return true;
        return false;
    }

    size_t Size() {
        return size_;
    }

private:
    struct Node {
        std::shared_ptr<ValueType> data;
        std::shared_ptr<struct Node> nextNode;
    };
    size_t size_;
    std::shared_ptr<struct Node> head_;
    std::shared_ptr<struct Node> tail_;
};

#endif //QUEUE_QUEUE_H
