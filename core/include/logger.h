//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_LOGGER_H
#define MAIN_LOGGER_H

#include <string>
#include <iostream>
#include <fstream>

#pragma once

namespace cfx {
    enum LogSeverity {
        Low,
        Normal,
        High
    };

    class logger {
    public:
        void log(std::string log, LogSeverity logSeverity);
        void set_output_file(std::string path);

        static logger *get_instance();



    private:
        std::ofstream outputFile;
        static logger* instance;
        std::string filePath;

        logger();

        ~logger();
    };
}
#endif //MAIN_LOGGER_H
