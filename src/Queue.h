#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H


#include <iostream>
#include <memory>

template<typename T>
class Queue {
public:
    Queue() : size_(0), head_(nullptr) , tail_(nullptr){}




    T& Front() {
        if(Empty()){
            std::cout<<"Queue is empty\n";
            exit(1);
        }

        return *(head_->data);
    }

    T& Back() {
        if(Empty()){
            std::cout<<"Queue is empty\n";
            exit(1);
        }

        return *(tail_->data);
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
            tail_ = node;
            size_++;
            return;
        }

        tail_->nextNode = node;
        tail_ = tail_->nextNode;
        size_++;
    }


    void Pop() {
        if (Empty()) {
            std::cout << "Cannot Pop from empty Queue\n";
            exit(1);
        }

        head_ = head_->nextNode;
        if(size_ == 1)
            tail_ = nullptr;
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
    std::shared_ptr<struct Node> tail_;
};

#endif //QUEUE_QUEUE_H
