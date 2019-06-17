//
// Created by chenwangwang on 2018/8/28.
//

#ifndef MMLOG_ILOGCOMPRESS_H
#define MMLOG_ILOGCOMPRESS_H

#include "autobuffer.h"
#include <zconf.h>

namespace mmslog {
    class ILogCompress {
    public:
        /**
         * 为一段文本进行压缩，压缩后的内容存放到_out_buff里
         * @param _log_data 日志内容起始指针
         * @param out_ptr 压缩后的内容写入内存指针
         * @param avail_out 压缩后的内容存放区域可用大小
         * @param write_len 成功写入的字段大小
         * @return true 压缩成功，false 压缩失败
         */
        virtual int compress(const void* const _log_data, size_t _input_len, Bytef * out_ptr, uInt avail_out, size_t &write_len) = 0;

        /**
         * 为一段文本进行解压缩，解压缩后的内容存放到_out_buff里
         * @param _log_data 待解压的数据内存指针
         * @param _input_len 待解压数据长度
         * @param out_ptr 数据输出地址
         * @param avail_out 输出地址可用长度
         * @param write_len 输出后的数据长度
         * @return true 解压缩成功，false 失败
         */
        virtual bool deCompress(const void* const _log_data, size_t _input_len, Bytef * out_ptr, uInt avail_out, size_t &write_len) = 0;

        /**
         * 结束以一系列压缩，从开始到结束，中间可以包含多个compress <br/>
         * 该方法和reset应该是成对出现的
         */
        virtual void complete() = 0;

        /**
         * 重置
         * 该方法和complete应该是成对出现的
         * @return true 代表重置成功，false 重置失败
         */
        virtual bool reset() = 0;
    };
}


#endif //MMLOG_ILOGCOMPRESS_H
