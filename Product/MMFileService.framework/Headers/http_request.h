#ifndef BASE_TOOL_HTTP_REQUEST_HTTP_REQUEST_H_
#define BASE_TOOL_HTTP_REQUEST_HTTP_REQUEST_H_

#include <string>
#include <thread>
#include <list>
#include <unordered_map>
#include "c_curl_task.h"

namespace base_tool {

    enum HttpRequest_method{
        kHttpRequestMethodHead = 1,
        kHttpRequestMethodGet,
        kHttpRequestMethodPost,
    };

    class DataFormFile {
        public:
            std::string name_; 
            std::string file_path_;
            std::string content_type_;
    };

    class DataFormContents {
        public:
            ~DataFormContents() {
                if(contents_){
                    free(contents_);
                }
            }
            std::string name_; 
            void *contents_ = NULL;
            size_t contents_length_;
            std::string content_type_;
    };

    class HttpRequest {
        public:
            HttpRequest();
            HttpRequest(HttpRequest &request);
            ~HttpRequest();
            
            int err_code_ = 0;
            std::shared_ptr<std::unordered_map<std::string, std::string> > interceptor_info_;

            bool IsSetUrl();
            void SetUrl(std::string url);
            std::string GetUrl();

            bool IsSetRange();
            void SetRange(std::string range);
            std::string GetRange();

            bool IsSetHost();
            void SetHost(std::string host);
            std::string GetHost();

            bool IsSetAccept();
            void SetAccept(std::string accept);
            std::string GetAccept();

            bool IsSetLevel();
            void SetLevel(unsigned int level);
            unsigned int GetLevel();

            bool IsSetMethod();
            void SetMethod(HttpRequest_method method);
            HttpRequest_method GetMethod();

            bool IsSetConnectTimeout();
            void SetConnectTimeout(int connect_timeout);
            int GetConnectTimeout();

            bool IsSetTimeout();
            void SetTimeout(int timeout);
            int GetTimeout();

            bool IsSetCallbackRecvBodyData();
            void SetCallbackRecvBodyData(std::function<void(void *ptr, size_t size)> callback);
            std::function<void(void *ptr, size_t size)> GetCallbackRecvBodyData();

            bool IsAddHeaderPragma();
            void AddHeaderPragma(const std::string &key, const std::string &value);
            std::shared_ptr<std::unordered_map<std::string, std::string> > GetPragma();

            bool IsAddPostData();
            void AddPostData(const std::string &key, const std::string &value);
            std::shared_ptr<std::unordered_map<std::string, std::string> > GetPostData();

            bool IsAddPostDataFormFile();
            void AddPostDataFormFile(const std::string &name, const std::string &filePath, const std::string &contentType);
            std::shared_ptr<std::list<std::shared_ptr<DataFormFile> > > GetPostDataFormFile();   

            bool IsAddPostDataFormContents();
            void AddPostDataFormContents(const std::string &name, const void *contents, size_t contentsLength, const std::string &contentType);
            std::shared_ptr<std::list<std::shared_ptr<DataFormContents> > > GetPostDataFormContents();

        private:
            bool is_set_url_;
            std::string url_;

            bool is_set_range_;
            std::string range_;

            bool is_set_host_;
            std::string host_;

            bool is_set_accept_;
            std::string accept_;

            bool is_set_level_;
            unsigned int level_;

            bool is_set_method_;
            HttpRequest_method method_;

            bool is_set_connect_timeout_;
            int connect_timeout_;

            bool is_set_timeout_;
            int timeout_;

            bool is_set_callback_recv_body_data_;
            std::function<void(void *ptr, size_t size)> callback_recv_body_data_;

            bool is_add_header_pragma_;
            std::shared_ptr<std::unordered_map<std::string, std::string> > pragma_;

            bool is_add_post_data_;
            std::shared_ptr<std::unordered_map<std::string, std::string> > post_data_;

            bool is_add_post_data_form_file_;
            std::shared_ptr<std::list<std::shared_ptr<DataFormFile> > > post_data_form_file_;

            bool is_add_post_data_form_contents_;
            std::shared_ptr<std::list<std::shared_ptr<DataFormContents> > > post_data_form_contents_;

    };

    class HttpResponse {
        public:
            HttpResponse();
            ~HttpResponse();

            int err_code_;
            char err_info_[33];
            int http_response_code_;  
            std::shared_ptr<std::unordered_map<std::string, std::string> >  result_header_data_;
            std::string result_body_data_;

            std::shared_ptr<HttpRequest> request_;
            std::shared_ptr<HttpRequest> request_primitive_;
    };

    class HttpInterceptor {
        public:
            virtual void Prepare(std::shared_ptr<HttpRequest> request) = 0;
            virtual void Complete(std::shared_ptr<HttpResponse> response ) = 0;
    };

    class HttpDispatcher : public HttpRequest {
        public:
            HttpDispatcher();
            ~HttpDispatcher();
            void SetThreadpool(std::shared_ptr<ThreadPool> pool);
            void AddInterceptor(std::shared_ptr<HttpInterceptor> interceptor);   

            void * Put(std::shared_ptr<HttpRequest> request);
            void Stop(void *id);
            void Stop();

        private:
            std::shared_ptr<ThreadPool> pool_;
            std::list<std::shared_ptr<HttpInterceptor> > interceptor_list_;
            std::shared_ptr<CCurlTasksDispatcher> dispatcher_;

        public:
            bool IsSetCaPath();
            void SetCaPath(std::string ca_path);
            std::string GetCaPath();

            bool IsSetUserAgent();
            void SetUserAgent(std::string user_agent);
            std::string GetUserAgent();

            bool IsSetFollowLocation();
            void SetFollowLocation(bool follow_location);
            bool GetFollowLocation();

            bool IsSetDebug();
            void SetDebug(bool debug);
            bool GetDebug();

        private:
            bool is_set_ca_path_;   
            std::string ca_path_;

            bool is_set_user_agent_;
            std::string user_agent_;

            bool is_set_follow_location_;
            bool follow_location_;

            bool is_set_debug_;
            bool debug_;
    };
}

#endif //BASE_TOOL_HTTP_REQUEST_H_
