//
// Created by chenwangwang on 2018/6/11.
//

#ifndef LBQ_LINKEDBLOCKINGQUEUE_H
#define LBQ_LINKEDBLOCKINGQUEUE_H

#include <sys/types.h>
#include <pthread.h>
#include <iostream>
#include <queue>

namespace mmslog {

    template<class N>
    class Node
    {
    public:
        Node<N>() {}
        Node* next = nullptr;
        Node* pre = nullptr;
        N data = 0;
    };

    using namespace std;

    template<class N>
    class LinkedList
    {
    public:
        int length;
        // 头
        Node<N>* head;
        // 尾
        Node<N>* tail;

        LinkedList() {
            this->length = 0;
            this->head = nullptr;
            this->tail = nullptr;
        }
        ~LinkedList() {
            clear();
        }
        // 从栈顶压入
        void push(const N &data) {
            Node<N>* node = new Node<N>();
            node->data = data;
            node->next = this->head;
            if (this->head) {
                // 容器不为空
                this->head->pre = node;
            } else {
                // 容器为空
                tail = node;
            }
            this->head = node;
            this->length++;
        }
        // 从栈底压入
        void pushBottom(const N &data) {
            // 容器不为空
            Node<N>* node = new Node<N>();
            node->data = data;
            node->pre = tail;
            if (this->tail) {
                // 容器不为空
                this->tail->next = node;
            } else {
                // 容器为空
                head = node;
            }
            this->tail = node;
            this->length++;
        }
        // 从栈底取并移除
        N pop() {
            if (length == 0) {
                return 0;
            }
            Node<N> *n = tail;
            tail = n->pre;
            if (length == 1) {
                head = nullptr;
            } else {
                n->pre->next = nullptr;
                n->pre = nullptr;
            }
            length--;
            N result = n->data;
            delete(n);
            return result;
        }
        // 从栈顶取并移除
        const N front() {
            if (length == 0) {
                return 0;
            }
            Node<N> *n = head;
            head = n->next;
            if (length == 1) {
                tail = nullptr;
            } else {
                n->next->pre = nullptr;
                n->next = nullptr;
            }
            length--;
            N result = n->data;
            delete(n);
            return result;
        }
        // 是否是空
        bool empty() {
            return length == 0;
        }
        int64_t size() {
            return length;
        }
        void clear() {
            while (length > 0) {
                pop();
            }
        }

        bool contain(const N &data) {
            Node<N> *n = head;
            while (n) {
                if (n->data == data) {
                    return true;
                }
                n = n->next;
            }
            return false;
        }
    };

    /**
     * 线程安全的队列
     * @tparam T
     */
    template<class T>
    class LinkedBlockingQueue {
    private:
        mutable std::mutex mut_;
        LinkedList<T> list;
        std::condition_variable cond_;
    public:
        /**
         * 队列长度
         */
        int64_t size() {
            std::lock_guard<std::mutex> lk(mut_);
            return list.size();
        }
        /**
         * 从队尾插入一个元素
         */
        void put(const T e) {
            std::lock_guard<std::mutex> lk(mut_);
            list.push(e);
            cond_.notify_all();
        }

        /**
         * 从队头插入一个元素
         */
        void appendHead(const T e) {
            std::lock_guard<std::mutex> lk(mut_);
            list.pushBottom(e);
            cond_.notify_all();
        }

        /**
         * 从队头获取并删除一个元素
         */
        T take() {
            std::unique_lock<std::mutex> lk(mut_);
            cond_.wait(lk, [this]{
                return !list.empty();
            });
            return list.pop();
        }

        /**
         * 是否存在指定元素，如果是非基本类型，需要自己重载判等运算符
         * @return true 存在，false不存在
         */
        bool contain(const T &e) {
            std::lock_guard<std::mutex> lk(mut_);
            return list.contain(e);
        }

        /**
         * 从队头取一个元素，如果队列为空则返回nullptr
         */
        T poll() {
            std::unique_lock<std::mutex> lk(mut_);
            if (list.empty()) {
                return 0;
            }
            return list.front();
        };

        void clear() {
            std::lock_guard<std::mutex> lk(mut_);
            list.clear();
        }

        bool empty() {
            std::lock_guard<std::mutex> lk(mut_);
            return list.empty();
        }
    };

}

#endif //LBQ_LINKEDBLOCKINGQUEUE_H
