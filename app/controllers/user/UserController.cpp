//
// Created by Dominic Järmann on 19/01/2021.
//

#include "UserController.h"
#include "../../models/UserModel.h"
#include "../../services/user/user_service.h"
#include <istream>

using namespace web;
using namespace http;

using namespace cfx;

void UserController::initRestOpHandlers() {

    _listener.support(methods::GET, std::bind(&UserController::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&UserController::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&UserController::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&UserController::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::OPTIONS, std::bind(&UserController::handleOptions, this, std::placeholders::_1));
}

json::value UserController::responseNotImpl(const http::method &method) {
    auto response = json::value::object();
    response["serviceName"] = json::value::string("C++ Mircroservice Sample");
    response["http_method"] = json::value::string(method);
    return response;
}

json::value UserController::userNotFoundError() {
    auto response = json::value::object();
    response["error"] = json::value::string("User with supplied id could not be found");
    return response;
}

json::value UserController::tokenResponse(std::string token) {
    auto response = json::value::object();
    response["token"] = json::value::string(token);
    return response;
}


void UserController::handleOptions(http_request message) {
    std::cout << "handle options" << std::endl;
    http_response response(status_codes::OK);
    response.headers().add(U("access-control-allow-origin"), U("http://localhost:4200"));
    response.headers().add(U("Access-Control-Allow-Credentials"), U("true"));
    response.headers().add(U("Access-Control-Allow-Methods"), U("GET, HEAD, OPTIONS, POST, PUT"));
    response.headers().add(U("Access-Control-Allow-Headers"), U("Origin, X-Requested-With, content-type, Accept, Authorization"));

    message.reply(response);
}

void add_cors_header(http_response* response){
    response->headers().add(U("Access-Control-Allow-Origin"), U("*"));
}

void UserController::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "find" && path.size() == 2) {
            const auto user = user_service::get_user(path[1]);
            if (user) {
                message.reply(status_codes::OK, user->toJson());
            } else {
                message.reply(status_codes::NotFound, userNotFoundError());
            }
        } else {
            if (path[0] == "me") {
                const auto auth_header = message.headers().find("Authorization");
                if (!auth_header->second.empty()) {
                    std::string delimiter = " ";
                    auto header_str = auth_header->second;


                    auto jwt_str = header_str;

                    jwt_str.erase(0, jwt_str.find(delimiter) + delimiter.length());


                    std::cout << jwt_str << std::endl;
                    auto user = user_service::get_user_from_jwt(jwt_str);
                    if (user == nullptr) {
                        message.reply(status_codes::Unauthorized, userNotFoundError());
                        return;
                    }
                    message.reply(status_codes::OK, user->toJson());


                } else {
                    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));

                }

                message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
            }
        }

    } else {
        message.reply(status_codes::NotImplemented, responseNotImpl(methods::GET)
        );
    }
}

void UserController::handlePost(http_request message) {

    std::cout << "handle_post" << std::endl;
    auto user = UserModel::fromJson(message.content_ready().get().extract_json(true).get());

    user_service::create_user(*user);

    http_response response(status_codes::Created);
    add_cors_header(&response);
    response.set_body(user->toJson());
    message.reply(response);
}

void UserController::handleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void UserController::handlePut(http_request message) {
    auto path = requestPath(message);
    auto json = message.content_ready().get().extract_json(true).get();

    if (path.empty()) {
        message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
    }

    if (path[0] == "login") {
        const auto email = json.as_object().at("email").as_string();
        const auto password = json.as_object().at("password").as_string();

        const auto user = user_service::login(email, password);
        if (user == nullptr) {
            message.reply(status_codes::Unauthorized, userNotFoundError());
            return;
        }
        message.reply(status_codes::OK, tokenResponse(*user_service::generate_jwt(user)));
        return;
    }
}





