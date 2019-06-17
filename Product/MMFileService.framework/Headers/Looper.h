//
// Created by chenwangwang on 2018/6/13.
//

#ifndef MOMO_IM_BASE_LOOPER_H
#define MOMO_IM_BASE_LOOPER_H

#include <memory>
#include <iostream>
#include "MessageQueue.h"

namespace mmslog {

    class MessageQueue;

    /**
     * 线程本地对象，用来管理每个线程的消息轮询队列
     */
    class Looper {
    private:
        std::shared_ptr<MessageQueue> mQueue;
    public:
        Looper();

        ~Looper();

        /**
         * 获取当前线程的Looper对象弱引用智能指针，
         * 设计成弱引用，是因为，Looper对象生命周期跟随线程结束而结束，用弱引用就够了。
         * 如果用强引用会导致析构报错
         */
        static std::weak_ptr<Looper> myLooper();
        /**
         * 为当前线程创建Looper对象
         * @return -1代表失败，否则代表成功
         */
        static int prepare();
        /**
         * 开始轮询当前线程的消息
         */
        static void loop();
        /**
         * 获取消息队列
         * 设计成弱引用，是因为，消息队列对象生命周期跟随线程结束而结束，用弱引用就够了。
         * 如果用强引用会导致析构报错
         */
        std::weak_ptr<MessageQueue> getQueue();
        /**
         * 退出loop
         */
        void quit();
    private:
        /**
         * 获取消息队列
         */
        static std::shared_ptr<MessageQueue> myQueue();
    };
}

#endif //MOMO_IM_BASE_LOOPER_H
