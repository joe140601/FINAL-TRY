#include "User.h"

User::User() : id(""), password(""), email(""), first_name(""), last_name("") {}

User::User(string first_name, string last_name, string id, string password, string email)
        : first_name(first_name), last_name(last_name), id(id), password(password), email(email) {}

bool User::login(const string &input_id, const string &input_password) const {
    return id == input_id && password == input_password;
}
