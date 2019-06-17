#ifndef BASE_TOOL_CRONJOB_CRONJOB_H
#define BASE_TOOL_CRONJOB_CRONJOB_H

#include <set>
#include <time.h>
#include <thread>
#include <pthread.h>

namespace base_tool {

class CronJob {
    public:
        CronJob();
        ~CronJob();
        /* 添加指定时间执行任务，任务只执行一次。
         * 参数at_time是指定执行func的确切时间（非当前时间开始sleep秒数）,单位：秒，小于当前时间或当前时间则表示立即执行。
         * 参数func：为空等同于没有调用此函数。
         * 注意：CronJob对象内所有任务共用一个线程执行func队列，所以func内执行耗时任务会影响此对象内其他任务的队列执行。
         */
        void Add(time_t at_time, std::function<void()> func);
    private:
        void * jobs_;
        bool flag_running;
        pthread_mutex_t mutex;
        int pipe_fd[2];
        time_t sg_at_time;
        std::shared_ptr<std::thread> thread_;
        
        void loop();
};

}

#endif //BASE_TOOL_CRONJOB_CRONJOB_H

/* CronJob定时器类使用实例：
#include "../../include/base_tool/cronjob/cronjob.h"
using namespace std;
using namespace base_tool;
#include <unistd.h>

class A {
    public:
        int n = 0;
};

void func(CronJob * cronjob, bool frist, shared_ptr<A> a) {
    if (!frist) {
        printf("::func() to do something()======= a.n: %d\n", a->n++);
    }

    cronjob->Add(time(NULL) + 1, [cronjob, a](){func(cronjob, false, a);});
}

void mainA() {
    shared_ptr<CronJob> cronjob1 = make_shared<CronJob>();
    shared_ptr<A> a = make_shared<A>();
    int i = 1;
    while(i--) {
        CronJob * cronjob = cronjob1.get();
        func(cronjob, true, a);
    }
    a = NULL;

    sleep(5);
    cronjob1 = nullptr;
}



class B {
    public:
        int n = 0;
        shared_ptr<CronJob> cronjob = make_shared<CronJob>();

        void func(bool frist) {
            cronjob->Add(time(NULL) + 1, [this](){func(false);});
            if (frist) {
                return;
            }

            printf("B::func() to do something()=======n: %d\n", n++);
        }
};

void mainB() {
        B * b = new B();
        b->func(true);
        sleep(5);
        delete b;
}

int main() {
    mainA();
    return 0;
}
*/
