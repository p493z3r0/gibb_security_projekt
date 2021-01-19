//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_USERCONTROLLER_H
#define MAIN_USERCONTROLLER_H

#pragma once

#include <core_controller.h>

using namespace cfx;

class UserController : public CoreController, Controller {
public:
    UserController() : CoreController() {}

    ~UserController() {}

    void handleGet(http_request message) override;
    void handlePut(http_request message) override;
    void handlePost(http_request message) override;
    void handleDelete(http_request message) override;
    void handleOptions(http_request message) override;
    void initRestOpHandlers() override;
private:
    static json::value responseNotImpl(const http::method & method);
    static json::value userNotFoundError();
    static json::value tokenResponse(std::string token);

};


#endif //MAIN_USERCONTROLLER_H
