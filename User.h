#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string id;
    string password;
    string email;
    string first_name;
    string last_name;

public:
    //Constructors
    User();
    User(string first_name, string last_name, string id, string password, string email);

    //Login function
    bool login(const string &input_id, const string &input_password) const;

    //Get functions
    string get_id() const { return id; }
    string get_password() const { return password; }
    string get_email() const { return email; }
    string get_first_name() const { return first_name; }
    string get_last_name() const { return last_name; }

    //Set functions
    void set_id(const string& new_id) { id = new_id; }
    void set_password(const string& new_password) { password = new_password; }
    void set_email(const string& new_email) { email = new_email; }
    void set_first_name(const string& new_first_name) { first_name = new_first_name; }
    void set_last_name(const string& new_last_name) { last_name = new_last_name; }

    //Destructor function
    ~User() = default;
};

#endif // USER_H