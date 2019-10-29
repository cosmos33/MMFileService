//
//  MomoThread.hpp
//  VodHttpServer
//
//  Created by guowei on 2018/5/14.
//  Copyright © 2018 MOMO. All rights reserved.
//

#ifndef Imomo_MomoThread_hpp
#define Imomo_MomoThread_hpp

#include <functional>
#include <thread>
#include <string>

// 替换std::thread，支持设置线程名称

namespace mmslog {

    class MomoNamedThread
    {
    public:

        MomoNamedThread();

        MomoNamedThread(const std::string& name);

        ~MomoNamedThread();

        bool joinable();

        void join();

        void setThreadName(const std::string& name);

        std::string& getThreadName();

        virtual void run(std::function<void()> function);

    protected:
        /**
         * 当线程调用时回调
         */
        virtual void onThreadRun();
        /**
         * 当线程退出的时候调用
         */
        virtual void onThreadExit();

    private:

        void setThreadNameInternal();

    private:
        std::thread mThread;
        std::string mThreadName;
        std::function<void()> mFunction;
    };

    void MomoNamedThreadSetThreadName(const std::string& threadName);
}

#endif /* Imomo_MomoThread_hpp */
