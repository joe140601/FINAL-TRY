//
// Created by bensi on 16/12/2024.
//
#include <iostream>
#include "Application.h"
#include "Jobs.h"

#define APPLICATIONS_FILE "../applications.txt"

using namespace std;

Application::Application(string &candidate_first_name, string &candidate_last_name, string &candidate_id,
                         string &candidate_email, string &candidate_phone_number, string &resume, string &job_UID,
                         string &employer_id, string &status) {
    this->candidate_first_name = candidate_first_name;
    this->candidate_last_name = candidate_last_name;
    this->candidate_id = candidate_id;
    this->candidate_email = candidate_email;
    this->candidate_phone_number = candidate_phone_number;
    this->resume = resume;
    this->job_UID = job_UID;
    this->employer_id = employer_id;
    this->status = status;
}

void Application::savetofile(const string &filename) const {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    outfile << candidate_first_name << "," << candidate_last_name << "," << candidate_id << ","
            << candidate_email << "," << candidate_phone_number << "," << resume << ","
            << job_UID << "," << employer_id << "," << status << "\n";
    outfile.close();
}

// Load all jobs from file
vector<Application> Application::loadfromfile(const string &filename) {
    vector<Application> applications;
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file for reading.\n";
        return applications;
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string candidate_first_name, candidate_last_name, candidate_id, candidate_email, candidate_phone_number, resume, job_UID, employer_id, status;

        getline(ss, candidate_first_name, ',');
        getline(ss, candidate_last_name, ',');
        getline(ss, candidate_id, ',');
        getline(ss, candidate_email, ',');
        getline(ss, candidate_phone_number, ',');
        getline(ss, resume, ',');
        getline(ss, job_UID, ',');
        getline(ss, employer_id, ',');
        getline(ss, status, ',');

        if (!candidate_first_name.empty() && !job_UID.empty()) {
            applications.emplace_back(candidate_first_name, candidate_last_name, candidate_id, candidate_email,
                                      candidate_phone_number, resume, job_UID, employer_id, status);
        }
    }
    infile.close();
    return applications;
}

void Application::display_application() const {
    cout << "Name: " << candidate_first_name << " " << candidate_last_name << endl;
    cout << "Candidate ID : " << candidate_id << endl << "Resume:" << resume << endl << "Phone number:"
         << candidate_phone_number << endl << "Email:" << candidate_email << endl << "Status: " << status << endl;
    cout << "Job UID: " << job_UID << endl;
}

void Application::set_status(const string &new_status) {
    status = new_status;
    vector<Application> applications = Application::loadfromfile(APPLICATIONS_FILE);
    ofstream outfile(APPLICATIONS_FILE);
    if (!outfile.is_open()) {
        cout << "Error: could not open file for updating " << endl;
        return;
    }
    for (int i = 0; i < applications.size(); ++i) {
        if (applications[i].get_job_uid() == job_UID) {
            applications[i].set_status(new_status);
        }
        outfile << applications[i].candidate_first_name << "," << applications[i].candidate_last_name << ","
                << applications[i].candidate_id << "," << applications[i].candidate_email << ","
                << applications[i].candidate_phone_number
                << "," << applications[i].resume << "," << applications[i].job_UID << "," << applications[i].employer_id
                << "," << applications[i].status << endl;
    }
}

string Application::get_job_uid() const { return job_UID; }

string Application::get_employer_id() const { return employer_id; }