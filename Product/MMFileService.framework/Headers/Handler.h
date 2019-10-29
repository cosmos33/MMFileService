//
// Created by chenwangwang on 2018/6/12.
//

#ifndef MOMO_IM_BASE_HANDLER_H
#define MOMO_IM_BASE_HANDLER_H

#include <memory>
#include "Message.h"
#include "MessageQueue.h"
#include "Looper.h"
#include "MUtils.h"
#include "Runnable.h"

namespace mmslog {

    static int64_t _HandlerNextId = 0;

    class MessageQueue;
    class Looper;

    class Message;

    using Callback2 = std::function<bool(std::shared_ptr<Message> msg)>;

    /**
     * 处理不同线程之间消息的类，也作为消息发送器
     * 消息处理顺序：
     * 1. Message#callback
     * 2. Handler#callback
     * 3. Handler#handleMessage()
     */
    class Handler : public std::enable_shared_from_this<Handler> {
    public:
        Handler() : Handler((Callback2) nullptr) {}
        Handler(Callback2 callback);
        Handler(std::weak_ptr<Looper> looper);

        virtual ~Handler();

        Callback2 mCallback;
        bool post(std::shared_ptr<Runnable> runnable);
        bool postDelayed(std::shared_ptr<Runnable> runnable, int64_t delayTimeMillis);
        void removeCallbacks(std::shared_ptr<Runnable> callback);
        void removeMessages(int what);
        void removeMessages(int what, void *object);
        bool sendMessage(std::shared_ptr<Message> msg);
        bool sendMessageDelayed(std::shared_ptr<Message> msg, int64_t delayMillis);
        /**
         * 开始处理消息
         */
        void dispatchMessage(std::shared_ptr<Message> msg);
        int64_t getId();
        bool hasMessages(int what);
        std::weak_ptr<Looper> getLooper();
    private:
        int64_t mId;
        bool sendMessageAtTime(std::shared_ptr<Message> msg, int64_t uptimeMillis);
        static std::shared_ptr<Message> getPostMessage(std::shared_ptr<Runnable> runnable);
        std::weak_ptr<MessageQueue> mQueue;
        std::weak_ptr<Looper> mLooper;
        static int64_t nextId();
    protected:
        void handleMessage(std::shared_ptr<Message> msg);
    };
}

#endif //MOMO_IM_BASE_HANDLER_H
