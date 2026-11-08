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


vector<ticket> load_csv(const string& filename) {
    vector<ticket> tickets;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return tickets;
        }

    string line;

    // We skip first header line
    getline(file,line);

    while(getline(file, line)) {
        stringstream ss(line);
        string token;
        ticket t;

       


        }
    }







}
