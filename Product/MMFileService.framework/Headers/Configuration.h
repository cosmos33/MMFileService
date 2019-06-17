//
// Created by chenwangwang on 2018/8/21.
//

#ifndef MMLOG_MMLOGCONFIGURATION_H
#define MMLOG_MMLOGCONFIGURATION_H

#include <string>
#include "MMFileInfo.h"


class IUpload {
    public:
        virtual bool UploadFile(std::string file) = 0; //返回值: true:代表上传成功，文件可以删除了。
};


namespace mmslog {

enum LogUploadStrategyType {
    LOGUPLOADSTRATEGYTYPE_15_MINUTES = 15 * 60,
    LOGUPLOADSTRATEGYTYPE_60_MINUTES = 60 * 60,
    LOGUPLOADSTRATEGYTYPE_6_HOURS = 6 * 60 * 60,
    LOGUPLOADSTRATEGYTYPE_24_HOURS = 24 * 60 * 60
};

#define MMLOG_SIZE_BUFFER 307200

    class Configuration {
    public:
        std::string app_id;                                      //AppID
        std::string device_id;                                  //设备唯一标识ID
        std::string log_upload_url;                             //用于上传的http协议url地址
        LogUploadStrategyType log_upload_strategy = LOGUPLOADSTRATEGYTYPE_60_MINUTES;              //上传时间间隔。

        std::string log_dir;                                    // 日志文件所在目录
        std::string cache_dir;                                  // 缓存文件所在目录
        std::string file_prefix;                                // 文件前缀名称
        size_t log_file_length;                                 // 日志文件最大值
        size_t cache_buffer_length = MMLOG_SIZE_BUFFER;         // 缓存大小
        bool is_crypt = false;                                  // 是否需要加密
        bool is_compress = true;                                // 是否需要压缩日志
        bool is_print_tip_log = false;                          // 是否需要打印提示日志
        int8_t head_wrapper_start = 1;                     // 头tag的前置分隔符
        int8_t head_wrapper_end = 4;                       // 头tag的后置分隔符
        int8_t body_wrapper_start = 2;                     // 内容区域tag的前置分隔符
        int8_t body_wrapper_end = 3;                       // 内容区域tag的后置分隔符
        char magic_crypt_no_compress_start = 18;                // 一段数据（包含多个head+body的组合）的控制头（如果自己设置，那么解析脚本也需要做相应修改）: 加密，但是不压缩
        char magic_crypt_compress_start = 19;                   // 一段数据（包含多个head+body的组合）的控制头（如果自己设置，那么解析脚本也需要做相应修改）: 即加密又压缩
        char magic_no_crypt_compress_start = 20;                // 一段数据（包含多个head+body的组合）的控制头（如果自己设置，那么解析脚本也需要做相应修改）: 不加密，只压缩
        char magic_no_crypt_no_compress_start = 04;             // 一段数据（包含多个head+body的组合）的控制头（如果自己设置，那么解析脚本也需要做相应修改）: 不加密，不压缩
        char kMagicEnd = 0;                                     // 一段数据（包含多个head+body的组合）的尾标识（如果自己设置，那么解析脚本也需要做相应修改）
        MMLogInfo *common_log_info = nullptr;                   // 通用的信息
        std::shared_ptr<IUpload> upload = nullptr;                   // 上层定义上传接口。      
    };
}


#endif //MMLOG_MMLOGCONFIGURATION_H
