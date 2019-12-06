//
//  MMXFileLogger.h
//  MMMediaLogger
//
//  Created by sunfei on 2019/4/27.
//  Copyright © 2019 sunfei. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSInteger {
    UPLOADSTRATEGYTYPE_INFINITE_MINUTES = -1, // 不上传
    UPLOADSTRATEGYTYPE_15_MINUTES,   // 15分钟上传一次
    UPLOADSTRATEGYTYPE_60_MINUTES,   // 1小时上传一次
    UPLOADSTRATEGYTYPE_6_HOURS,      // 6小时上传一次
    UPLOADSTRATEGYTYPE_24_HOURS      // 24小时上传一次
} MMXFileUploadStrategyType;

@class MMXFileLoggerInfo;

@interface MMXFileConfiguration : NSObject

// appId
@property (nonatomic, copy) NSString *appId;

// deviceId
@property (nonatomic, copy) NSString *deviceId;

// upload url
@property (nonatomic, copy) NSString *uploadURL;

// upload strategy
@property (nonatomic, assign) MMXFileUploadStrategyType strategy;

// log cache dir
@property (nonatomic, copy) NSString *logDir;

// file idntifier
@property (nonatomic, copy) NSString *fileIdentifier;

// 是否加密
@property (nonatomic, assign) BOOL crypt;

// 是否压缩
@property (nonatomic, assign) BOOL compress;

// header
@property (nonatomic, strong) MMXFileLoggerInfo *header;

@end

@interface MMXFileLoggerInfo : NSObject

@property (nonatomic, strong, readonly) NSArray <NSString *> *heads;
@property (nonatomic, strong, readonly) NSString *body;

- (instancetype)initWithHeads:(NSArray *)heads andBody:(NSString *)body;

- (void)appendHeader:(NSString *)header;
- (void)setBody:(NSString *)body;

@end

@interface MMXFileLogger : NSObject

@property (nonatomic, readonly) NSError *error;

- (instancetype)initWithConfiguration:(MMXFileConfiguration *)configuration businessNames:(NSString *)businessName, ...;

// 默认更新第一个business的HeaderInfo
- (void)updateLoggerHeaderInfo:(MMXFileLoggerInfo *)headerInfo;

// 为Business更新HeaderInfo
- (void)updateLoggerHeaderInfoForBusinessName:(NSString *)businessName headerInfo:(MMXFileLoggerInfo *)headerInfo;

// 写入文件
- (void)writeToBusinessName:(NSString *)businessName info:(MMXFileLoggerInfo *)loggerInfo;
- (void)writeToBusinessName:(NSString *)businessName body:(NSString *)body headers:(NSString *)header, ...;

// 默认为第一个business写入log
- (void)writeBody:(NSString *)body headers:(NSString *)header, ...;

// 默认为第一个business写入log
- (void)flushWithBusinessName:(NSString *)businessName;

// 关闭Logger
- (void)closeLogger;

// 关闭business相关的logger
- (void)closeLoggerForBusinessName:(NSString *)businessName;

// 上传所有的log
- (void)forceUpload;

// 上传business的log
- (void)forceUploadForBusinessName:(NSString *)businessName;

// 暂停写入文件
- (void)pauseAllWrite:(BOOL)pause;

@end

NS_ASSUME_NONNULL_END
