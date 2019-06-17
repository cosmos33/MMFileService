//
// Created by chenwangwang on 2018/9/18.
//

#ifndef MMLOG_ILOGMANAGER_H
#define MMLOG_ILOGMANAGER_H

#include <memory>
#include "MMFileInfo.h"
#include "ILogCrypt.h"
#include "ILogCompress.h"

namespace mmslog {

    class ILogManager {
    public:
        /**
         * 启动日志存储模块，将会打开mmap，只有执行了该方法之后，才能写日志
         */
        virtual void start() = 0;

        /**
         * 写日志
         * @param _info 日志信息
         * @param _log 日志内容
         */
        virtual void writeLog(const MMLogInfo *_info) = 0;

        /**
         * 将缓冲区的日志刷新到日志文件中
         */
        virtual void flush() = 0;

        /**
         * 关闭日志读写功能，该方法将会回收缓冲区资源，如果需要再次写日志，需要重新执行start方法
         */
        virtual void close() = 0;

        /**
         * 设置加密逻辑处理对象
         */
        virtual void setCrypt(std::shared_ptr <ILogCrypt> crypt) = 0;

        /**
         * 设置压缩逻辑处理对象
         */
        virtual void setCompress(std::shared_ptr <ILogCompress> compress) = 0;

        /**
         * 重新开启一个新的文件来存储数据，
         * 此方法用于业务可能需要将之前的文件做转移的时候，防止一边读一边写的情况发生
         */
        virtual void openNewLogFile() = 0;

        /**
         * 暂停日志的写入
         * @param pause true 暂停，false 继续
         */
        virtual void setPauseLogWrite(bool pause) = 0;

        /**
         * 更新统一参数信息
         */
        virtual void updateCommonInfo(const MMLogInfo &mmLogInfo) = 0;
    };

}

#endif //MMLOG_ILOGMANAGER_H
