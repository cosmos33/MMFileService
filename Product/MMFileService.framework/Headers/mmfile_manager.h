

#ifndef MMLOG_MMFILE_MANAGE_MMFILE_MANAGE_H
#define MMLOG_MMFILE_MANAGE_MMFILE_MANAGE_H

#include <unordered_map>

#include "Configuration.h"
#include "LogManager.h"
#include "log_upload.h"
#include "MMFileInfo.h"
//class Configuration;
//class LogManager;
//class LogUpload;
//class MMLogInfo;

namespace mmslog {

class MMFileManager {
    std::shared_ptr<Configuration> configuration_;
    std::shared_ptr<LogManager> logManager_;
    std::shared_ptr<LogUpload> logUpload_;
public:
    MMFileManager();
    virtual ~MMFileManager();

    /*返回值:   成功:   0。
                失败:   -1001: app_id 为空。
                        -1002: device_id 为空。
                        -1003: log_dir 为空。
                        -1004: file_prefix 为空。
                        -2001: file_prefix 冲突，已经存在相同的file_prefix。
     * 
     */
    static int Open(std::string business[], int num, const std::shared_ptr<Configuration> configuration);

    static std::shared_ptr<MMFileManager> GetMMFileManager(std::string business);

    /*返回值:   成功:   0。
     *          失败:   -1: business 不存在。
     */
    static int UpdateCommonInfo(std::string business, const MMLogInfo &info);

    /*返回值:   成功:   0。
     *          失败:   -1: business 不存在。
     */
    static int Write(std::string business, const MMLogInfo &info);

    /*返回值:   成功:   0。
     *          失败:   -1: business 不存在。
     */
    static int ForceUpload(std::string business);
    static int ForceUpload_synchronized(std::string business);

    /*返回值:   成功:   0。
     *          失败:   -1: business 不存在。
     */
    static int Close(std::string business);    

    static void PauseAllWrite(bool pause);
};

}

void MMFileBaseToolLogSetLevel(int level);
#endif //MMLOG_MMFILE_MANAGE_MMFILE_MANAGE_H

