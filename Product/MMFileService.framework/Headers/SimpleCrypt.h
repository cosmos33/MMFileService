//
// Created by chenwangwang on 2018/8/29.
//

#ifndef MMLOG_SIMPLECRYPT_H
#define MMLOG_SIMPLECRYPT_H

#include "../base/ILogCrypt.h"

namespace mmslog {

#define KEY 13

    class SimpleCrypt : public ILogCrypt {
    public:
        void crypt(const char *const _log_data, size_t _input_len, AutoBuffer &_out_buff) override;
    };

}


#endif //MMLOG_SIMPLECRYPT_H
