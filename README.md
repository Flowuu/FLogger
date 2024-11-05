# FLogger

FLogger is a simple yet powerful logging library designed specifically for reverse engineering, game development, and related applications. It provides a console logging interface with customizable log levels, timestamps, and color-coded output to facilitate debugging, monitoring, and analysis of game behavior.

[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)

## Features

- **Color-Coded Logging:** Easily distinguish between different log levels with color-coded output, making it simpler to analyze logs during reverse engineering.
- **Timestamp Support:** Optionally include timestamps in your log messages to track when events occur, which is crucial for analyzing game mechanics and behaviors.
- **Console Management:** Automatically allocates a console window for output, making it suitable for console applications and tools used in game reverse engineering.
- **Visibility Control:** Toggle the console cursor visibility and clear the console output to enhance readability while debugging.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Flowuu/FLogger
   cd FLogger
   ```

2. **Include `flogger.hpp` in your project:**
   Make sure to include `flogger.hpp` in your source files where logging is needed.

   ```cpp
   #include "flogger.hpp"
   ```

3. **Link against necessary libraries:**
   Ensure that your project links against the necessary libraries, such as `kernel32.lib` for Windows API functions.

## Usage

### Initialization

To initialize the logger, create an instance of the `FLog` class:

```cpp
FLog logger("My Game Tool");
```

### Logging Messages

Use the following methods to log messages with different log levels:

- **Basic Log:**
  ```cpp
  logger.log("This is a basic log message related to reverse engineering.");
  ```

- **Log with Level:**
  ```cpp
  logger.log(LogLevel::info, "This is an info message about game state.");
  ```

- **Log with Title:**
  ```cpp
  logger.logWithTitle(LogLevel::warning, "Warning Title", "This is a warning message regarding game behavior.");
  ```

- **Report with Level:**
  ```cpp
  logger.report(LogLevel::error, "An error occurred: %s", errorMessage);
  ```

### Toggling Features

You can toggle timestamps and cursor visibility:

```cpp
logger.toggleTimestamp(); // Enable or disable timestamps for better tracking
logger.showCursor();      // Toggle cursor visibility during debugging
```

### Clearing the Console

To clear the console output, use:

```cpp
logger.clear();
```

### Closing the Logger

When your application is done logging, ensure to close the logger to free resources:

```cpp
logger.close();
```

## Log Levels

The `LogLevel` enum provides predefined levels to categorize log messages, aiding in organizing logs related to reverse engineering and game mechanics:

- `LogLevel::black`
- `LogLevel::blue`
- `LogLevel::green`
- `LogLevel::cyan`
- `LogLevel::red`
- `LogLevel::magenta`
- `LogLevel::orange`
- `LogLevel::lightgray`
- `LogLevel::darkgray`
- `LogLevel::lightblue`
- `LogLevel::lightgreen`
- `LogLevel::lightcyan`
- `LogLevel::lightred`
- `LogLevel::lightmagenta`
- `LogLevel::yellow`
- `LogLevel::white`

Additionally, there are alias levels for convenience:

- `LogLevel::success` (lightgreen)
- `LogLevel::info` (lightcyan)
- `LogLevel::warning` (orange)
- `LogLevel::error` (red)

## Example

Here's a simple example demonstrating how to use FLogger in a game reverse engineering context:

```cpp
#include "flogger.hpp"

int main() {
    FLog logger("Game Reverse Engineering Tool");

    logger.log("Tool started.");
    logger.log(LogLevel::info, "Analyzing game memory...");
    logger.report(LogLevel::success, "Memory analysis completed successfully!");
    
    // Toggle cursor and timestamps
    logger.showCursor();
    logger.toggleTimestamp();

    logger.log(LogLevel::warning, "Detected potential game exploit.");
    logger.log(LogLevel::error, "An error occurred: %s", "Memory access violation");

    logger.close();
    return 0;
}
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributions

Contributions are welcome! If you have suggestions or improvements, feel free to create a pull request or open an issue.
