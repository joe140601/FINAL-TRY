//
// Created by איליי on 14/12/2024.
//
#ifndef ALLOJBSV2_CANDIDATE_H
#define ALLOJBSV2_CANDIDATE_H

#include <algorithm>
#include "User.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Jobs.h"

class Application;

class Jobs;

class Candidate : public User {
private:
    string resume;
    string phone_number;
    string job_type;
    vector<string> favorites;

public:
    //Constructors
    Candidate();
    Candidate(string first_name, string last_name, string id, string password, string email, string resume,
              string phone_number, string job_type);

    //Login function
    bool login(const string &input_id, const string &input_password) const;

    //Save and Load
    void savetofile(const string &filename) const;
    static vector<Candidate> loadfromfile(const string &filename);

    //Get functions
    string get_resume() const { return resume; }
    string get_job_type() const { return job_type; }

    //Set functions
    void set_phone_number(const string &phone) { phone_number = phone; }
    void set_job_type(const string &job) { job_type = job; }

    //Candidate requirements functions
    void remove_account(const string &filename, const string &user_id);
    void submit_resume(const string &resume_content);
    void update_profile_in_file(const string &filename) const;

    //View functions
    void view_jobs_and_apply(vector<Jobs> &jobs, vector<Application> &all_applications);
    void view_applications(const vector<Application> &all_applications);

    //Display functions
    void display_details() const;
    void edit_profile(Candidate &candidate);
    void candidate_menu(vector<Jobs> &all_jobs, vector<Application> &all_applications,vector<Candidate> &all_candidates);

};

#endif //ALLOJBSV2_CANDIDATE_H
