// MIT License
//
// Copyright(c) 2025 Flowu
//
// Permission is hereby granted,
// free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and / or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all copies
// or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS",
// WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef FLOGGER_HPP
#define FLOGGER_HPP

#include <Windows.h>

#include <iostream>
#include <sstream>

enum LogLevel : unsigned int {
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
    warn    = orange,
    error   = red,
};

struct FLog {
   private:
    inline static HANDLE m_consoleHandle = nullptr;
    inline static bool m_timeStamp       = false;

    void logMessage(LogLevel level, const char* title, const char* input, va_list args) {
        FLog::setColor(level);

        if (m_timeStamp) std::cout << __TIME__ << "| ";

        if (title != nullptr) {
            std::cout << "[" << title << "] ";
            resetColor();
        }

        vprintf(input, args);
        resetColor();
    }

   public:
    std::string getLastError() { return std::error_code(static_cast<int>(GetLastError()), std::system_category()).message(); }

    template <typename T>
    T getInput(const char* input, ...) {
        va_list args;
        va_start(args, input);
        logMessage(LogLevel::white, nullptr, input, args);
        va_end(args);

        std::string inputStr;
        std::getline(std::cin, inputStr);

        std::stringstream ss(inputStr);
        T value;

        if constexpr (std::is_integral_v<T>)
            if (inputStr.substr(0, 2) == "0x" || inputStr.substr(0, 2) == "0X") ss >> std::hex;

        ss >> value;
        return value;
    }

    template <typename T>
    T getInput(LogLevel level, const char* input, ...) {
        va_list args;
        va_start(args, input);
        logMessage(level, nullptr, input, args);
        va_end(args);

        std::string inputStr;
        std::getline(std::cin, inputStr);

        std::stringstream ss(inputStr);
        T value;

        if constexpr (std::is_integral_v<T>)
            if (inputStr.substr(0, 2) == "0x" || inputStr.substr(0, 2) == "0X") ss >> std::hex;

        ss >> value;
        return value;
    }

    void report(LogLevel level, const char* input, ...) {
        const char* title;
        switch (level) {
            case LogLevel::info:
                title = "i";
                break;
            case LogLevel::warn:
                title = "!";
                break;
            case LogLevel::error:
                title = "-";
                break;
            case LogLevel::success:
                title = "+";
                break;
            default:
                title = ">";
                break;
        }

        va_list args;
        va_start(args, input);
        logMessage(level, title, input, args);
        va_end(args);
    }

    void log(const char* input, ...) {
        va_list args;
        va_start(args, input);
        logMessage(LogLevel::white, nullptr, input, args);
        va_end(args);
    }

    void log(LogLevel level, const char* input, ...) {
        va_list args;
        va_start(args, input);
        logMessage(level, nullptr, input, args);
        va_end(args);
    }

    void showCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        if (!GetConsoleCursorInfo(m_consoleHandle, &cursorInfo)) return;

        cursorInfo.bVisible = !cursorInfo.bVisible;
        SetConsoleCursorInfo(m_consoleHandle, &cursorInfo);
    }

    void toggleTimestamp() { m_timeStamp = !m_timeStamp; }

    void resetColor() { setColor(LogLevel::white); }

    void setColor(LogLevel level) {
        if (level < LogLevel::black || level > LogLevel::white) level = LogLevel::white;

        SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(level));
    }

    void clear() {
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
        DWORD written;
        COORD coord{0};

        if (!GetConsoleScreenBufferInfo(m_consoleHandle, &bufferInfo)) return;

        FillConsoleOutputCharacter(m_consoleHandle, ' ', bufferInfo.dwSize.X * bufferInfo.dwSize.Y, coord, &written);
        SetConsoleCursorPosition(m_consoleHandle, coord);
    }

    void destroy() {
        CloseHandle(m_consoleHandle);
        FreeConsole();
    }

    FLog(const char* title = "Untitled") {
        AllocConsole();
        freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

        m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (title != nullptr) SetConsoleTitleA(title);
    }

    ~FLog() { destroy(); }
};
inline std::unique_ptr<FLog> console = std::make_unique<FLog>();

#endif  // !FLOGGER_HPP
