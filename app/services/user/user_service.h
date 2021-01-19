//
// Created by Dominic Järmann on 19/01/2021.
//

#ifndef MAIN_USER_SERVICE_H
#define MAIN_USER_SERVICE_H


#include "../../models/UserModel.h"

class user_service {
public:
    static UserModel *create_user(UserModel &user);

    static UserModel *delete_user(UserModel &user);

    static UserModel *update_user(UserModel &user);

    static UserModel *get_user(std::string email);

    static UserModel *login(std::string email, std::string password);

    static std::string *generate_jwt(UserModel *user);

    static UserModel *get_user_from_jwt(std::string jwt);


private:

};


#endif //MAIN_USER_SERVICE_H
