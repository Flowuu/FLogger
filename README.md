# FLogger.hpp

**FLogger.hpp** is a C++ logging library designed for simplicity and ease of use. It provides functionalities for console-based logging with support for various log levels, timestamps, custom text colors, and error handling. It works on Windows platforms and is ideal for debugging or logging in applications, including game reverse engineering projects.

## Features

- **Log Levels**: Different log levels for organizing output messages.
- **Timestamps**: Option to enable or disable timestamps for log entries.
- **Customizable Colors**: Different colors for each log level for better readability.
- **Error Handling**: Retrieve last error messages via the Windows API.
- **Input Handling**: Supports receiving input from the user and automatically interpreting hexadecimal values.
- **Cursor Visibility**: Toggle console cursor visibility.
- **Clear Console**: Clear the console output when needed.
- **File Output**: Optionally output logs to the console.
- **Memory Efficient**: Designed to be lightweight for efficient memory usage.

## Installation

1. Clone or download the repository.
2. Include `FLogger.hpp` in your project.
3. Optionally, link with any required libraries for your platform (such as the Windows SDK).

## Usage

### Creating a Logger Instance

To use the FLogger, use the global instance or create an instance of the `FLog` class:

```cpp
#include "FLogger.hpp"

int main() {
    // Log a message with the default white color
    console->log("This is a regular log message.");

    // Log a message with a specific log level
    console->log(LogLevel::info, "This is an info message.");

    // Log an error
    console->report(LogLevel::error, "This is an error message.");

    // Enable timestamp in logs
    console->toggleTimestamp();

    // Get user input
    int value = console->getInput<int>("Enter a number: ");

    // Display last error message
    console->log("%s\n", console->getLastError().c_str());

    return 0;
}
```
### Input Handling
Use `getInput<T>()` to prompt the user for input, where `T` is the type of input (e.g., `int`, `float`, `std::string`):
```cpp
int number = console->getInput<int>("Enter a number: ");
```

### Error Handling
Use `getLastError()` to retrieve the most recent error message from the Windows API:
```cpp
console->log("%s\n", console->getLastError().c_str());
// or
std::cout << "Last Error: " << console->getLastError() << std::endl;
```

### Console Manipulation
- Toggle Cursor Visibility: Use `showCursor()` to toggle the cursor visibility.
- Clear Console: Use `clear()` to clear the entire console output.
