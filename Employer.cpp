//
// Created by איליי on 14/12/2024.
//
using namespace std;

#include <iostream>
#include <vector>
#include "Jobs.h"
#include "Employer.h"
#include "Application.h"


Employer::Employer(string first_name, string last_name, string id, string password, string email) : User(first_name,
                                                                                                         last_name,
                                                                                                         id,
                                                                                                         password,
                                                                                                         email) {
}

bool Employer::login(const string &input_id, const string &input_password) const {
    if (id == input_id && password == input_password) {
        return true;
    }
}

// Save to file
void Employer::savetofile(const string &filename) const {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    outfile << first_name << "," << last_name << "," << id << "," << password << "," << email << "\n";
    outfile.close();
}

// Load from file
vector<Employer> Employer::loadfromfile(const string &filename) {
    vector<Employer> employers;
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file for reading.\n";
        return employers;
    }
    string line, first_name, last_name, id, password, email;
    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, first_name, ',');
        getline(ss, last_name, ',');
        getline(ss, id, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        employers.emplace_back(first_name, last_name, id, password, email);
    }
    infile.close();
    return employers;
}

void Employer::update_jobs_file(const vector<Jobs> &all_jobs, const string &filename) {
    ofstream outfile(filename); // פותח את הקובץ במצב כתיבה מחדש
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    for (const auto &job: all_jobs) {
        outfile << job.get_job_UID() << ","
                << job.get_employer_id() << ","
                << job.get_profession() << ","
                << job.get_job_type() << ","
                << job.get_location() << ","
                << job.get_experience() << "\n";
    }
    outfile.close();
}

void Employer::view_published_jobs(vector<Jobs> &all_jobs) const {
    bool found = false;
    for (int i = 0; i < all_jobs.size(); ++i) {
        if (all_jobs[i].get_employer_id() == id) {
            all_jobs[i].display_jobs();
            found = true;
        }
    }
    if (!found) {
        cout << "You have not posted any jobs yet! " << endl;
    }
}

void Employer::manage_jobs(vector<Jobs> &all_jobs) {
    int choice = 0;
    bool run = true;
    while (run) {
        cout << "Choose an option : " << endl << "1.Update job." << endl << "2.Delete job." << endl << "3. Exit ."
             << endl;
        cin >> choice;

        switch (choice) {
            case 1 : {
                string UID;
                cout << "Enter the job UID that you want to update:" << endl;
                cin.ignore();
                getline(cin, UID);

                bool found = false;
                for (int i = 0; i < all_jobs.size(); ++i) {
                    if (all_jobs[i].get_job_UID() == UID) {
                        all_jobs[i].update_job(all_jobs, "jobs.txt");
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Job UID not found. " << endl;
                }
                break;
            }
            case 2: {
                string UID;
                cout << "Enter the job UID you want to delete:";
                cin.ignore();
                getline(cin, UID);

                bool found = false;
                for (int i = 0; i < all_jobs.size(); ++i) {
                    if (all_jobs[i].get_job_UID() == UID) {
                        all_jobs.erase(all_jobs.begin() + i);
                        found = true;
                        update_jobs_file(all_jobs, "jobs.txt");
                        cout << "Job deleted successfully" << endl;
                        break;
                    }
                    if (!found) {
                        cout << "Job UID not found." << endl;
                    }
                }
            }

            case 3:
                run = false;
                break;

        }
    }
}


void Employer::display_details() const {
    cout << "First name: " << first_name << endl;
    cout << "Last name: " << last_name << endl;
    cout << "ID: " << id << endl;
    cout << "Password: " << password << endl;
    cout << "Email: " << email << endl;

}

void Employer::employer_menu(vector<Jobs> &all_jobs, vector<Application> &all_applications) {
    int choice;
    bool run = true;
    while (run) {
        cout << "\n======= Employer Menu =======: \n";
        cout << "1) Post jobs " << endl;
        cout << "2) View Published jobs " << endl;
        cout << "3) Manage jobs " << endl;
        cout << "4) Search Jobs" << endl;
        cout << "5) View applications for a job." << endl;
        cout << "6) Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Jobs newJob = Jobs().create_job(id);
                all_jobs.push_back(newJob);
                newJob.savetofile("jobs.txt");
                cout << "Job posted successfully!";
                break;
            }
            case 2: {
                view_published_jobs(all_jobs);
                break;
            }
            case 3: {
                manage_jobs(all_jobs);
                break;
            }

            case 4: {

                Jobs job_manager;
                vector<Jobs> found_result = job_manager.search_jobs(all_jobs);
                if (found_result.empty()) {
                    cout << "No jobs match the given criteria." << endl;
                    break;
                } else {
                    cout << "Matching jobs:" << endl;
                    for (int i = 0; i < found_result.size(); ++i) {
                        found_result[i].display_jobs();
                        cout << "----------------------" << endl;
                    }
                }
                break;
            }
            case 5: {
                view_applications(all_applications);
                string uid;
                cout << "Enter job UID to view its applications: ";
                cin.ignore();
                getline(cin, uid);

                bool found = false;
                for (int i = 0; i < all_applications.size(); i++) {
                    if (all_applications[i].get_job_uid() == uid) {
                        found = true;
                        all_applications[i].display_application();

                        int choice;
                        cout << "Do you want to answer to a candidate's application? " << endl;
                        cout << "1. Yes " << endl;
                        cout << "2. No" << endl;
                        cin >> choice;

                        if (choice == 1) {
                            cout << "Enter the Candidate ID to respond: ";
                            string candidateID;
                            cin >> candidateID;
                            if (all_applications[i].get_candidate_id() == candidateID) {
                                cout << "Enter status (Accept/Reject/Skip): ";
                                string status;
                                cin >> status;

                                all_applications[i].set_status(status);
                                cout << "Response successfully sent to the candidate." << endl;
                                break;
                            }
                        }
                        if (!found) {
                            cout << "Job UID not found." << endl;
                        }
                    }
                }
                break;
            }
            case 6 : {
                run = false;
                cout << "Goodbye!" << endl;
                break;
            }

            default: {
                cout << "Invalid choice. try again. \n";

            }

        }

    }
}

void Employer::view_applications(vector<Application> &all_applications) {
    for (int i = 0; i < all_applications.size(); i++) {
        if (all_applications[i].get_employer_id() == id) {
            all_applications[i].display_application();
            cout << endl;
        }
    }
}