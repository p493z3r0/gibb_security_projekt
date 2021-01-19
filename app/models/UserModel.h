//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_USERMODEL_H
#define MAIN_USERMODEL_H


#include <string>
#include <cpprest/json.h>

class UserModel {
private:
    std::string uuid;
    std::string email;
    std::string password;
    std::string name;

public:
    static UserModel *fromJson(web::json::value value);


    void set_uuid(std::string uuid) { this->uuid = uuid; }

    void set_email(std::string email) { this->email = email; }

    void set_password(std::string password) { this->password = password; }

    void set_name(std::string name) { this->name = name; }

    std::string get_name() { return this->name; }

    std::string get_password() { return this->password; }

    std::string get_email() { return this->email; }

    std::string get_uuid() { return this->uuid; }

    web::json::value toJson();

    bool validate_password(std::string password);

};


#endif //MAIN_USERMODEL_H
