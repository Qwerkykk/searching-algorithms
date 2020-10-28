#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <memory>
#include <iostream>
#include <cassert>

template<typename T>
class Stack {
public:
    using ValueType = T;
    Stack() : size_(0), head_(nullptr) {}

    ValueType& Top() {
        assert(Empty() != true && "Stack is empty");
        return *(head_->data);
    }


    void Push(ValueType&& data) {

        Push(std::forward<T&>(data));
    }

    void Push(ValueType& data) {
        std::shared_ptr<struct Node> node = std::make_shared<struct Node>();

        node->data = std::make_shared<ValueType>(data);
        node->nextNode = nullptr;


        if (Empty()) {
            head_ = node;
            size_++;
            return;
        }

        node->nextNode = head_;
        head_ = node;
        size_++;
    }

    void Pop() {
        assert(Empty() != true && "Stack is empty");

        head_ = head_->nextNode;
        size_--;
    }

    bool Contains(ValueType&& data) {

        return Contains(std::forward<ValueType&>(data));
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
};


#endif //STACK_STACK_H
