#ifndef BASE_TOOL_LOG_LOG_H_
#define BASE_TOOL_LOG_LOG_H_

/* 日志级别定义
 */
typedef enum {
    K_BASETOOL_LOG_LEVEL_ALL = 0,
    K_BASETOOL_LOG_LEVEL_VERBOSE = 1,
    K_BASETOOL_LOG_LEVEL_DEBUG = 2,
    K_BASETOOL_LOG_LEVEL_INFO = 3,
    K_BASETOOL_LOG_LEVEL_WARN = 4,
    K_BASETOOL_LOG_LEVEL_ERROR = 5,
    K_BASETOOL_LOG_LEVEL_FATAL = 6,
    K_BASETOOL_LOG_LEVEL_OFF = 7
} BaseToolLogLevel;

/* 下面三个接口禁止外部直接调用。
 */
extern BaseToolLogLevel g_basetool_log_level;
extern void BaseToolLogPrint(BaseToolLogLevel level, const char *file, const char *func, int line, const char *format, ...);
#define BaseToolLogP(level, format, ...) { if (level >= g_basetool_log_level) BaseToolLogPrint(level, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__); }

/* 设置输出日志级别。
 */
extern void BaseToolLogSetLevel(BaseToolLogLevel level);

/* 六个级别的日志输出
 */
#define BaseToolLogV(format, ...) BaseToolLogP(K_BASETOOL_LOG_LEVEL_VERBOSE, format, ##__VA_ARGS__)
#define BaseToolLogD(format, ...) BaseToolLogP(K_BASETOOL_LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define BaseToolLogI(format, ...) BaseToolLogP(K_BASETOOL_LOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define BaseToolLogW(format, ...) BaseToolLogP(K_BASETOOL_LOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define BaseToolLogE(format, ...) BaseToolLogP(K_BASETOOL_LOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define BaseToolLogF(format, ...) BaseToolLogP(K_BASETOOL_LOG_LEVEL_FATAL, format, ##__VA_ARGS__)

/* 日志输出，一定输出，仅用于临时调试。
 */
#define BaseToolLog(format, ...) BaseToolLogP(K_BASETOOL_LOG_LEVEL_OFF, format, ##__VA_ARGS__)

#endif //BASE_TOOL_LOG_LOG_H_
