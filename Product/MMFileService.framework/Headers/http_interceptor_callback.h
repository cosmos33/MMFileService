#include "base_tool/http_request/http_request.h"

namespace base_tool {

class HttpInterceptorCallback : public base_tool::HttpInterceptor {
    public:
        void SetCallback(std::function<void(std::shared_ptr<base_tool::HttpResponse> response)> callback);
        void Prepare(std::shared_ptr<base_tool::HttpRequest> request) override;
        void Complete(std::shared_ptr<base_tool::HttpResponse> response ) override;
    private:
        std::function<void(std::shared_ptr<base_tool::HttpResponse> response)> callback_;
};

}
