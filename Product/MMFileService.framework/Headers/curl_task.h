#ifndef BASE_TOOL_HTTP_REQUEST_CURL_TASK_H_
#define BASE_TOOL_HTTP_REQUEST_CURL_TASK_H_

#include <thread>
#include <list>
#include <string>
#include <unordered_map>

namespace base_tool {
    enum CurlTaskMethod{
        kCurlTaskMethodHead = 1,
        kCurlTaskMethodGet,
        kCurlTaskMethodPost,
    };

    enum CurlTaskEvent{
        kCurlTaskEventStart = 1,
        kCurlTaskEventPauseForPriorityControl,
        kCurlTaskEventResumeForPriorityControl,
        kCurlTaskEventEnd,
    };

    /* URL请求类
     */
    class CurlTask{
        public:
            /* 错误码，0：代表正常结束，-1000:任务被强行停止，其他值：libcurl错误码。(注：非HTTP的Status-Code值)
             */
            int err_code_;

            /* 下载完的报头数据全部写入此成员。
             */
            std::string result_header_data_;

            /* 如果没有设置callback_recvBodyData成员，则下载完的报体数据全部写入此成员。
             */
            std::string result_body_data_;

            /* 如果此回调非空，则每次下载到报体数据时会调取此回调方法(下载完所有数据会多次回调此方法)。
             * 入参ptr：本次调用下载到数据的首地址。
             * 入参size：本次调用下载到的数据大小。
             */
            std::function<void(void *ptr, size_t size)> callback_recv_body_data_;

            /* 任务级别，0最高，值越大级别越低。
             */
            unsigned int level_; 

            /* 事件回调。
             */
            std::function<void(CurlTaskEvent event)> callback_event_;

            CurlTask();
            ~CurlTask();

            /* 设置URL地址。
             */
            void SetUrl(const char *url);

            /* 设置链接地址和端口。
             */
            void SetConnectTo(const char *ip, const char *port); //删除=================。

            /* 设置CA证书。
             */
            void SetCA(const char * path);

            /* 设置请求方法
             */
            void SetMethod(enum CurlTaskMethod method);

            /* 设置socket链接超时时间，单位：秒。
             */
            void SetConnectTimeout(long timeout_s);

            /* 设置总超时时间，单位：秒。
             */
            void SetTimeout(long timeout_s);

            /* 设置是否301、302跳转，false:禁止跳转，true:开启跳转。已经在构造函数内设置为了开启跳转。
             */
            void SetFollowLocation(bool enable);

            /* 设置Range参数。
             */
            void SetRange(const char *range);

            /* 设置报头的User-Agent字段信息。
             */
            void SetUserAgent(const char * user_agent);

            /* 设置Host参数。
             */
            void SetHost(const char * host);

            /* 设置Accept参数。
             */
            void SetAccept(const char * accept);

            /* 设置添加报头内自定义字段。
             */
            void AddHeaderPragma(const char *key, const char *value);

            /* 设置为普通格式的post请求。
             */
            void SetPost(const char *postdata, long size);
            //=======addPost_keyValue(char *key, char *value);

            /* 设置form-data格式的post请求。
             */
            void SetPostDataFormAddFile(const char *name, const char *file, const char *content_type);

            /* 设置form-data格式的post请求。
             */
            void SetPostDataFormAddContents(const char *name, const void *contents, size_t contents_length, const char *content_type);

            /* 重置result的数据,这时可以在次使用此对象重新发起请求，常用于服务器或网络问题下载数据失败需要再次发起请求时。 
             */
            void ResetResult();

            /* 开始请求，此函数会阻塞直至请求完成结束。
             * 如果此对象会加入CurlTasksDispatcher对象进行并行下载那么无需调用此接口。
             */
            void TaskPerform();

            /* CurlTasksDispatcher根据优先级控制暂停
             */
            void PauseForPriorityControl();

            /* CurlTasksDispatcher根据优先级控制继续
             */
            void ResumeForPriorityControl();

            /* 获取最后一次使用的url
             */
            const char * GetUrl();

            /* 获取HTTP返回值。
             */
            void GetResponseCode(long *codep);

            /* 查看result数据有多少个报头
             */
            int GetResultHeaderDataHeaderTotal();

            /* 从最后一个报头读取字段信息
             */
            void GetResultHeaderDataPragma(const char *key, std::string &value);

            /* 从最第num个报头读取字段信息
             */
            void GetResultHeaderDataPragma(int num, const char *key, std::string &value);

            /* resultHeaderData内每个字段也会写入此list内的map内，当有返回多个报头时(在302跳转时会存储多个报头)此list内最后一个map即是最后一个报头信息。
             */
            std::list<std::shared_ptr<std::unordered_map<std::string, std::string> > > GetResultHeaderDataList();

            /* 获取Curl句柄,(此类有很多功能未实现接口，此类本身封装Curl实现的，所以可以得到此Curl句柄后对其更多的设置)
             */
            void * GetCurl();

            /* 开启调试打印信息。
             */
            void SetDebug();

        private:
            void * curl_;
            std::string url_;
            std::unordered_map<std::string, std::string> map_set_http_header_;
            std::list<std::shared_ptr<std::unordered_map<std::string, std::string> > > result_header_data_list_;
            bool flag_pause_for_priority_control_;
            void *slist_;
            std::string connect_to_ip_, connect_to_port_;
            void *connect_to_;
            void *formpost_;
            void *lastptr_;
            
            std::list<void *> when_completed_free_;
            char * when_completed_free_post_data;
    };

    /* 多CurlTask对象并行任务调度类
     */
    class CurlTasksDispatcher{
        public:
            //=====================shared_ptr<ThreadPool> pool;

            CurlTasksDispatcher();
            ~CurlTasksDispatcher();

            /* 加入一个CurlTask对象。
             */
            void Put(std::shared_ptr<CurlTask> task);

            /* 取出一个已经完成的CurlTask对象，当没有可取时阻塞直至有完成任务时，如果调取了distroy接口则不会在阻塞，当返回所有任务后返回nullptr。
             */
            std::shared_ptr<CurlTask> Take();

            /* 强行停止正在运行的某任务。
             */
            void Stop(CurlTask* task);

            /* 强行停止所有任务。
             */
            void Stop();

            /* 销毁，此方法用于此对象不再使用时(主要目的是为了Take接口不在阻塞)。
             */
            void Distroy();

        private:
            bool flag_distroy_;
            void * curlm_;
            std::thread* thread_;
            int pipe_fd_[2];
            std::mutex mutex_;
            std::condition_variable cov_;
            std::unordered_map<unsigned long long, std::shared_ptr<CurlTask> > tasks_running_; //正在执行中的所有任务。
            std::list<std::shared_ptr<CurlTask> > complete_tasks_; //已经完成的任务队列。
            void Loop();
            void PriorityControl();
            int EfCurlMultiSelect(void * curlm, int fd);
    };
}
#endif //BASE_TOOL_HTTP_REQUEST_CURL_TASK_H_
