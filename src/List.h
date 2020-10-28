#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <memory>
#include <iostream>
#include <cassert>


template<typename T>
struct Node_ {
    std::shared_ptr<T> data;
    std::weak_ptr<Node_> leftNode;
    std::shared_ptr<Node_> rightNode;
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
    std::shared_ptr<Node_<ValueType>> ptr_;
};

template<typename T>
class List {
public:


    using ValueType = T;
    using SharedPointerType = std::shared_ptr<T>;
    using Iterator = ListIterator<List<T>>;
    using SharedPointerNode = std::shared_ptr<Node_<ValueType>>;
public:
    List() {

        SharedPointerNode node = std::make_shared<Node_<ValueType>>();
        node->data = nullptr;
        node->leftNode.reset();
        node->rightNode = nullptr;

        head_ = node;
        tail_ = node;
        size_ = 0;
    }


    void Clear() {
        head_ = tail_.lock();
        head_->leftNode.reset();
        size_ = 0;
    }

    void PushFront(ValueType&& data) {
        PushFront(std::forward<ValueType&>(data));
    }

    void PushFront(ValueType& data) {

        SharedPointerNode node = std::make_shared<Node_<ValueType>>();

        node->data = std::make_shared<ValueType>(data);
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

    void PushBack(ValueType&& data) {
        PushBack(std::forward<ValueType&>(data));
    }

    void PushBack(ValueType& data) {
        SharedPointerNode node = std::make_shared<Node_<ValueType>>();
        node->data = std::make_shared<ValueType>(data);

        if (Empty()) {
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
        assert(Empty() != true && "You cannot pop node from empty list");

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
        assert(Empty() != true && "You cannot pop node from empty list");

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
        assert(Empty() != true && "You cannot remove node from empty list");

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

    size_t Size() const {
        return size_;
    }

    bool Empty() const {
        if (size_ == 0)
            return true;
        return false;
    }


private:


    std::shared_ptr<Node_<ValueType>> head_;
    std::weak_ptr<Node_<ValueType>> tail_;
    size_t size_;

};


#endif
