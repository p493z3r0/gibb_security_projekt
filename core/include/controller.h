//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_CONTROLLER_H
#define MAIN_CONTROLLER_H
#pragma once
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

namespace cfx {
    // This is the interface which the controller uses to do some basic http rest stuff

    class Controller {
    public:
        virtual void handleGet(http_request message) = 0;
        virtual void handlePost(http_request message) = 0;
        virtual void handlePut(http_request message) = 0;
        virtual void handleDelete(http_request message) = 0;
        virtual void handleOptions(http_request message) = 0;
        // Should be all Methods needed in this project
    };
}


#endif //MAIN_CONTROLLER_H
