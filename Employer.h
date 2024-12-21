//
// Created by איליי on 14/12/2024.
//

#ifndef ALLOJBSV2_EMPLOYER_H
#define ALLOJBSV2_EMPLOYER_H

#include "User.h"
#include "Jobs.h"
#include <string>
#include <vector>
#include "Application.h"
#include <map>

class Jobs;

class Application;

class Employer : public User {
private:

public:
    //Constructors
    Employer();
    Employer(string first_name, string last_name, string id, string password, string email);

    //Login function
    bool login(const string &input_id, const string &input_password) const;

    //Save and Load
    void savetofile(const string &filename) const;
    static vector<Employer> loadfromfile(const string &filename);

    //Get function
    string get_id() const;

    //Employer requirements functions
    void manage_jobs(vector<Jobs> &all_jobs);
    void update_jobs_file(const vector<Jobs> &all_jobs, const string &filename);

    //View functions
    void view_published_jobs(vector<Jobs> &all_jobs) const;
    void view_applications(vector<Application> &all_applications);

    //Display functions
    void display_details() const;
    void employer_menu(vector<Jobs> &all_jobs, vector<Application> &all_applications);
};

#endif //ALLOJBSV2_EMPLOYER_H
