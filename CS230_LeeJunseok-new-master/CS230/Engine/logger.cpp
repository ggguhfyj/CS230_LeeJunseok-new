/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    CS230 Engine
Author:     Junseok Lee
Created:    March 8, 2023
Updated:    March 18, 2025
*/

#include <iostream>
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point last_tick) : min_level(severity), out_stream("Trace.log") {
    SetTraceLogLevel(LOG_NONE);
    if (use_console == true) {
        out_stream.set_rdbuf(std::cout.rdbuf());
    }
    start_time = last_tick;
}

CS230::Logger::~Logger() {
    out_stream.flush();
    out_stream.close();
}

void CS230::Logger::log(CS230::Logger::Severity severity, std::string message) {
    if (severity < min_level || static_cast<int>(severity) >= 4) return;
    out_stream.precision(4);
    out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
    static const char* severity_labels[] = { "Verbose", "Debug", "Event", "Error" };
    out_stream << severity_labels[static_cast<int>(severity)] << "\t" << message << std::endl;
    return;
}

