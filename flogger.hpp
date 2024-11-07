#ifndef FLOGGER_HPP
#define FLOGGER_HPP

#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>
#include <string_view>
#include <cstdarg>

#define ALLOCATE_CONSOLE
#define GLOBAL_CONSOLE

#define LOG_ERROR_AT() \
    console.report(LogLevel::error, "%s -> %d", __FUNCSIG__, __LINE__)

enum class LogLevel : unsigned int {
    black,
    blue,
    green,
    cyan,
    red,
    magenta,
    orange,
    lightgray,
    darkgray,
    lightblue,
    lightgreen,
    lightcyan,
    lightred,
    lightmagenta,
    yellow,
    white,

    success = lightgreen,
    info    = lightcyan,
    warning = orange,
    error   = red,
};

class FLog {
private:
    FILE* filePointer = nullptr;
    bool timestampEnabled = false;
    HANDLE consoleHandle;

    void resetColor() const {
        setColor(LogLevel::white);
    }

    void logMessage(LogLevel level, const char* title, const char* format, va_list args, bool endLine = true) const {
        setColor(level);

        if (timestampEnabled)
            std::cout << __TIME__ << "| ";

        if (title)
            std::cout << "[" << title << "] ", resetColor();

        vprintf(format, args);
        resetColor();

        if (endLine)
            std::cout << std::endl;
    }

public:
    explicit FLog(const char* title) {
#ifdef ALLOCATE_CONSOLE
        AllocConsole();
        freopen_s(&filePointer, "CONOUT$", "w", stdout);
#endif
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (title != nullptr)
            SetConsoleTitleA(title);
    }

    FLog() : FLog("Untitled") {}

    ~FLog() {
        close();
    }

    void close() {
        if (!filePointer)
            return;

        fclose(filePointer);
        FreeConsole();
        filePointer = nullptr;
    }

    void clearEx() const {
        system("cls");
    }

    void clear() const {
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        DWORD written;
        COORD coord = { 0, 0 };

        if (!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
            return;

        FillConsoleOutputCharacter(consoleHandle, ' ', bufferInfo.dwSize.X * bufferInfo.dwSize.Y, coord, &written);

        SetConsoleCursorPosition(consoleHandle, coord);
    }

    void setColor(LogLevel level) const {
        if (level < LogLevel::black || level > LogLevel::white)
            level = LogLevel::white;

        SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(level));
    }

    void log(const char* format, ...) const {
        va_list args;
        va_start(args, format);
        logMessage(LogLevel::white, nullptr, format, args);
        va_end(args);
    }

    void log(LogLevel level, const char* format, ...) const {
        va_list args;
        va_start(args, format);
        logMessage(level, nullptr, format, args);
        va_end(args);
    }

    void logInline(const char* format, ...) const {
        va_list args;
        va_start(args, format);
        logMessage(LogLevel::white, nullptr, format, args, false);
        va_end(args);
    }

    void logInline(LogLevel level, const char* format, ...) const {
        va_list args;
        va_start(args, format);
        logMessage(level, nullptr, format, args, false);
        va_end(args);
    }

    void logWithTitle(LogLevel level, const char* title, const char* format, ...) const {
        va_list args;
        va_start(args, format);
        logMessage(level, title, format, args);
        va_end(args);
    }

    void report(LogLevel level, const char* format, ...) const {
        const char* title = nullptr;

        switch (level) {
        case LogLevel::info: title =    "  Info "; break;
        case LogLevel::warning: title = "Warning"; break;
        case LogLevel::error: title =   " Error "; break;
        case LogLevel::success: title = "Success"; break;
        default: title =                "  Log  "; break;
        }

        va_list args;
        va_start(args, format);
        logMessage(level, title, format, args);
        va_end(args);
    }

    void showCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;

        if (!GetConsoleCursorInfo(consoleHandle, &cursorInfo))
            return;

        cursorInfo.bVisible = !cursorInfo.bVisible;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    void toggleTimestamp() {
        timestampEnabled = !timestampEnabled;
    }
};

#ifdef GLOBAL_CONSOLE
inline FLog console(nullptr);
#endif

#endif // FLOGGER_HPP
