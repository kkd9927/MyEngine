//#include "Util/Logger/Logger.h"
//
//#include <spdlog/sinks/stdout_color_sinks.h>
//#include <spdlog/sinks/basic_file_sink.h>
//
//#include "Util/FileSystem/FileSystem.h"
//
//namespace Util
//{
//    void Logger::Trace(const std::string& msg) { GetLogger()->trace(msg); }
//
//    void Logger::Debug(const std::string& msg) { GetLogger()->debug(msg); }
//
//    void Logger::Info(const std::string& msg) { GetLogger()->info(msg); }
//
//    void Logger::Warn(const std::string& msg) { GetLogger()->warn(msg); }
//
//    void Logger::Error(const std::string& msg) { GetLogger()->error(msg); }
//
//    void Logger::Critical(const std::string& msg) { GetLogger()->critical(msg); }
//    
//    /**
//     * @brief Logger 인스턴스는 클래스 정적 멤버 함수 내에서 정적 지역 변수로 관리됩니다.
//     * @brief 최초 호출시 CreateLogger 함수로 초기화 되며, 최초 이후 호출에 대해서는
//     * @brief 데이터 세그먼트에 정적으로 저장된 logger 객체를 반환합니다.
//     */
//    std::shared_ptr<spdlog::logger> Logger::GetLogger() {
//        static std::shared_ptr<spdlog::logger> logger = CreateLogger(); // 최초 호출시 초기화
//        return logger;
//    }
//
//    /**
//     * @brief GetLogger 함수 최초 호출시 한 번 호출됩니다.
//     */
//    std::shared_ptr<spdlog::logger> Logger::CreateLogger()
//    {
//        std::string logFilePath = FileSystem::GetExcutablePath() + "\\log";
//
//        // 콘솔 컬러 싱크
//        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
//        console_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
//        console_sink->set_level(spdlog::level::trace);
//
//        // 파일 싱크
//        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, true);
//        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
//        file_sink->set_level(spdlog::level::trace);
//
//        // 멀티 싱크 로거
//        auto logger = std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list{console_sink, file_sink});
//        logger->set_level(spdlog::level::trace);
//        spdlog::register_logger(logger);
//
//        return logger;
//    }
//}