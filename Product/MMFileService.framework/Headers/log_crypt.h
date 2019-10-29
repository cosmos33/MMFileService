// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

//
//  log_crypt.h
//  mars-ext
//
//  Created by yanguoyue on 16/6/14.
//

#ifndef LOG_CRYPT_H_
#define LOG_CRYPT_H_

#include <memory>
#include <stdint.h>
#include <string>

#include "autobuffer.h"
#include "ILogCrypt.h"

namespace mmslog {

    class LogCrypt {
    public:
        LogCrypt(bool _is_crypt, char _cryptNoCompressStart = 18, char _cryptCompressStart = 19,
                 char _noCryptCompressStart = 20, char _noCryptNoCompressStart = 4, char _kMagicEnd = 0);

        virtual ~LogCrypt() {}

    private:
        LogCrypt(const LogCrypt &);

        LogCrypt &operator=(const LogCrypt &);

    public:
        /**
         * 获取头数据部分长度
         */
        static uint32_t GetHeaderLen();

        /**
         * 获取尾信息部分长度
         */
        static uint32_t GetTailerLen();

        /**
         * 获取压缩后的日志长度，根据头信息里记录的
         * @param _data buffer指针
         * @param _len buffer长度
         * @return 日志长度
         */
        uint32_t GetEncodeLogLen(const char *const _data, size_t _len);

        /**
         * 获取压缩之前的日志长度，根据头信息里记录的
         * @param _data buffer指针
         * @param _len buffer长度
         * @return 原始日志长度
         */
        uint32_t GetOriginLogLen(const char *const _data, size_t _len);

        /**
         * 更新压缩后的日志长度
         * @param _data buffer指针
         * @param _add_len 新增的长度
         */
        void UpdateEncodeLogLen(char *_data, uint32_t _add_len);

        /**
         * 更新压缩前的日志长度
         * @param _data buffer指针
         * @param _add_len 新增的长度
         */
        void UpdateOriginLogLen(char *_data, uint32_t _add_len);

    public:

        /**
         * 设置头信息
         * @param _data buffer指针
         * @param _is_compress 是否压缩
         */
        void SetHeaderInfo(char *_data, bool _is_compress);

        /**
         * 设置尾信息，根据head信息里的长度来判断要在哪个位置插入尾信息
         * @param _data buffer指针
         */
        void SetTailerInfo(char *_data);

        /**
         * 加密日志信息，加密完之后不更新头信息
         * @param _log_data 数据内存头指针
         * @param _input_len 输入的内容长度
         * @param _out_buff 加密后的内容输出容器
         */
        void CryptAsyncLog(const char *const _log_data, size_t _input_len, AutoBuffer &_out_buff);

        /**
         * 输入一个缓冲区头指针，根据里边的内容，调整头信息
         * @param _data buffer指针
         * @param _data_len buffer长度
         * @param encodeLogLength 压缩后的长度
         * @return
         */
        bool Fix(char *_data, size_t _data_len, uint32_t &encodeLogLength);

        /**
         * 设置加密逻辑处理对象
         */
        void setCrypt(std::shared_ptr<ILogCrypt> crypt);

    private:
        bool is_crypt_;
        std::shared_ptr<ILogCrypt> mCrypt = nullptr;
        char kMagicCryptNoCompressStart;             // 加密，但是不压缩
        char kMagicCryptCompressStart;               // 即加密又压缩
        char kMagicNoCryptCompressStart;             // 不加密，只压缩
        char kMagicNoCryptNoCompressStart;           // 不加密，不压缩
        char kMagicEnd;                              // 尾标识
    };
}



#endif /* LOG_CRYPT_H_ */
