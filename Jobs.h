//
// Created by איליי on 14/12/2024.
//
#ifndef ALLOJBSV2_JOBS_H
#define ALLOJBSV2_JOBS_H

using namespace std;

#include <string>
#include <iostream>
#include <vector>
#include "Employer.h"
#include "Application.h"

class Jobs {
protected:
    string location;
    string profession;
    string job_type;
    string jobUID;
    int experience;
    string employer_id;
    int limit;
    int app_number;

public:
    //Constructors
    Jobs();
    Jobs(string location, string profession, string job_type, string jobUID, int experience, string employer_id,
         int limit, int app_number);

    //Save and Load
    void savetofile(const string &filename) const;
    static vector<Jobs> loadfromfile(const string &filename);

    //Get function
    string get_location() const { return location; }
    string get_profession() const { return profession; }
    string get_job_type() const { return job_type; }
    string get_job_UID() const { return jobUID; }
    string get_employer_id() const { return employer_id; }
    int get_app_number() const { return app_number; }
    int get_experience() const { return experience; }
    int get_limit() const { return limit; }

    //Jobs requirements functions
    Jobs create_job(const string &employer_id) const;
    vector<Jobs> search_jobs(vector<Jobs> &all_jobs);

    //Apply counter function
    void increase_app_number() { app_number++; }

    //Set functions
    void set_location(const string &loc) { location = loc; }
    void setProfession(const string &prof) { profession = prof; }
    void set_job_type(const string &type) { job_type = type; }
    void set_job_UID(const string &uid) { jobUID = uid; }
    void set_experience(int exp) { experience = exp; }
    void set_application(const Application &app);

    //Display function
    void display_jobs() const;

    //Update functions
    void update_app_number_in_file(const string &filename, const string &job_id) const;
    void update_job(vector<Jobs> &all_jobs, const string &filename);
    void update_jobs_file(vector<Jobs> &all_jobs, const string &filename, const string &job_id);

};

#endif //ALLOJBSV2_JOBS_H
