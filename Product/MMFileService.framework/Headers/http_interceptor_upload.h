#ifndef BASE_TOOL_HTTP_INTERCEPTOR_UPLOAD_H
#define BASE_TOOL_HTTP_INTERCEPTOR_UPLOAD_H

#include "http_request.h"
#include "auto_buffer.h"
#include "cJSON.h"
#include "key_info.h"

namespace base_tool {

    class HttpInterceptorUploadKeyInfo {
        public:
            int version_;
            int scenario_;
            base_tool::AutoBuffer aes_key_;
            base_tool::AutoBuffer aes_key_spkenc_base64enc_;
    
            HttpInterceptorUploadKeyInfo();
            ~HttpInterceptorUploadKeyInfo();
            void SetServerPublicKey(int version, int scenario);
            void GenAesKey();
        private:
            void *server_public_key_;
    };

    class HttpInterceptorUpload : public HttpInterceptor {
        public:
            HttpInterceptorUpload();
            void SetKeyInfo(int version, int scenario);
            void SetMaxTryCount(int max);

            void Prepare(std::shared_ptr<base_tool::HttpRequest> request) override;
            void Complete(std::shared_ptr<base_tool::HttpResponse> response ) override;

        private:
            HttpInterceptorUploadKeyInfo keyinfo;
            std::mutex mutex_;
            base_tool::WaitNum wait_num;
            int EncAndBase64(base_tool::cJSON *root, base_tool::AutoBuffer &enData, base_tool::AutoBuffer &signAndBase64);
            int max_try_count_;
    };

}

#endif //BASE_TOOL_HTTP_INTERCEPTOR_UPLOAD_H
