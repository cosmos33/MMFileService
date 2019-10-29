//
// Created by chenwangwang on 2018/8/24.
//

#ifndef MMLOG_MMLOGUTILS_H
#define MMLOG_MMLOGUTILS_H

#include <string>
#include <sys/file.h>
#include <zconf.h>
#include <sys/stat.h>
#include <dirent.h>
#include <functional>
#include "MMFileInfo.h"
#include "ptrbuffer.h"
#ifdef __ANDROID__
#include <sys/vfs.h>    /* 或者 <sys/statfs.h> */
#elif __APPLE__
#include <sys/mount.h>
#endif

namespace mmslog {

    extern const long kMaxLogAliveTime;


    class MMLogUtils {
    public:
        /**
         * 判断一个文件/目录是否存在
         * @param filePath 路径
         * @return true 存在，false 不存在
         */
        static bool isFileExit(const char* filePath);

        /**
         * 判断一个路径是否是文件夹
         * @param dirPath 路径
         * @return true 是文件夹，false 不是
         */
        static bool isDir(const char* dirPath);

        /**
         * 删除一个目录下的所有文件
         * @param _forder_path 路径
         */
        static void __del_files(const std::string& _forder_path);
        static void __del_timeout_file(const std::string& _log_path);
        /**
         * 遍历一个目录下的所有文件
         * @param dirPath 目录路径
         * @param lambda 需要回调的方法, return true 代表break，return false代表继续循环下一条
         * file_abs_path 是文件的绝对路径， file_name是文件的名称
         */
        static void traverseFolder(const char* dirPath, std::function<bool(std::string file_abs_path, std::string file_name)> lambda);

        static bool __append_file(const std::string& _src_file, const std::string& _dst_file);

        static void log_formater(int8_t _head_separator_start, int8_t _head_separator_end,
                          int8_t _body_separator_start, int8_t _body_separator_end,
                          const MMLogInfo *_info, PtrBuffer &_log);

        static bool startWith(std::string tar, std::string key);

        static bool endWith(std::string tar, std::string key);

        /**
         * 获取当前系统剩余的可用存储空间占比
         * @param free 剩余的存储空间占比
         * @return 0成功获取，否则获取失败
         */
        static int getSystemDiskFreeRate(std::string path, double *free);

        /**
         * 获取当前系统剩余的可用存储空间
         * @param free 剩余的存储空间
         * @return 0成功获取，否则获取失败
         */
        static int getSystemDiskFree(std::string path, double *free);
    };

}


#endif //MMLOG_MMLOGUTILS_H
