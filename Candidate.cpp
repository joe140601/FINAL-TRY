//
// Created by איליי on 14/12/2024.
//
using namespace std;

#include "Candidate.h"
#include "Jobs.h"
#include "User.h"
#include "Application.h"

Candidate::Candidate() : User() {
    this->resume = nullptr;
    this->job_type = nullptr;
    this->phone_number = nullptr;
}

void Candidate::update_profile_in_file(const string &filename) const {
    vector<Candidate> candidates = Candidate::loadfromfile(filename);
    ofstream outfile(filename);

    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for updating.\n";
        return;
    }

    for (auto &candidate : candidates) {
        if (candidate.get_id() == id) {
            candidate = *this;
        }

        outfile << candidate.get_first_name() << ","
                << candidate.get_last_name() << ","
                << candidate.get_id() << ","
                << candidate.get_password() << ","
                << candidate.get_email() << ","
                << candidate.get_resume() << ","
                << candidate.phone_number << ","
                << candidate.job_type << ",";

        // שמירת המשרות המועדפות
        for (size_t i = 0; i < candidate.favorites.size(); i++) {
            outfile << candidate.favorites[i];
            if (i != candidate.favorites.size() - 1) {
                outfile << "|";
            }
        }
        outfile << "\n";
    }

    outfile.close();
    cout << "Profile updated successfully in the file.\n";
}

Candidate::Candidate(string first_name1, string last_name1, string id1, string password1, string email1, string resume1,
                     string phone_number1, string job_type1) : User(first_name1, last_name1, id1, password1, email1) {
    this->resume = resume1;
    this->phone_number = phone_number1;
    this->job_type = job_type1;
}

bool Candidate::login(const string &input_id, const string &input_password) const {
    return (id == input_id && password == input_password);
}

void Candidate::savetofile(const string &filename) const {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    outfile << first_name << "," << last_name << "," << id << "," << password << "," << email << "," << resume << ","
            << phone_number << "," << job_type << ",";
    for (size_t i = 0; i < favorites.size(); i++) {
        outfile << favorites[i];
        if (i != favorites.size() - 1) {
            outfile << "|";
        }
    }

    outfile << "\n";
    outfile.close();
}

// Load from file
vector<Candidate> Candidate::loadfromfile(const string &filename) {
    vector<Candidate> candidates;
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file for reading.\n";
        return candidates;
    }

    string line, first_name, last_name, id, password, email, resume, phone_number, job_type, fav_line;
    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, first_name, ',');
        getline(ss, last_name, ',');
        getline(ss, id, ',');
        getline(ss, password, ',');
        getline(ss, email, ',');
        getline(ss, resume, ',');
        getline(ss, phone_number, ',');
        getline(ss, job_type, ',');
        getline(ss, fav_line); // קריאת המשרות המועדפות

        Candidate candidate(first_name, last_name, id, password, email, resume, phone_number, job_type);

        // פיצול המשרות המועדפות והכנסתן לווקטור
        stringstream fav_stream(fav_line);
        string fav;
        while (getline(fav_stream, fav, '|')) {
            candidate.favorites.push_back(fav);
        }

        candidates.push_back(candidate);
    }

    infile.close();
    return candidates;
}

void Candidate::display_details() const {
    cout << "Candidate Details:\n";
    cout << "ID: " << id << "\n"
         << "First Name: " << first_name << "\n"
         << "Last Name: " << last_name << "\n"
         << "Email: " << email << "\n"
         << "Phone Number: " << phone_number << "\n"
         << "Job Type: " << job_type << "\n"
         << "Resume: " << resume << "\n";
}

void Candidate::view_jobs_and_apply(vector<Jobs> &jobs, vector<Application> &all_applications) {
    string job_id;
    cout << "Enter the Job UID you want to apply for: ";
    cin.ignore();
    getline(cin, job_id);

    bool job_found = false;
    for (int i = 0; i < jobs.size(); i++) {
        if (jobs[i].get_job_UID() == job_id) {
            job_found = true;
            if (jobs[i].get_limit() != -1 && jobs[i].get_app_number() == jobs[i].get_limit()) {
                cout << "There are too much application for this job! " << endl;
                return;
            }
            string employer_id = jobs[i].get_employer_id();
            string status = "Pending...";
            Application app(first_name, last_name, id, email, phone_number, resume, job_id, employer_id, status);
            all_applications.push_back(app);
            app.savetofile("applications.txt");
            cout << "Application submitted successfully!\n";
            jobs[i].increase_app_number();
            jobs[i].update_jobs_file(jobs, "jobs.txt", job_id);
            return;
        }
    }
    if (!job_found) {
        cout << "Job ID not found.\n";
    }
}

void Candidate::view_applications(const vector<Application> &all_applications) {
    cout << "\nYour Applications:\n";
    bool has_applications = false;

    for (int i = 0; i < all_applications.size(); i++) {
        if (all_applications[i].get_candidate_id() == id) {
            all_applications[i].display_application();
            has_applications = true;
        }
    }

    if (!has_applications) {
        cout << "You have not submitted any applications yet.\n";
    }
}

void Candidate::submit_resume(const std::string &resume_content) {
    resume = resume_content;
    cout << "Resume updated successfully " << endl;
    update_profile_in_file("candidates.txt");
}
void Candidate::remove_account(const string &filename, const string &user_id) {
    vector<Candidate> candidates = loadfromfile(filename);
    ofstream outfile(filename, ios::trunc);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    for (const auto &candidate : candidates) {
        if (candidate.get_id() != user_id) {
            candidate.savetofile(filename);
        }
    }
    outfile.close();
    cout << "Account with ID '" << user_id << "' has been removed.\n";
}
void Candidate::edit_profile(Candidate &candidate) {
    int choice;
    bool run = true;
    while (run) {
        cout << "Manage profile menu: " << endl;
        cout << "1. Change my first name: " << endl;
        cout << "2. Change my last name: " << endl;
        cout << "3. Change my email address: " << endl;
        cout << "4. Change my phone number: " << endl;
        cout << "5. Display my profile's details: " << endl;
        cout << "6.Exit." << endl;
        cout << "Please choose an option:" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                string new_first_name;
                cout << "Enter the new first name :";
                getline(cin, new_first_name);
                candidate.set_first_name(new_first_name);
                this->first_name = new_first_name;
                cout << "First name updated successfully!\n";
                break;
            }
            case 2: {
                string new_last_name;
                cout << "Enter the new last name : ";
                getline(cin, new_last_name);
                candidate.set_last_name(new_last_name);
                this->last_name = new_last_name;
                cout << "Last name updated successfully!";
                break;
            }
            case 3: {
                string new_email;
                cout << "Enter the new email:";
                getline(cin, new_email);
                candidate.set_email(new_email);
                this->email = new_email;
                cout << "Email updated successfully!";
                break;
            }
            case 4: {
                string new_phone_number;
                cout << "Enter the new phone number:";
                getline(cin, new_phone_number);
                candidate.set_phone_number(new_phone_number);
                this->phone_number = new_phone_number;
                cout << "Phone number updated successfully!";
                break;
            }
            case 5: {
                display_details();
                break;
            }
            case 6:
                cout << "Goodbye!" << endl;
                run = false;
                break;
            default:
                cout << "invalid option , please try again.";
        }
        update_profile_in_file("candidates.txt");
    }
}

void Candidate::candidate_menu(vector<Jobs> &all_jobs, vector<Application> &all_applications, vector<Candidate> &all_candidates) {
    int choice;
    bool run = true;
    while (run) {
        cout << "\n======= Candidate Menu =======: \n";
        cout << "1) Search jobs."<< endl;
        cout << "2) Edit profile." << endl;
        cout << "3) View favorites." << endl;
        cout << "4) View application history." << endl;
        cout << "5) View profile." << endl;
        cout << "6) Submit resume." << endl;
        cout << "7) View resume." << endl;
        cout << "8) Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
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
                int num;
                cout << "Do you want to apply for a job / mark as favorite / return to the menu ( 1-Apply | 2-Mark asFavorite | 3- return to the menu ): ";
                cin >> num;
                if (num == 1) {
                    view_jobs_and_apply(all_jobs, all_applications);
                } else if (num == 2) {
                    string temp_uid;
                    cout << "Enter Job UID that you want to mark as favorite: ";
                    cin.ignore();
                    getline(cin, temp_uid);
                    bool temp = false;
                    for (int i = 0; i < all_jobs.size(); ++i) {
                        if (temp_uid == all_jobs[i].get_job_UID()) {
                            favorites.push_back(temp_uid);
                            update_profile_in_file("candidates.txt");
                            temp = true;
                            cout << "The job added to your favorites! " << endl;
                            break;
                        }
                    }
                    if (!temp) {
                        cout << "There is no job with that UID! " << endl;
                    }
                } else if (num == 3) {
                    break;
                }
                break;
            }
            case 2: {
                edit_profile(*this);
                break;
            }
            case 3: {
                if (favorites.empty()) {
                    cout << "No job in your favorite list " << endl;
                    break;
                }
                bool job_found = false;
                for (int i = 0; i < all_jobs.size(); ++i) {
                    for (int j = 0; j < favorites.size(); ++j) {
                        if (all_jobs[i].get_job_UID() == favorites[j]) {
                            all_jobs[i].display_jobs();
                            job_found = true;
                        }
                    }
                }
                if (!job_found) {
                    cout << "No matching jobs found in your favorite list" << endl;
                }
                break;
            }
            case 4: {
                view_applications(all_applications);
                break;
            }
            case 5: {
                display_details();
                break;
            }
            case 6: {
                string resume_content;
                cout << "Enter your resume content: ";
                cin.ignore();
                getline(cin, resume_content);
                submit_resume(resume_content);
                cout << "Resume submitted successfully.\n";
                break;
            }
            case 7: {
                cout << "Your Resume:\n" << get_resume() << "\n";
                break;
            }

            case 8: {
                run = false;
                break;
            }
            default: {
                cout << "Invalid choice. try again. \n";
            }
        }
    }

}