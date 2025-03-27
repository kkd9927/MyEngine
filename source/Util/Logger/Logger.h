#pragma once

//#define SPDLOG_HEADER_ONLY
//#include <spdlog/spdlog.h>
//#include <string>
//#include <memory>
//
//namespace Util
//{
//    class Logger
//    {
//    public:
//        static void Trace(const std::string& msg);
//        static void Debug(const std::string& msg);
//        static void Info(const std::string& msg);
//        static void Warn(const std::string& msg);
//        static void Error(const std::string& msg);
//        static void Critical(const std::string& msg);
//        
//    private:
//        static std::shared_ptr<spdlog::logger> GetLogger();
//        static std::shared_ptr<spdlog::logger> CreateLogger();
//
//        Logger() = delete;
//        ~Logger() = delete;
//
//        Logger(const Logger& rhs) = delete;
//        Logger& operator=(const Logger& rhs) = delete;
//    };
//}