//
// Created by chenwangwang on 2018/8/28.
//

#ifndef MMLOG_ILOGCRYPT_H
#define MMLOG_ILOGCRYPT_H

#include "autobuffer.h"

namespace mmslog {
    class ILogCrypt {
    public:
        /**
         * 为一段文本进行加密，加密后的内容存放到_out_buff里
         * @param _log_data 日志内容起始指针
         * @param _input_len 长度
         * @param _out_buff 输出容器
         */
        virtual void crypt(const char* const _log_data, size_t _input_len, AutoBuffer& _out_buff) = 0;
    };
}


#endif //MMLOG_ILOGCRYPT_H
