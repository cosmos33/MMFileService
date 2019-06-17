// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

/*
 * log_buffer.h
 *
 *  Created on: 2015-7-28
 *      Author: yanguoyue
 */

#ifndef LOGBUFFER_H_
#define LOGBUFFER_H_

#include <zlib.h>
#include <string>
#include <stdint.h>
#include <memory>

#include "ptrbuffer.h"
#include "autobuffer.h"
#include "ILogCrypt.h"
#include "ILogCompress.h"
#include "ZLibCompress.h"
#include "log_crypt.h"

namespace mmslog {
    class LogBuffer {
    public:
        LogBuffer(int fd, void *_pbuffer, size_t _len, bool _is_compress, LogCrypt *logCrypt, bool _is_crypt);

        ~LogBuffer();

    public:
        int GetFd();

        PtrBuffer &GetData();

        void Flush(AutoBuffer &_buff);

        int Write(const void *_data, size_t _length);

        /**
         * 设置加密逻辑处理对象
         */
        void setCrypt(std::shared_ptr<ILogCrypt> crypt);

        /**
         * 设置压缩逻辑处理对象
         */
        void setCompress(std::shared_ptr<ILogCompress> compress);

    private:

        bool __Reset();

        void __Flush();

        void __Clear();

        void __Fix();

    private:
        int fd_ = -1;
        PtrBuffer buff_;
        bool is_compress_;

        class LogCrypt *log_crypt_;

        bool isCrypt = true;

        // 默认使用zlib实现压缩
        std::shared_ptr<ILogCompress> mCompress = nullptr;
        std::shared_ptr<ILogCrypt> mCrypt = nullptr;
    };
}


#endif /* LOGBUFFER_H_ */
