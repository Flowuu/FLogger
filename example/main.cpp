#include "fLogger.hpp"

int main() {
    console->log("\n------------with-time-stamp--------------\n\n");

    console->toggleTimestamp();
    console->log("log default\n");
    console->log(LogLevel::cyan, "log colored\n\n");

    console->report(LogLevel::magenta, "this is report (default)\n");
    console->report(LogLevel::info, "this is info\n");
    console->report(LogLevel::warn, "this is warning\n");
    console->report(LogLevel::error, "this is error\n");
    console->toggleTimestamp();

    console->log("\n------------without-time-stamp-----------\n\n");

    console->log("log default\n");
    console->log(LogLevel::cyan, "log colored\n\n");

    console->report(LogLevel::magenta, "this is report (default)\n");
    console->report(LogLevel::info, "this is info\n");
    console->report(LogLevel::warn, "this is warning\n");
    console->report(LogLevel::error, "this is error\n");

    console->log("\n------------get-last-error---------------\n\n");

    HANDLE hHandle = CreateFile(L"non_existent_file.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);  // Try to open a non-existent file to set the error

    if (hHandle == INVALID_HANDLE_VALUE)
        console->report(LogLevel::error, "%s\n", console->getLastError().c_str());
    else
        console->log("handle -> %x\n", hHandle);

    console->log("\n------------get-input--------------------\n\n");

    int intInput = console->getInput<int>("[%s] input -> ", "int");
    console->log("[int] output -> %d\n\n", intInput);

    std::string strInput = console->getInput<std::string>("[std::string] input -> ");
    console->log("[std::string] output -> %s\n\n", strInput.c_str());

    DWORD dValue = console->getInput<DWORD>("[DWORD] input -> ");
    console->log("[DWORD] output -> %x\n\n", dValue);

    console->getInput<int>("");

    return 0;
}
