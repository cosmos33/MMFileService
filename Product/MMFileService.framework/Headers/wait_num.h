#ifndef BASE_TOOL_WAIT_NUM_WAIT_NUM_H_
#define BASE_TOOL_WAIT_NUM_WAIT_NUM_H_

#include <sstream>

namespace base_tool {
    class WaitNum {
        public:
            WaitNum();
            WaitNum(int num);
            ~WaitNum();
            void Wait(int num);
            void Inc();
            void Dec();
        private:
            int num_;
            std::mutex mutex_;
            std::condition_variable cov_;
    };
}

#endif //BASE_TOOL_WAIT_NUM_WAIT_NUM_H_
