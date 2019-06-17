//
// Created by chenwangwang on 2018/6/15.
//

#ifndef MOMO_IM_BASE_HANDLERTHREAD_H
#define MOMO_IM_BASE_HANDLERTHREAD_H

/**
 * 带消息处理队列的线程封装
 */
#include "MomoNamedThread.hpp"
#include "Looper.h"

namespace mmslog {
    using MLock = std::lock_guard<std::mutex>;
    using UNILock = std::unique_lock<std::mutex>;

    class HandlerThread : public MomoNamedThread {
    public:
        void run(std::function<void()> function) override;

        HandlerThread();

        HandlerThread(const std::string &name);

        std::weak_ptr<Looper> getLooper();
        void quit();
    protected:
        void onThreadRun() override;
        void onThreadExit() override;
        void onLooperPrepared();
    private:
        std::mutex mMutex;
        std::condition_variable mVariable;
        std::weak_ptr<Looper> mLooper;
        bool isLooperInit = false;
        bool isRunning = false;
    };
}


#endif //MOMO_IM_BASE_HANDLERTHREAD_H
