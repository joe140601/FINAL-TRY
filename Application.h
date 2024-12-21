//
// Created by bensi on 16/12/2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Jobs.h"
#include "Candidate.h"

class Candidate;

class Employer;

class Application {
private:
    string candidate_first_name;
    string candidate_last_name;
    string candidate_id;
    string candidate_email;
    string candidate_phone_number;
    string resume;
    string status;
    string job_UID;
    string employer_id;

public:
    //Constructors
    Application() = default;
    Application(string &candidate_first_name, string &candidate_last_name, string &candidate_id,
                string &candidate_email,
                string &candidate_phone_number, string &resume, string &job_UID, string &employer_id, string &status);

    //Save and Load
    void savetofile(const string &filename) const;
    static vector<Application> loadfromfile(const string &filename);

    //Get funcions
    string get_candidate_id() const { return candidate_id; }
    string get_employer_id() const;
    string get_job_uid() const;

    //Set function
    void set_status(const string &new_status);

    //Display function
    void display_application() const;
};

#endif //APPLICATION_H