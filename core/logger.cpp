//
// Created by Dominic Järmann on 19/01/2021.
//

#include <logger.h>
#include <chrono>
#include <iostream>
#include <ostream>

namespace cfx {

    void logger::set_output_file(std::string path) {
        this->filePath = path;
    }

    void logger::log(std::string log, LogSeverity logSeverity) {
        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::string time = std::ctime(&end_time);
        time.erase(std::remove(time.begin(), time.end(), '\n'), time.end());
        this->outputFile.open(this->filePath, std::ios_base::app);
        this->outputFile << "[" << time << "]: " << log << "\n";
        this->outputFile.close();
    }

    logger::logger() {

    }

    logger* logger::instance = nullptr;

    logger::~logger() {
        this->outputFile.close();
    }

    logger *logger::get_instance() {
        if (instance == nullptr) {
            instance = new logger();
        }
        return instance;
    }


}

