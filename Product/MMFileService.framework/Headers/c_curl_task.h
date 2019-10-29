#ifndef BASE_TOOL_HTTP_REQUEST_C_CURL_TASK_H_
#define BASE_TOOL_HTTP_REQUEST_C_CURL_TASK_H_

#include <thread>
#include <list>
#include <string>
#include <unordered_map>
#include "curl_task.h"
#include "thread_pool.h"
#include "wait_num.h"
#include "log.h"

namespace base_tool {
    /* 重写CurlTask类，增加了开始task前的回调接口和task完成后的回调接口。
     */
    class CCurlTask : public CurlTask {
        public:
            CCurlTask() {
                BaseToolLogD("CCurlTask() :%p\n", this);
            }
            ~CCurlTask() {
                BaseToolLogD("~CCurlTask() :%p\n", this);
            }
            std::function<void()> callback_prepare_ = nullptr;
            std::function<void()> callback_complete_ = nullptr;
    };

    /* 重写CurlTasksDispatcher类，改为了task被执行完毕后通过task的callback_complete接口回调。
       Take接口不允许调用,其他接口与CurlTasksDispatcher一致。
     */
    class CCurlTasksDispatcher : public CurlTasksDispatcher {
        public:

            /* 自己内部会创建一个线程池，并且所有的回调都交由线程池。
             */
            CCurlTasksDispatcher();

            /* 接受一个已经创建好的线程池。
             */
            CCurlTasksDispatcher(std::shared_ptr<ThreadPool> pool);

            ~CCurlTasksDispatcher();

            void Put(std::shared_ptr<CCurlTask> task);
            void Stop(CurlTask* task);
            void Stop();
            void Distroy();

        private:
            std::unordered_map<unsigned long long, bool > tasks_prepare_;
            std::mutex mutex_;
            std::shared_ptr<ThreadPool> pool_;
            std::thread* e_thread_;
            std::shared_ptr<WaitNum> wait_num_;
            bool flag_distroy_;
            void Take();
            void Loop();
    };
}

#endif //BASE_TOOL_HTTP_REQUEST_C_CURL_TASK_H_
