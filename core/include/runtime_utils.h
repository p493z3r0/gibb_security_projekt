//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_RUNTIME_UTILS_H
#define MAIN_RUNTIME_UTILS_H

#pragma once

#include <execinfo.h>
#include <unistd.h>

namespace cfx {
    class RuntimeUtils {
    public:
        static void printStackTrace() {
            const int MAX_CALLSTACK = 100;
            void * callstack[MAX_CALLSTACK];
            int frames;

            // get void*'s for all entries on the stack...
            frames = backtrace(callstack, MAX_CALLSTACK);

            // print out all the frames to stderr...
            backtrace_symbols_fd(callstack, frames, STDERR_FILENO);
        }
    };
}
#endif //MAIN_RUNTIME_UTILS_H
