#ifndef MMLOG_UPLOAD_LOG_UPLOAD_H
#define MMLOG_UPLOAD_LOG_UPLOAD_H

#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <thread>
#include "base_tool.h"
#include "Configuration.h"

namespace mmslog {

class LogUpload : public base_tool::HttpInterceptor, public std::enable_shared_from_this<LogUpload> {
    public:
        LogUpload();
        ~LogUpload();
        void SetConfiguration(const std::shared_ptr<Configuration> configuration);
        std::function<void()> callback_prepare_upload_flush_;
        std::function<void()> callback_prepare_upload_openNewLogFile_;
        void Start();
        void Stop();
        void ForceUpload();
        void CronJobFunc(bool first);
    private:
        time_t last_time_upload;
        std::string url_;
        time_t strategy_;
        std::string dir_;
        std::string prefix_;
        std::string app_id_;
        std::string device_id_;
        std::thread *thread_; 
        std::shared_ptr<IUpload> upload_;
        std::shared_ptr<base_tool::CronJob> cronjob;
        int status_;
        void loop();
        std::shared_ptr<base_tool::HttpDispatcher> hd;
        pthread_mutex_t mutex_;
        void Prepare(std::shared_ptr<base_tool::HttpRequest> request) override;
        void Complete(std::shared_ptr<base_tool::HttpResponse> response) override;
        
};

};
#endif //MMLOG_UPLOAD_LOG_UPLOAD_H

