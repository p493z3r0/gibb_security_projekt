//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_USER_SERVICE_H
#define MAIN_USER_SERVICE_H


#include "../../models/user_model.h"

class user_service {
public:
    static user_model *create_user(user_model &user);

    static user_model *delete_user(user_model &user);

    static user_model *update_user(user_model &user);

    static user_model *get_user(std::string email);

    static user_model *login(std::string email, std::string password);

    static std::string *generate_jwt(user_model *user);

    static user_model *get_user_from_jwt(std::string jwt);


private:

};


#endif //MAIN_USER_SERVICE_H
