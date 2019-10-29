#ifndef _MDLOG_MDLOG_H_
#define _MDLOG_MDLOG_H_
#include <set>
#include <iostream>

typedef enum {
    K_MDLOG_LEVEL_ALL = 0,
    K_MDLOG_LEVEL_VERBOSE = 1,
    K_MDLOG_LEVEL_DEBUG = 2,   
    K_MDLOG_LEVEL_INFO = 3,   
    K_MDLOG_LEVEL_WARN = 4, 
    K_MDLOG_LEVEL_ERROR = 5, 
    K_MDLOG_LEVEL_FATAL = 6,
    K_MDLOG_LEVEL_OFF = 7 
} MDLogLevel;

/* 初始化文件相关信息（如需写入文件则必须先调用此函数）
 * 入参：   log_path：文件目录
 *          log_name_prefix：文件前缀
 * 返回值： 0:成功，< 0:失败。 (入参log_path或入参log_name_prefix有为空则会返回-1)。
 */
extern int MDLogInitFileInfo(std::string log_path, std::string log_name_prefix);

/* 设置写入文件开关
 * 入参：   open: true为开，fase为关。
 *          truncate：把所有之前的文件清除。
 * 返回值： 0:成功，< 0:失败。（失败的原因是创建mmfile失败，log_name_prefix已经存在）
 */
extern int MDLogSetFileOpen(bool open, bool truncate);

/* 获取log文件，所有文件将写入files内，如不删除则下次获取依然存在。
 * 返回值：0:成功, < 0:失败。（失败的原因是当前设置写入文件开关为关）
 */
extern int MDLogGetFile(std::set<std::string> &files);

/* 设置是否打印到控制台
*/
extern void MDLogSetConsoleOpen(bool open);

/* 设置输出的日志级别，白名单除外
*/
extern void MDLogSetLevel(MDLogLevel level);

/* 添加到白名单
*/
extern void MDLogAddWhiteTag(std::string tag, MDLogLevel level);            //增加level。

/* 从白名单内删除
*/
extern void MDLogDelWhiteTag(std::string tag);

/* 清空白名单
*/
extern void MDLogClearWhiteTags();

/* 输出日志，为了提高速度应使用下面定义的MDLogP宏。
*/
extern void MDLogPrint(std::string tag, MDLogLevel level, const char *file, const char *func, int line, const char *format, ...);

/* 这两个变量禁止外部代码直接更改，如需要改变它们的值请调用上面声明的相关函数。
 * 这两个变量声明为全局只为宏MDLogP优化在大部分情况下减少一次进入函数。
 */
extern bool g_mdlog_file_open;
extern bool g_mdlog_console_open;

/* 输出日志。
 */
#define MDLogP(tag, level, format, ...) { if (g_mdlog_file_open == true || g_mdlog_console_open == true) MDLogPrint(tag, level, __FILE__, __func__, __LINE__, format, ##__VA_ARGS__); }
                                                                 //把宏的名称改成和以前的保持一致。
#define MDLogV(tag, format, ...) MDLogP(tag, K_MDLOG_LEVEL_VERBOSE, format, ##__VA_ARGS__)
#define MDLogD(tag, format, ...) MDLogP(tag, K_MDLOG_LEVEL_DEBUG, format, ##__VA_ARGS__)
#define MDLogI(tag, format, ...) MDLogP(tag, K_MDLOG_LEVEL_INFO, format, ##__VA_ARGS__)
#define MDLogW(tag, format, ...) MDLogP(tag, K_MDLOG_LEVEL_WARN, format, ##__VA_ARGS__)
#define MDLogE(tag, format, ...) MDLogP(tag, K_MDLOG_LEVEL_ERROR, format, ##__VA_ARGS__)
#define MDLogF(tag, format, ...) MDLogP(tag, K_MDLOG_LEVEL_FATAL, format, ##__VA_ARGS__)

#endif //_MDLOG_MDLOG_H_
