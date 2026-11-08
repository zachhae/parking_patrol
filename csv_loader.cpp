#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm> // Needed to remove quotes
#include "ticket.h"

using namespace std;

string clean_token(const string& token) {
    if (token.length() >= 2 && token.front() == '"' && token.back() == '"')
        return token.substr(1, token.length() - 2);
 
    return token;
}

double safe_stod(string str) {
    str = clean_token(str);

    if(str.empty())
        return 0.0;
    
    try {return stod(str);}
    catch (...) { return 0.0; }
}

int safe_stoi(string str) {
    str = clean_token(str);

    if(str.empty())
        return 0;

    try { return stoi(str); }
    catch (...) { return 0;}    
}


vector<ticket> load_csv(const string& filename) {
    vector<ticket> tickets;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return tickets;
        }

    string line;
    getline(file,line);


    while(getline(file, line)) {
        stringstream ss(line);
        string token;
        ticket t;

        getline(ss, token, ',');
        t.plate_number = clean_token(token);

        getline(ss, token, ',');
        t.state = clean_token(token);

        getline(ss, token, ',');
        t.vehicle_make = clean_token(token);

        getline(ss, token, ',');
        t.vehicle_style = clean_token(token);

        getline(ss, token, ',');
        t.vehicle_color = clean_token(token);

        getline(ss, token, ',');
        t.location = clean_token(token);

        getline(ss, token, ',');
        t.violation = clean_token(token);

        getline(ss, token, ',');
        t.fine = safe_stod(token);

        getline(ss, token, ',');
        t.year = safe_stoi(token);

        getline(ss, token, ',');
        t.month = safe_stoi(token);

        getline(ss, token, ',');
        t.day = safe_stoi(token);

        getline(ss, token, ',');
        t.hour = safe_stoi(token);

        getline(ss, token, ',');
        t.minute = safe_stoi(token);

        tickets.push_back(t);

        }

        file.close();
        return tickets;
    }


