#ifndef PRIORITYQUEUE_PRIORITYQUEUE_H
#define PRIORITYQUEUE_PRIORITYQUEUE_H


#include <memory>
#include <vector>


template<typename T>
class PriorityQueue {
public:
    PriorityQueue() : size_(0) {}


    void Push(T&& data, int priority) {

        Push(std::forward<T&>(data), priority);
    }

    void Push(T& data, int priority) {
        std::shared_ptr<struct Node> node = std::make_shared<struct Node>();
        node->data = std::make_shared<T>(data);
        node->priority = priority;

        int childLocation, parentLocation;

        size_++;
        childLocation = size_ - 1;
        parentLocation = (childLocation - 1) / 2;

        if (queue.size() == size_-1)
            queue.push_back(node);
        else
            queue.at(childLocation) = node;

        while (childLocation != 0 && queue.at(parentLocation)->priority > queue.at(childLocation)->priority) {
            auto temp = queue.at(parentLocation);
            queue.at(parentLocation) = queue.at(childLocation);
            queue.at(childLocation) = temp;

            childLocation = parentLocation;
            parentLocation = (childLocation - 1) / 2;
        }
    }

    T& Top() {
        if (Empty()) {
            std::cout << "Queue is empty\n";
            exit(1);
        }
        return *(queue.at(0)->data);
    }

    int TopPriority() {
        return queue.at(0)->priority;
    }

    void Pop() {
        if (Empty()) {
            std::cout << "Queue is empty\n";
            exit(1);
        }

        if (size_ == 1) {
            size_--;
            queue.at(0) = nullptr;
            return;
        }


        queue.at(0) = queue.at(size_ - 1);
        queue.at(size_ - 1) = nullptr;
        size_--;
        Heapify(0);

    }

    void UpdatePriority(T& data, int newPriority) {
        for (auto it = queue.begin(); it != queue.end(); it++) {
            if (data == *((*it)->data)) {
                (*it)->priority = newPriority;
                Heapify(0);
                return;
            }
        }
    }

    bool Contains(T& data) {
        for (size_t it = 0; it < size_; it++) {
            if (data == *(queue.at(it)->data))
                return true;
        }

        return false;
    }

    inline size_t Size() {
        return size_;
    }

    inline bool Empty() {
        if (size_ == 0)
            return true;
        return false;
    }

    void Heapify(size_t position) {
        size_t leftChild = 2 * position + 1;
        size_t rightChild = 2 * position + 2;
        size_t lowestPriority = position;

        if (leftChild < size_ && queue.at(leftChild)->priority < queue.at(lowestPriority)->priority)
            lowestPriority = leftChild;
        if (rightChild < size_ && queue.at(rightChild)->priority < queue.at(lowestPriority)->priority)
            lowestPriority = rightChild;

        if (lowestPriority != position) {
            auto temp = queue.at(position);
            queue.at(position) = queue.at(lowestPriority);
            queue.at(lowestPriority) = temp;

            Heapify(lowestPriority);
        }

    }

private:


    struct Node {
        int priority;
        std::shared_ptr<T> data;
    };

    size_t size_;
    std::vector<std::shared_ptr<struct Node>> queue;;

};


#endif //PRIORITYQUEUE_PRIORITYQUEUE_H
