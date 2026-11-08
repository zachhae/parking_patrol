#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "ticket.h"
#include "csv_loader.h"

using namespace std;

void display_tickets(const vector<ticket>& tickets, int limit = 15) {
    cout << "\nShowing top " << limit << " results:\n";
    
    
    cout << left 
         << setw(12) << "Plate" 
         << setw(8)  << "State" 
         << setw(15) << "Make" 
         << setw(35) << "Violation" 
         << setw(10) << "Fine ($)" << endl;
         
   
    cout << string(80, '-') << endl;


    int count = 0;
    for (const auto& t : tickets) {
        if (count >= limit) break; 
        
        cout << left 
             << setw(12) << t.plate_number
             << setw(8)  << t.state
             << setw(15) << t.vehicle_make
             << setw(35) << t.violation.substr(0, 33) // Truncate super long violations
             << setw(10) << t.fine << endl;
             
        count++;
    }
    cout << endl;
}
    


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


    int main() {
    cout << "Loading parking data...\n";
    
    // Load the CSV using your inline function
    vector<ticket> tickets = load_csv("parking_citations_expanded.csv"); 
    
    if (tickets.empty()) {
        cout << "Failed to load data. Check the file name and path.\n";
        return 1;
    }
    
    cout << "Successfully loaded " << tickets.size() << " tickets.\n";

    // Test the display function directly
    display_tickets(tickets);

    return 0;
}

