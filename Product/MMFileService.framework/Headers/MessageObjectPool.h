//
// Created by chenwangwang on 2018/6/13.
//

#ifndef MOMO_IM_BASE_OBJECTPOOL_H
#define MOMO_IM_BASE_OBJECTPOOL_H


#include <mutex>
#include "Message.h"

namespace mmslog {
    class MessageObjectPool {

    public:
        static MessageObjectPool *getInstance();
        /**
         * 从对象池里取一个消息对象
         */
        std::shared_ptr<Message> obtain();

        void recycle(std::shared_ptr<Message> msg);

    private:
        std::mutex mut_;
        std::shared_ptr<Message> __messagePool;
        int __poolSize;
        const int MAX_POOL_SIZE = 50;
    };

}
#endif //MOMO_IM_BASE_OBJECTPOOL_H
