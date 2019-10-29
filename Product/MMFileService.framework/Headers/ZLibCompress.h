//
// Created by chenwangwang on 2018/8/28.
//

#ifndef MMLOG_ZLIBCOMPRESS_H
#define MMLOG_ZLIBCOMPRESS_H

#include <zlib.h>
#include "ILogCompress.h"

namespace mmslog {

    class ZLibCompress : public ILogCompress {
    private:
        z_stream cstream_;
        bool is_compress = true;    // 默认是压缩模式
    public:

        ZLibCompress(bool _is_compress);

        /**
         * 压缩
         * @param _log_data 数据内存起始地址
         * @param _input_len 数据长度
         * @param out_ptr 输出内存地址
         * @param avail_out 可用的输出内存长度
         * @param write_len 压缩后的数据长度
         * @return 0 成功，否则失败
         */
        int compress(const void* const _log_data, size_t _input_len, Bytef * out_ptr, uInt avail_out, size_t &write_len) override;

        bool deCompress(const void *const _log_data, size_t _input_len, Bytef *out_ptr, uInt avail_out,
                        size_t &write_len) override;

        /**
         * 结束一次合并压缩， 与reset成对出现
         */
        void complete() override;

        /**
         * 合并压缩之前，需要执行一次该方法，与complete成对出现
         * @return true 成功，false 失败
         */
        bool reset() override;

    };

}

#endif //MMLOG_ZLIBCOMPRESS_H
