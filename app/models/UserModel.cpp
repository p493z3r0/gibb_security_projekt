//
// Created by Dominic Järmann on 19/01/2021.
//

#include "UserModel.h"
#include <bcrypt.h>


UserModel *UserModel::fromJson(web::json::value value) {

    std::string password = value.as_object().at("password").as_string();

    password = bcrypt::generateHash(password, 10);

    UserModel *model = new UserModel();
    model->set_uuid(value.as_object().at("uuid").as_string());
    model->set_email(value.as_object().at("email").as_string());
    model->set_password(password);
    model->set_name(value.as_object().at("name").as_string());

    return model;
}

web::json::value UserModel::toJson() {
    auto json = web::json::value::object();
    json["uuid"] = web::json::value::string(this->get_uuid());
    json["email"] = web::json::value::string(this->get_email());
    json["password"] = web::json::value::string(this->get_password());
    json["name"] = web::json::value::string(this->get_name());

    return json;
}

bool UserModel::validate_password(std::string password) {
    return bcrypt::validatePassword(password, this->get_password());
}
