#ifndef QHLOGGERDEFINE_H
#define QHLOGGERDEFINE_H

/// Logging module (multiple modules can write logs to different files)
enum QhLoggerModule {
    LoggerMMain = 0,   // 默认模块
    LoggerMCustom = 10 // 自定义模块
};

/// @brief logger level（追踪，调试、信息、警告、严重、错误）
enum QhLoggerLevel {
    LoggerLTrace = 0,
    LoggerLDebug = 1,
    LoggerLInfo = 2,
    LoggerLWarring = 3,
    LoggerLCritical = 4,
    LoggerLFail = 5
};

#endif // QHLOGGERDEFINE_H
