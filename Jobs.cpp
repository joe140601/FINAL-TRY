//
// Created by איליי on 14/12/2024.
//

#include "Jobs.h"
#include <vector>

Jobs::Jobs() {
    this->location = "";
    this->profession = "";
    this->job_type = "";
    this->jobUID = "";
    this->experience = 0;
    this->employer_id = "";
    this->limit = -1;
    this->app_number = 0;
}

Jobs::Jobs(string location, string profession, string job_type, string jobUID, int experience, string employer_id,
           int limit, int app_number) {
    this->location = location;
    this->profession = profession;
    this->job_type = job_type;
    this->jobUID = jobUID;
    this->experience = experience;
    this->employer_id = employer_id;
    this->app_number = app_number;
    this->limit = limit;

}

// Save job to file
void Jobs::savetofile(const string &filename) const {
    ofstream outfile(filename, ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }
    outfile << location << ","
            << profession << ","
            << job_type << ","
            << jobUID << ","
            << experience << ","
            << employer_id << ","
            << limit << ","
            << app_number << endl;
    outfile.close();
}

// Load all jobs from file
vector<Jobs> Jobs::loadfromfile(const string &filename) {
    vector<Jobs> jobs;
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error: Could not open file for reading." << endl;
        return jobs;
    }

    string line, location, profession, job_type, jobUID, employerID;
    int experience, limit, app_number;
    while (getline(infile, line)) {
        stringstream ss(line);
        getline(ss, location, ',');
        getline(ss, profession, ',');
        getline(ss, job_type, ',');
        getline(ss, jobUID, ',');
        ss >> experience;
        ss.ignore(1);
        getline(ss, employerID, ',');
        ss >> limit;
        ss.ignore(1);
        ss >> app_number;
        ss.ignore(1);

        if (!location.empty() && !profession.empty() && !jobUID.empty()) {
            jobs.emplace_back(location, profession, job_type, jobUID, experience, employerID, limit, app_number);
        }
    }
    infile.close();
    return jobs;
}

void Jobs::update_jobs_file(vector<Jobs> &all_jobs, const string &filename, const string &job_id) {

    vector<Jobs> jobs = Jobs::loadfromfile(filename);

    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error: Could not open file for updating.\n";
        return;
    }

    for (int i = 0; i < jobs.size(); ++i) {
        if (jobs[i].get_job_UID() == job_id) {
            jobs[i] = *this;
            all_jobs[i] = jobs[i];
        }
        outfile << jobs[i].get_location() << ","
                << jobs[i].get_profession() << ","
                << jobs[i].get_job_type() << ","
                << jobs[i].get_job_UID() << ","
                << jobs[i].get_experience() << ","
                << jobs[i].get_employer_id() << ","
                << jobs[i].get_limit() << ","
                << jobs[i].get_app_number() << "\n";
    }

    outfile.close();
}

void Jobs::display_jobs() const {
    cout << "------ Job Details------:\n";
    cout << "Location: " << location << "\n"
         << "Profession: " << profession << "\n"
         << "Job Type: " << job_type << "\n"
         << "Job UID: " << jobUID << "\n"
         << "Experience: " << experience << "\n";
}

void Jobs::update_job(vector<Jobs> &all_jobs, const string &filename) {
    int choice = 0;
    bool run = true;
    while (run) {
        cout << "What do tou want to update?:" << endl;
        cout << "1. Job location :" << endl;
        cout << "2. Job profession (job title):" << endl;
        cout << "3. Job type (full time / part time):" << endl;
        cout << "4. Required experience:" << endl;
        cout << "5. Change limit: " << endl;
        cout << "6. Exit." << endl;
        cin >> choice;
        switch (choice) {
            case 1: {
                string new_location;
                cout << "Enter the new location:" << endl;
                cin.ignore();
                getline(cin, new_location);
                location = new_location;
                break;
            }
            case 2: {
                string new_profession;
                cout << "Enter the new profession:" << endl;
                cin.ignore();
                getline(cin, new_profession);
                profession = new_profession;
                break;
            }
            case 3: {
                string new_job_type;
                cout << "Enter the new job-type (full time / part time) :" << endl;
                cin.ignore();
                getline(cin, new_job_type);
                job_type = new_job_type;
                break;
            }
            case 4: {
                int new_experience;
                cout << "Enter the new required experience (in years):" << endl;
                cin >> new_experience;
                experience = new_experience;
                break;
            }
            case 5: {
                int new_limit;
                cout << "Enter the new limit: ";
                cin >> new_limit;
                limit = new_limit;
                break;
            }

            case 6 : {
                run = false;

                cout << "Update successfully completed!" << endl;
                break;
            }
            default:
                cout << "Invalid choice." << endl;

        }
        update_jobs_file(all_jobs, filename, jobUID);
    }
}

vector<Jobs> Jobs::search_jobs(vector<Jobs> &all_jobs) {
    string filter_location, filter_job_type, filter_profession;
    int filter_experience;
    bool use_location = false, use_job_type = false, use_experience = false, use_profession = false;
    cout << "By which criteria do you want to search a job?" << endl;
    cout << endl;
    int choice;
    bool run = true;
    while (choice != 5) {
        cout << "Choose an option:" << endl;
        cout << "1. By location." << endl;
        cout << "2. By job type (full-time/part-time)." << endl;
        cout << "3. Required experience ." << endl;
        cout << "4. Profession." << endl;
        cout << "5. Search." << endl;
        cin >> choice;
        switch (choice) {

            case 1: {
                cout << "Enter a location:" << endl;
                cin.ignore();
                getline(cin, filter_location);
                use_location = true;
                break;
            }

            case 2: {
                cout << "Enter the job-type (full time / part time):" << endl;
                cin.ignore();
                getline(cin, filter_job_type);
                use_job_type = true;
                break;
            }
            case 3: {
                cout << "Enter your experience (in years):" << endl;
                cin >> filter_experience;
                use_experience = true;
                break;
            }
            case 4: {
                cout << "Enter your profession:" << endl;
                cin.ignore();
                getline(cin, filter_profession);
                use_profession = true;
                break;
            }
            case 5: {
                run = false;
                break;
            }
            default: {
                cout << "Invalid choice! try again ";
            }
        }

    }
    vector<Jobs> results;
    for (int i = 0; i < all_jobs.size(); ++i) {
        Jobs job1 = all_jobs[i];
        bool match = true;
        if (use_location && job1.get_location() != filter_location)
            match = false;
        if (use_job_type && job1.get_job_type() != filter_job_type)
            match = false;
        if (use_experience && job1.get_experience() != filter_experience)
            match = false;
        if (use_profession && job1.get_profession() != filter_profession)
            match = false;
        if (match)
            results.push_back(job1);
    }
    return results;

}

Jobs Jobs::create_job(const string &employer_id1) const {
    string profession1, location1, job_type1, jobUID1;
    int experience1, limit;
    cout << "Enter the location: " << endl;
    cin.ignore();
    getline(cin, location1);
    cout << "Enter the profession:" << endl;
    getline(cin, profession1);
    cout << "Enter the job type:" << endl;
    getline(cin, job_type1);
    cout << " Enter jobUID: " << endl;
    getline(cin, jobUID1);
    cout << " Enter required experience (in years): " << endl;
    cin >> experience1;
    cout << "Enter number to limit the applications (type: -1 for no limit): " << endl;
    cin >> limit;

    return Jobs(location1, profession1, job_type1, jobUID1, experience1, employer_id1, limit, 0);
}