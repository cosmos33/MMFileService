//
// Created by chenwangwang on 2018/8/22.
//

#ifndef MMLOG_LOGMANAGER_H
#define MMLOG_LOGMANAGER_H

#include "Configuration.h"
#include "log_buffer.h"
#include "HandlerThread.h"
#include "ILogCrypt.h"
#include "ILogCompress.h"
#include "MMFileInfo.h"
#include "ILogManager.h"

using namespace mmslog;
class LogUpload;

namespace mmslog {

    using MLock = std::lock_guard<std::mutex>;
    using MRLock = std::lock_guard<std::recursive_mutex>;
    using UNILock = std::unique_lock<std::mutex>;

    static bool ALL_PAUSE_WRITE_LOG = false;

    enum Event {
        WriteError,
        OutOfBuffer,
        OpenMMPError,
        MoveOldFile,
        GetDiskFreeError,
        DiskFreeIsLow
    };


    class EventListener {
    public:
        virtual void onEvent(Event event, std::string msg) = 0;
    };

    /**
     * 高效日志存储类
     */
    class LogManager : public ILogManager {
    private:
        std::recursive_mutex mOpenStatusMutex;
        std::mutex mLogFileMutex;                                       // 日志文件操作的锁
        std::mutex mBufferMutex;                                        // 缓冲区操作的锁
        bool isStart = false;                                           // 是否启动了日志存储模块
        bool isUseMMap = true;                                          // 是否使用了mmap作为缓冲区
        HandlerThread *mHandlerThread = nullptr;                                  // 异步存储缓冲区日志到文件的线程
        std::shared_ptr<Handler> mAsyncHandler = nullptr;                                         // 向异步线程发送消息的handler
        std::shared_ptr<Runnable> mAsyncRunnable = nullptr;
        std::shared_ptr<HandlerThread> mMoveOldFileThread = nullptr;
        std::shared_ptr<Handler> mMoveOldFileHandler = nullptr;
        std::shared_ptr<Runnable> mMoveOldFileRunnable = nullptr;
        std::shared_ptr<Configuration> mConfiguration = nullptr;
        std::shared_ptr<LogBuffer> mLogBuffer = nullptr;                // 用来读写buffer的对象
        std::shared_ptr<ILogCrypt> mCrypt = nullptr;
        std::shared_ptr<ILogCompress> mCompress = nullptr;
        bool mNeedOpenLogFile = false;
        bool mPauseWriteLog = false;                                    // 暂停写入日志，该开关可以动态设置
        std::shared_ptr<EventListener> mEventListener = nullptr;
    private:
        /**
         * 打开一个mmap缓存
         * @param buffer_fd 文件描述符
         * @param buffer_size 缓存大小
         * @return 打开失败：nullptr，成功：缓存地址
         */
        char* openMMap(int buffer_fd, size_t buffer_size);

        void writeASync(const MMLogInfo *pInfo);

        void log2file();

        void __make_logfilename(const timeval& _tv, const std::string& _logdir,
                                const char* _prefix, const std::string& _fileext,
                                char* _filepath, unsigned int _len, bool forceOpenNewFile = false);

        long __get_next_fileindex(const std::string &_fileprefix, const std::string &_fileext);

        bool __writefile(FILE *_file, std::string filePath, const void *extraData, size_t length);

        /**
         * 异步线程存储缓冲区日志到文件
         */
        void ASyncSave2File();

        void moveOldFile2Log();

        bool write2file(std::string dir, const void *extraData, size_t length);

        /**
         * 封装往缓冲区写入数据的逻辑
         * @return true 写入成功，false 失败
         */
        bool write2BufferInternal(const void *_data, size_t _length);

    public:
        LogManager(const std::shared_ptr<Configuration> configuration);

        void start() override;

        void writeLog(const MMLogInfo *_info) override;

        void upload();

        void flush() override;

        void close() override;

        void setCrypt(std::shared_ptr<ILogCrypt> crypt) override;

        void setCompress(std::shared_ptr<ILogCompress> compress) override;

        void openNewLogFile() override;

        void setPauseLogWrite(bool pause) override;

        static void pauseAllLogManager(bool pauseAll);

        void updateCommonInfo(const MMLogInfo &mmLogInfo) override;

        void log2file(const void *extraData, size_t length);

        void setEventListener(const std::shared_ptr<EventListener> &eventListener);
    };

}


#endif //MMLOG_LOGMANAGER_H
