#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <memory>
#include <functional>
#include <iostream>
#include <utility>



template<typename T>
struct Node {
    std::shared_ptr<T> data;
    std::weak_ptr<struct Node> leftNode;
    std::shared_ptr<struct Node> rightNode;
};


template<typename List_>
class ListIterator {
public:
    using ValueType = typename List_::ValueType;
    using SharedPointerType = typename List_::SharedPointerType;
    using SharedPointerNode = typename List_::SharedPointerNode;
    using ReferenceType = ValueType&;
public:
    ListIterator(SharedPointerNode ptr) : ptr_(ptr) {}

    ListIterator& operator++() {
        ptr_ = ptr_->rightNode;
        return *this;
    }

    ListIterator operator++(int) {
        ListIterator iterator = *this;
        ptr_ = ptr_->rightNode;
        return iterator;
    }


    ListIterator& operator--() {
        ptr_ = ptr_->leftNode.lock();
        return *this;
    }

    ListIterator operator--(int) {
        ListIterator iterator = *this;
        ptr_ = ptr_->leftNode.lock();
        return iterator;
    }

    SharedPointerType operator->() {
        return ptr_->data;
    }

    ReferenceType operator*() {
        return *(ptr_->data);
    }

    bool operator==(const ListIterator& other) const {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const ListIterator& other) const {
        return !(*this == other);
    }

private:
    std::shared_ptr<struct Node<ValueType>> ptr_;
};

template<typename T>
class List {
public:


    using ValueType = T;
    using SharedPointerType = std::shared_ptr<T>;
    using Iterator = ListIterator<List<T>>;
    using SharedPointerNode = std::shared_ptr<Node<ValueType>>;
public:
    List() {

        SharedPointerNode node = std::make_shared<Node<ValueType>>();
        node->data = nullptr;
        node->leftNode.reset();
        node->rightNode = nullptr;

        head_ = node;
        tail_ = node;
        size_ = 0;
    }


    void Clear(){
        head_ = tail_.lock();
        head_->leftNode.reset();
        size_ = 0;
    }

    void PushFront(T&& data) {
        PushFront(std::forward<T&>(data));
    }

    void PushFront(T& data) {

        SharedPointerNode node = std::make_shared<struct Node<ValueType>>();

        node->data = std::make_shared<T>(data);
        node->rightNode = head_;
        ++size_;

        head_->leftNode = node;
        head_ = node;
    }

    T& Front() {
        return *(head_->data);
    }

    T& Back() {
        return *(tail_.lock()->leftNode.lock()->data);
    }

    Iterator begin() {
        return Iterator(head_);
    }

    Iterator end() {
        return Iterator(tail_.lock());
    }

    void PushBack(T&& data) {
        PushBack(std::forward<T&>(data));
    }

    void PushBack(T& data) {
        SharedPointerNode node = std::make_shared<struct Node<ValueType>>();
        node->data = std::make_shared<T>(data);

        if (IsEmpty()) {
            node->rightNode = tail_.lock();
            tail_.lock()->leftNode = node;
            head_ = node;
            ++size_;
            return;
        }

        node->leftNode = tail_.lock()->leftNode;
        node->rightNode = tail_.lock();
        node->leftNode.lock()->rightNode = node;
        tail_.lock()->leftNode = node;
        ++size_;
    }

    void PopFront() {
        if (IsEmpty()) {
            std::cout << "Cannot pop from empty list\n";
            exit(1);
        }

        if (size_ == 1) {
            head_ = tail_.lock();
            tail_.lock()->leftNode.reset();
            --size_;
            return;
        }

        head_ = head_->rightNode;
        head_->leftNode.reset();
        --size_;
    }

    void PopBack() {
        if (IsEmpty()) {
            std::cout << "Cannot pop from empty list\n";
            exit(1);
        }

        if (size_ == 1) {
            head_ = tail_.lock();
            head_->leftNode.reset();
            --size_;
            return;
        }

        SharedPointerNode temp = tail_.lock()->leftNode.lock();
        tail_.lock()->leftNode = temp->leftNode;
        temp->leftNode.lock()->rightNode = tail_.lock();
        --size_;
    }


    void Remove(T&& data) {
        Remove(std::forward<T&>(data));
    }

    void Remove(T& data) {
        if (IsEmpty()) {
            std::cout << "You cannot delete a node from an empty list" << std::endl;
            exit(1);
        }

        SharedPointerNode it = head_;
        while (it->rightNode != nullptr) {
            if (*(it->data) == data) {
                if (it == head_) {
                    head_ = head_->rightNode;
                    head_->leftNode.reset();
                    --size_;
                    return;
                }

                SharedPointerNode temp = it->rightNode;
                temp->leftNode = it->leftNode;
                it->leftNode.lock()->rightNode = temp;

                --size_;
                return;
            }
            it = it->rightNode;
        }
    }

    void sort() {
        qsort();
    }

    void sort(const std::function<int8_t(T, T)>& compare_function) {
        Compare = std::move(compare_function);
        qsort();
    }


    size_t Size() const {
        return size_;
    }

    bool IsEmpty() const {
        if (size_ == 0)
            return true;
        return false;
    }


private:


    std::shared_ptr<struct Node<ValueType>> head_;
    std::weak_ptr<struct Node<ValueType>> tail_;
    size_t size_;

    std::function<int8_t(T, T)> Compare;

    void Swap(SharedPointerNode node1, SharedPointerNode node2) {
        SharedPointerType temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    }

    void qsort() {

    }

};


#endif
