//
// Created by chenwangwang on 2018/6/13.
//

#ifndef MOMO_IM_BASE_MESSAGEQUEUE_H
#define MOMO_IM_BASE_MESSAGEQUEUE_H

#include <condition_variable>
#include <memory>
#include "Message.h"
#include "Runnable.h"

namespace mmslog {

    using MLock = std::lock_guard<std::mutex>;
    using UNILock = std::unique_lock<std::mutex>;

    class Message;

    class Handler;

    /**
     * 用来处理线程消息的队列
     */
    class MessageQueue {
    public:
        virtual ~MessageQueue();

        /**
         * 获取下一个需要处理的消息
         */
        std::shared_ptr<Message> next();
        /**
         * 入队消息
         * @param msg 消息对象
         * @param when 时间
         */
        bool enqueueMessage(std::shared_ptr<Message> msg, int64_t when);
        /**
         * 移除指定Runnable的消息
         * @param h Handler
         * @param r Runnable
         * @param obj Object
         */
        void removeMessages(std::shared_ptr<Handler> h, std::shared_ptr<Runnable> r, void *obj);

        /**
         * 移除指定what的消息
         * @param h Handler
         * @param what what
         * @param obj Object
         */
        void removeMessages(std::shared_ptr<Handler> h, int what, void *obj);

        bool hasMessages(std::shared_ptr<Handler> h, int what, void *obj);

        void quit();

    private:
        std::mutex mMutex;
        std::condition_variable mVariable;
        bool mBlocked;   // 是否进入休眠
        bool mQuitting;   // 是否正在退出
        std::shared_ptr<Message> mMessages = nullptr;     // 当前的消息头
        /**
         * 唤醒异步线程
         */
        void wake();
        /**
         * 安全的移除所有消息
         */
        void removeAllMessagesLocked();
        void goSleep(int sleepTimeMillis, UNILock &lk);

    };
}


#endif //MOMO_IM_BASE_MESSAGEQUEUE_H
