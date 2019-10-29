#ifndef BASE_TOOL_HTTP_INTERCEPTOR_SECURITY_H
#define BASE_TOOL_HTTP_INTERCEPTOR_SECURITY_H

#include "http_request.h"
#include "auto_buffer.h"
#include "cJSON.h"
#include "key_info.h"


namespace base_tool {

    class HttpInterceptorSecurity : public HttpInterceptor {
        public:
            HttpInterceptorSecurity();
            void SetKeyInfo(int version, int scenario, int add_salt_aes_case, const char * default_passwd);
            void SetAskCallback(std::function<void(std::string &exchange_key_url, std::string &sessionid, std::string &user_agent, std::string &net, std::string &uid)> ask_callback);
            void SetMaxTryCount(int max);

            void Prepare(std::shared_ptr<base_tool::HttpRequest> request) override;
            void Complete(std::shared_ptr<base_tool::HttpResponse> response ) override;

        private:
            std::function<void(std::string &exchange_key_url, std::string &sessionid, std::string &user_agent, std::string &net, std::string &uid)> ask_callback_ = nullptr;
            void GenKey(std::string old_passwd);
            KeyInfo keyinfo;
            std::mutex mutex_;
            base_tool::WaitNum wait_num;
            int EncAndBase64(base_tool::cJSON *root, base_tool::AutoBuffer &enData, base_tool::AutoBuffer &signAndBase64);
            int max_try_count_;
    };

}

#endif //BASE_TOOL_HTTP_INTERCEPTOR_SECURITY_H
