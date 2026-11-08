#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "ticket.h"
#include "csv_loader.h"
#include "quick_sort.h"

using namespace std;

void display_tickets(const vector<ticket>& tickets, int limit = 15) {
    cout << "\nShowing top " << limit << " results:\n";
    
    
    cout << left 
         << setw(12) << "Plate" 
         << setw(8)  << "State" 
         << setw(15) << "Make" 
         << setw(35) << "Violation" 
         << setw(10) << "Fine ($)"
         << setw(15) << "Color"
         << setw(10) << "Year"
         << setw(5) << "Month" << endl;
         
   
    cout << string(110, '-') << endl;


    int count = 0;
    for (const auto& t : tickets) {
        if (count >= limit) break; 
        
        cout << left 
             << setw(12) << t.plate_number
             << setw(8)  << t.state
             << setw(15) << t.vehicle_make
             << setw(35) << t.violation.substr(0, 33) // Truncate super long violations
             << setw(10) << t.fine
             << setw(15) << t.vehicle_color
             << setw(10) << t.year
             << setw(5) << t.month << endl;
             
        count++;
    }
    cout << endl;
}
    


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main() {
    vector<ticket> tickets = load_csv("../parking_citations_expanded.csv");

    vector<ticket> few(tickets.begin(), tickets.begin() + 20000);

    vector<ticket> sorted = do_quick_sort(few, TicketData::Month);

    display_tickets(sorted);
}