//
// Created by Dominic Järmann on 19/01/2021.
//

#include "user_service.h"
#include <pqxx/pqxx>
#include <jwt/jwt.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <logger.h>
const auto SECRET = "oiwucdoqjidiochjoiwjaiodjweoqdijowqe";
using namespace jwt::params;
using namespace boost::uuids;
using namespace cfx;

user_model *user_service::create_user(user_model &user) {
    pqxx::connection *C = new pqxx::connection("postgres://postgres:1234@localhost:5433/security");

    pqxx::work W{*C};

    const auto select_statement = "SELECT * FROM users where email = '" + W.esc(user.get_email()) + "'";

    boost::uuids::random_generator_pure gen;
    boost::uuids::uuid uuid = gen();

    user.set_uuid(boost::uuids::to_string(uuid));
    pqxx::result R{W.exec(select_statement)};
    if (R.size() > 0) {
        logger::get_instance()->log("Tried to recreate user with mail:  :" + user.get_email(), LogSeverity::Normal);
        return &user;
    }

    std::cout << "Creating user..\n";

    const auto statement = "INSERT into users(uuid, email, name, password) VALUES ('" +
                           W.esc(user.get_uuid()) + "', '" + W.esc(user.get_email()) + "', '" + W.esc(user.get_name()) +
                           "', '" + W.esc(user.get_password()) + "')";
    std::cout << statement << std::endl;
    W.exec(statement);

    logger::get_instance()->log("Created with Email :" + user.get_email(), LogSeverity::Normal);
    W.commit();

    return &user;
}

user_model *user_service::delete_user(user_model &user) {
    return &user;
}

user_model *user_service::update_user(user_model &user) {
    return &user;
}

user_model *user_service::get_user(std::string email) {


    logger::get_instance()->log("Get User:" + email, LogSeverity::Normal);
    pqxx::connection *C = new pqxx::connection("postgres://postgres:1234@localhost:5433/security");

    pqxx::work W{*C};

    const auto select_statement = "SELECT * FROM users where email = '" + W.esc(email) + "'";

    pqxx::result result{W.exec(select_statement)};

    if (result.size() == 1 && result[0].size() == 4) {
        // user found
        const auto user = new user_model();
        pqxx::row const row = result[0];


        user->set_uuid(row[0].c_str());
        user->set_name(row[1].c_str());
        user->set_password(row[2].c_str());
        user->set_email(row[3].c_str());
        return user;

    }

    return nullptr;
}

std::string *user_service::generate_jwt(user_model *user) {
    jwt::jwt_object obj{algorithm("HS256"), secret(SECRET), payload({{"user", user->get_email()}})};
    logger::get_instance()->log("Generate JWT for user:  :" + user->get_email(), LogSeverity::Normal);

    return new std::string(obj.signature().c_str());
}

user_model *user_service::login(std::string email, std::string password) {
    const auto user = user_service::get_user(email);
    if (user == nullptr) {
        logger::get_instance()->log("Failed login attempt with email  :" + user->get_email(), LogSeverity::Normal);
        return nullptr;
    }

    if (user->validate_password(password)) {
        logger::get_instance()->log("successful login attempt with email  :" + user->get_email(), LogSeverity::Normal);

        return user;
    }

    logger::get_instance()->log("Failed login attempt with email  :" + user->get_email(), LogSeverity::Normal);

    return nullptr;

}

user_model *user_service::get_user_from_jwt(std::string jwt) {
    auto dec_obj = jwt::decode(jwt, algorithms({"HS256"}), secret(SECRET));

    const auto email = dec_obj.payload().create_json_obj().at("user");
    // logger::get_instance()->log(&"Got email from JWT :" [ email], LogSeverity::Normal);

    return user_service::get_user(email);

}
