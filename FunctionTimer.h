//
//  FunctionTimer.hpp
//  CppSandbox
//
//  Created by Admin on 28.07.2021.
//

#pragma once

#include <chrono>
#include <iostream>

#define CALL_AND_CAPTURE_TIME(x)                                                                                                           \
    {                                                                                                                                      \
        ScopedTimer timer;                                                                                                         \
        x;                                                                                                                                 \
    }

struct ScopedTimer {
    std::chrono::time_point<std::chrono::high_resolution_clock> mStartTimePoint;

    ScopedTimer() {
        mStartTimePoint = std::chrono::high_resolution_clock::now();
    }

    ~ScopedTimer() {
        stop();
    }

    void stop() const {
        auto stopTimePoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::nanoseconds>(mStartTimePoint).time_since_epoch().count();
        auto stop = std::chrono::time_point_cast<std::chrono::nanoseconds>(stopTimePoint).time_since_epoch().count();

        auto duration = stop - start;
        auto ns = duration;
        std::cout << ns << " nanoseconds" << std::endl;
        std::cout << ns / 1e3 << " microseconds" << std::endl;
        std::cout << ns / 1e6 << " miliseconds" << std::endl;
    }
};

