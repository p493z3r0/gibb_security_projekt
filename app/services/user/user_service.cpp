//
// Created by Dominic Järmann on 19/01/2021.
//

#include "user_service.h"
#include <pqxx/pqxx>
#include <jwt/jwt.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

const auto SECRET = "oiwucdoqjidiochjoiwjaiodjweoqdijowqe";
using namespace jwt::params;
using namespace boost::uuids;


UserModel *user_service::create_user(UserModel &user) {
    pqxx::connection *C = new pqxx::connection("postgres://postgres:1234@localhost:5433/security");

    pqxx::work W{*C};

    const auto select_statement = "SELECT * FROM users where email = '" + W.esc(user.get_email()) + "'";

    boost::uuids::random_generator_pure gen;
    boost::uuids::uuid uuid = gen();

    user.set_uuid(boost::uuids::to_string(uuid));
    pqxx::result R{W.exec(select_statement)};
    if (R.size() > 0) {
        std::cout << "User already exists" << std::endl;
        return &user;
    }

    std::cout << "Creating user..\n";

    const auto statement = "INSERT into users(uuid, email, name, password) VALUES ('" +
                           W.esc(user.get_uuid()) + "', '" + W.esc(user.get_email()) + "', '" + W.esc(user.get_name()) +
                           "', '" + W.esc(user.get_password()) + "')";
    std::cout << statement << std::endl;
    W.exec(statement);

    std::cout << "Making changes definite ";
    W.commit();
    std::cout << "OK.\n";

    return &user;
}

UserModel *user_service::delete_user(UserModel &user) {
    return &user;
}

UserModel *user_service::update_user(UserModel &user) {
    return &user;
}

UserModel *user_service::get_user(std::string email) {


    pqxx::connection *C = new pqxx::connection("postgres://postgres:1234@localhost:5433/security");

    pqxx::work W{*C};

    const auto select_statement = "SELECT * FROM users where email = '" + W.esc(email) + "'";

    pqxx::result result{W.exec(select_statement)};

    if (result.size() == 1 && result[0].size() == 4) {
        // user found
        const auto user = new UserModel();
        pqxx::row const row = result[0];


        user->set_uuid(row[0].c_str());
        user->set_name(row[1].c_str());
        user->set_password(row[2].c_str());
        user->set_email(row[3].c_str());
        return user;

    }

    return nullptr;
}

std::string *user_service::generate_jwt(UserModel *user) {
    jwt::jwt_object obj{algorithm("HS256"), secret(SECRET), payload({{"user", user->get_email()}})};

    return new std::string(obj.signature().c_str());
}

UserModel *user_service::login(std::string email, std::string password) {
    const auto user = user_service::get_user(email);
    if (user == nullptr) {
        return nullptr;
    }

    if (user->validate_password(password)) {
        return user;
    }
    return nullptr;

}

UserModel *user_service::get_user_from_jwt(std::string jwt) {
    auto dec_obj = jwt::decode(jwt, algorithms({"HS256"}), secret(SECRET));

    const auto email = dec_obj.payload().create_json_obj().at("user");

    return user_service::get_user(email);

}
