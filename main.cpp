#include <iostream>
#include "User.h"
#include "Candidate.h"
#include "Employer.h"
#include "Jobs.h"
#include <limits>

#define CANDIDATE_FILE "../candidates.txt"
#define APPLICATIONS_FILE "../applications.txt"
#define EMPLOYER_FILE "../employers.txt"
#define JOB_FILE "../jobs.txt"
using namespace std;


void display_main_menu() {
    cout << "\n======== Job Management System ========\n";
    cout << "1. Candidate Menu\n";
    cout << "2. Employer Menu\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void candidate_menu(vector<Candidate> &candidates, vector<Jobs> &jobs, vector<Application> &all_applications) {
    int choice;
    string id, password, job_title;

    cout << "\n------ Candidate Menu ------\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Delete an account\n";
    cout << "4. Exit to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string first_name, last_name, email, phone, job_type;
        cout << "Enter First Name: ";
        getline(cin, first_name);
        cout << "Enter Last Name: ";
        getline(cin, last_name);
        cout << "Enter ID: ";
        getline(cin, id);
        cout << "Enter Password: ";
        getline(cin, password);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Job Type: ";
        getline(cin, job_type);

        Candidate new_candidate(first_name, last_name, id, password, email, " ", phone, job_type);
        candidates.push_back(new_candidate);
        new_candidate.savetofile(CANDIDATE_FILE);
        cout << "Registration successful!\n";
    } else if (choice == 2) {
        cout << "Enter ID: ";
        getline(cin, id);
        cout << "Enter Password: ";
        getline(cin, password);

        bool user_found = false;

        for (auto it = candidates.begin(); it != candidates.end(); ++it) {
            if (it->login(id, password)) {
                cout << "Welcome, " << it->get_first_name() << "!\n";
                it->candidate_menu(jobs, all_applications, candidates);
                user_found = true;
                break;
            }
        }
        if (!user_found) {
            cout << "Login failed. Please check your ID and password.\n";
        }
    } else if (choice == 3) {
        cout << "Enter ID: ";
        getline(cin, id);
        cout << "Enter Password: ";
        getline(cin, password);

        bool user_found = false;
        for (auto it = candidates.begin(); it != candidates.end(); ++it) {
            if (it->login(id, password)) {
                user_found = true;
                cout << "Account deleted successfully! " << endl;
                for (int i = 0; i < candidates.size(); ++i) {
                    if (candidates[i].get_id() == id) {
                        candidates.erase(candidates.begin() + i);
                    }
                }
                it->remove_account("candidates.txt", it->get_id());
                break;
            }
        }
        if (!user_found) {
            cout << "ID or Password are incorrect. Please check your ID and password.\n";
        }
    }
}

void employer_menu(vector<Employer> &employers, vector<Jobs> &jobs, vector<Application> &all_applications) {
    int choice;
    string id, password;

    cout << "\n------ Employer Menu ------\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        string first_name, last_name, email;
        cout << "Enter First Name: ";
        getline(cin, first_name);
        cout << "Enter Last Name: ";
        getline(cin, last_name);
        cout << "Enter ID: ";
        getline(cin, id);
        cout << "Enter Password: ";
        getline(cin, password);
        cout << "Enter Email: ";
        getline(cin, email);

        Employer new_employer(first_name, last_name, id, password, email);
        employers.push_back(new_employer);
        new_employer.savetofile(EMPLOYER_FILE);
        cout << "Registration successful!\n";
    } else if (choice == 2) {
        cout << "Enter ID: ";
        getline(cin, id);
        cout << "Enter Password: ";
        getline(cin, password);

        bool user_found = false;

        for (auto it = employers.begin(); it != employers.end(); ++it) {
            if (it->login(id, password)) {
                cout << "Welcome, " << it->get_first_name() << "!\n";
                it->employer_menu(jobs, all_applications);
                user_found = true;
                break;
            }
        }
        if (!user_found) {
            cout << "Login failed. Please check your ID and password.\n";
        }
    }
}

int main() {
    vector<Application> all_applications = Application::loadfromfile(APPLICATIONS_FILE);
    vector<Candidate> candidates = Candidate::loadfromfile(CANDIDATE_FILE);
    vector<Employer> employers = Employer::loadfromfile(EMPLOYER_FILE);
    vector<Jobs> jobs = Jobs::loadfromfile(JOB_FILE);

    int choice;
    do {
        display_main_menu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
            case 1:
                candidate_menu(candidates, jobs, all_applications);
                break;
            case 2:
                employer_menu(employers, jobs, all_applications);
                break;
            case 3:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
