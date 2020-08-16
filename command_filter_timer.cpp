#include "command_filter_timer.h"

bool CommandFilterTimer::canSendCommand(){
    auto oldTime = currentTime;
    auto newCurrentTime = std::chrono::system_clock::now();

    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(newCurrentTime-oldTime);

    if(timeDiff > padding){
        return true;
    }

    return false;
}

void CommandFilterTimer::reset(){
    currentTime = std::chrono::system_clock::now();
}
