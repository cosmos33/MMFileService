//
// Created by chenwangwang on 2018/6/12.
//

#ifndef MOMO_IM_BASE_MESSAGE_H
#define MOMO_IM_BASE_MESSAGE_H

#include <memory>
#include <mutex>
#include <thread>
#include "Handler.h"
#include "MUtils.h"
#include "Runnable.h"

/**
 * 不同线程之间进行通讯的数据传输类
 * 1. what: 标记此次通讯的动作
 * 2. arg1/arg2: int类型数据
 * 3. obj: 需要传递的数据，不限制类型
 */
namespace mmslog {

    class Handler;

    class Message : public std::enable_shared_from_this<Message> {

    public:
        // friend class MessageObjectPool;
        int what = 0;
        int arg1 = 0;
        int arg2 = 0;
        void *obj  = nullptr;
        // 何时执行
        int64_t when = 0;
        std::shared_ptr<Runnable> callback = nullptr;
        // 消息处理器
        std::shared_ptr<Handler> target  = nullptr;

        // 采用链表的方式实现，所以需要记录下一个消息
        // FIXME 放在private下面，messageObjectPool访问不到，设置了友元也不行？？？
        std::shared_ptr<Message> next = nullptr;

        void sendToTarget();

        static std::shared_ptr<Message> obtain();

        static std::shared_ptr<Message> obtain(std::shared_ptr<Handler> target);

        static std::shared_ptr<Message> obtain(std::shared_ptr<Handler> target, std::shared_ptr<Runnable> callback);

        static void recycle(std::shared_ptr<Message> msg);
    };
}

#endif //MOMO_IM_BASE_MESSAGE_H
