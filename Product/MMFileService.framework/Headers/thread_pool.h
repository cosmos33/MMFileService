#ifndef BASE_TOOL_THREAD_POOL_THREAD_POOL_H_
#define BASE_TOOL_THREAD_POOL_THREAD_POOL_H_

#include <functional>
#include <unistd.h>
#include <sstream>
#include "log.h"

namespace base_tool{
    class Job{ //任务节点
        public:
            Job() {
                BaseToolLogD("Job()\n");
            }
            ~Job() {
                BaseToolLogD("~Job()\n");
            }
            std::function<void()> callback = NULL;
            Job *next = NULL;
    };

    class ThreadPool{
        public:
            ThreadPool(std::string name, int thread_corenum, int thread_maxinum, int thread_timeout);
            ~ThreadPool();
            void AddJob(std::function<void()> func);
            void GetInfo(int &thread_num_now, int &thread_num_sleep, int &node_num_malloc_now);
        private:
            std::string name_;     //线程名前缀。
            int count_;          //配合线程名前缀给每个线程起名用。

            int flag_close_;         //标志开始结束工作。
            int thread_corenum_;   //最少线程数。 
            int thread_maxinum_;    //最多线程数。
            int thread_num_now_;     //当前线程数。
            int thread_num_sleep_;   //正在休眠线程数。
            int timeout_;            //线程进入休眠状态开始计时且当超过此时间则判断线程池内线程数是否多余thread_corenum数，多余则回收此线程
            pthread_mutex_t mutex_;  //互斥锁。
            pthread_cond_t cond_pulljob_;    //唤醒休眠线程。
            pthread_cond_t cond_exit_;       //唤醒destroy检查。

            int node_num_malloc_now_;        //当前已经malloc的node数。
            Job *tail_;              //任务队列队尾。
            Job head_;               //任务队列头部，定义为非指针是为了当任务队列为空时减少一次动态申请内存。

            std::function<void()> callback_;   //执行的任务。
            void ThreadWork();
    };
}

#endif //BASE_TOOL_THREAD_POOL_THREAD_POOL_H_
