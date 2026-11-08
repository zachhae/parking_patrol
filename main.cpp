#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
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
    
void display_top_ten(const vector<ticket>& tickets, TicketData data) {
    unordered_map<variant<string, int, double>, int> tracker;

    for (const auto& t : tickets) {
        tracker[t.get_data_field(data)]++;
    }

    vector<pair<variant<string, int, double>, int>> results(tracker.begin(), tracker.end());
    sort(results.begin(), results.end(), [](auto a, auto b) {
        return a.second > b.second;
    });

    cout << "\nShowing top 10 offender results:\n";
    cout << string(40, '-') << endl;
    for (int i = 0; i < 10 && i < results.size(); i++) {
        visit([](auto &arg) { cout << left << setw(35) << arg; }, results[i].first);
        cout << right << setw(5) << results[i].second << endl;
    }
}


int main() {
    vector<ticket> tickets = load_csv("../parking_citations_expanded.csv");

    // vector<ticket> few(tickets.begin(), tickets.begin() + 20000);
    //
    // vector<ticket> sorted = do_quick_sort(few, TicketData::Month);
    //
    // display_tickets(sorted);

    display_top_ten(tickets, TicketData::Plate_Number);
}