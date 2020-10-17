#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <memory>
#include <iostream>

template<typename T>
class Stack {
public:

    Stack() : size_(0), head_(nullptr) {}

    T& Top() {
        if(Empty()){
            std::cout<<"Stack is empty\n";
            exit(1);
        }

        return *(head_->data);
    }


    void Push(T&& data) {

        Push(std::forward<T&>(data));
    }

    void Push(T& data) {
        std::shared_ptr<struct Node> node = std::make_shared<struct Node>();

        node->data = std::make_shared<T>(data);
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
        if (Empty()) {
            std::cout << "Cannot Pop from empty Stack\n";
            exit(1);
        }

        head_ = head_->nextNode;
        size_--;
    }

    bool Contains(T&& data) {

        return Contains(std::forward<T&>(data));
    }

    bool Contains(T& data){
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
        std::shared_ptr<T> data;
        std::shared_ptr<struct Node> nextNode;
    };
    size_t size_;
    std::shared_ptr<struct Node> head_;
};


#endif //STACK_STACK_H
