#ifndef LOGGER_H 
#define LOGGER_H 
 
#include <iostream> 
#include <fstream> 
#include <string> 
 
// Перечисление уровней логирования 
enum class LogLevel { 
    Info,       // Информационное сообщение 
    Debug,      // Сообщение для отладки 
    Error       // Сообщение об ошибке 
}; 
 
class Logger { 
public: 
    // Конструктор, который принимает имя файла и уровень логирования 
    Logger(std::string filename, LogLevel level = LogLevel::Info); 
 
    // Деструктор, который закрывает файл 
    ~Logger(); 
 
    // Метод для изменения уровня логирования 
    void setLogLevel(LogLevel level); 
 
    // Метод для записи сообщения лога в файл и на консоль 
    void log(std::string message, LogLevel level = LogLevel::Info); 
 
private: 
    LogLevel m_logLevel;            // Уровень логирования 
    std::ofstream m_fileStream;     // Поток для записи в файл 
 
    // Метод для получения строки, соответствующей уровню логирования 
    std::string getLogLevelString(LogLevel level); 
}; 
 
#endif // LOGGER_H 
 
// Logger.cpp 
 
// #include "Logger.h" 
#include <iomanip> 
#include <ctime> 
 
// Конструктор класса 
Logger::Logger(std::string filename, LogLevel level) { 
    m_logLevel = level; // Установка уровня логирования 
    m_fileStream.open(filename.c_str(), std::ios::out | std::ios::app); // Открытие файла для записи 
} 
 
// Деструктор класса 
Logger::~Logger() { 
    m_fileStream.close(); // Закрытие файла 
} 
 
// Метод для изменения уровня логирования 
void Logger::setLogLevel(LogLevel level) { 
    m_logLevel = level; 
} 
 
// Метод для записи сообщения лога в файл и на консоль 
void Logger::log(std::string message, LogLevel level) { 
    // Проверка, нужно ли записывать сообщение в лог 
    if (level >= m_logLevel) { 
        std::time_t t = std::time(nullptr); 
        std::tm tm = *std::localtime(&t); 
 
        std::string logLevelString = getLogLevelString(level); // Получение строки для уровня логирования 
        std::time_t now = std::time(nullptr); // Получение текущего времени в секундах
        std::tm tm_ = *std::localtime(&now); // Преобразование текущего времени в структуру std::tm
        char buffer[100]; // Создание буфера для хранения отформатированной даты и времени
        std::strftime(buffer, 100, "%d.%m.%Y %H:%M:%S", &tm); // Форматирование даты и времени и запись в буфер
        std::string timestamp(buffer); // Преобразование отформатированной даты и времени в std::string
        std::string logMessage = "[" + timestamp + "] " + "[" + logLevelString + "] " + message; // Формирование сообщения лога 
 
        std::cout << logMessage << std::endl; // Вывод сообщения на консоль 
        m_fileStream << logMessage << std::endl; // Запись сообщения в файл 
    } 
} 
 
// Метод для получения строки, соответствующей уровню логирования 
std::string Logger::getLogLevelString(LogLevel level) { 
    switch (level) { 
        case LogLevel::Info: 
            return "INFO"; 
        case LogLevel::Debug: 
            return "DEBUG"; 
        case LogLevel::Error: 
            return "ERROR"; 
        default: 
            return "UNKNOWN"; 
    } 
} 
// #include "Logger.h"

int main() {
    // Создание объекта класса Logger с именем файла "log.txt" и уровнем логирования LogLevel::Debug
    Logger logger("log.txt", LogLevel::Debug);

    // Запись сообщений лога разных уровней
    logger.log("This is an info message", LogLevel::Info);
    logger.log("This is a debug message", LogLevel::Debug);
    logger.log("This is an error message", LogLevel::Error);

    // Изменение уровня логирования
    logger.setLogLevel(LogLevel::Info);

    // Запись сообщения лога с новым уровнем
    logger.log("This message should be logged with Info level", LogLevel::Info);

    return 0;
}
