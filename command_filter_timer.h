#pragma once

#include <chrono>
using namespace std::chrono_literals;
class CommandFilterTimer{
public:
    bool canSendCommand();
    void reset();
private:
    std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    constexpr static std::chrono::milliseconds padding = 500ms;
};
