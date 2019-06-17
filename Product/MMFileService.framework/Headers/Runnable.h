//
// Created by chenwangwang on 2018/6/19.
//

#ifndef MOMO_IM_BASE_RUNNABLE_H
#define MOMO_IM_BASE_RUNNABLE_H

#include <cstdint>
#include <functional>

namespace mmslog {
    static int64_t _RunnableNextId = 0;

    /**
     * 一个带ID的runnable接口类
     */
    class Runnable {
    private:
        int64_t mId;
        std::function<void()> mCallback;
        static int64_t nextId();
        Runnable(int64_t id) : mId(id) {}
    public:
        Runnable(std::function<void()> callback) : Runnable(nextId()) {
            mCallback = callback;
        }
        void run();
        int64_t getId();
        bool operator==(const Runnable &other){
            return mId == other.mId;
        }
    };

}



#endif //MOMO_IM_BASE_RUNNABLE_H
