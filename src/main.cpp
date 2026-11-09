#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <string>
#include "ticket.h"
#include "csv_loader.h"
#include "quick_sort.h"

using namespace std;


struct SortResult {
    string name;
    vector<ticket> tickets;   // the sorted list
    double timeMs = 0;
    long long comparisons = 0;
    long long moves = 0;
    bool finished = true;     // false if quick sort was stopped
};


//display menu
void printMenu(int ticketCount) {
    cout << endl;
    cout << "==============================================" << endl;
    cout << "      TICKET TRACKER  (" << ticketCount << " tickets)" << endl;
    cout << "==============================================" << endl;
    cout << " 1. Sort tickets by a field" << endl;
    cout << " 2. Two-level sort (e.g. street, then date)" << endl;
    cout << " 3. Top 10 offenders" << endl;
    cout << " 5. Run performance tests" << endl;
    cout << " 6. Exit" << endl;
    cout << "----------------------------------------------" << endl;
}

//input
int getNumber(int low, int high) {
    int number;
    while (true) {
        cout << "Choose: ";
        if (cin >> number) {
            if (number >= low && number <= high) {
                return number;
            }
        } else {
            if (cin.eof()) {
                return high; 
            }
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "Please type a number from " << low << " to " << high << "." << endl;
    }
}

string fieldName(TicketData data) {
    switch (data) {
        case TicketData::Plate_Number: return "Plate";
        case TicketData::Location: return "Street";
        case TicketData::Violation: return "Violation";
        case TicketData::Fine: return "Fine";
        case TicketData::Date: return "Date";
        default: return "Other";
    }
}

TicketData chooseField(string title) {
    cout << endl << title << endl;
    cout << " 1. Plate   2. Street   3. Violation   4. Fine   5. Date" << endl;
    int choice = getNumber(1, 5);
    if (choice == 1) return TicketData::Plate_Number;
    if (choice == 2) return TicketData::Location;
    if (choice == 3) return TicketData::Violation;
    if (choice == 4) return TicketData::Fine;
    return TicketData::Date;
}

int chooseAlgorithm() {
    cout << endl << "Algorithm:" << endl;
    cout << " 1. Merge Sort   2. Quick Sort (first pivot)   3. Both (compare)" << endl;
    return getNumber(1, 3);
}

SortResult runMergeSort(const vector<ticket>& tickets, TicketData data) {
    SortResult result;
    result.name = "Merge Sort";
    result.tickets = tickets; 
    int comparisons, moves;

    auto start = chrono::steady_clock::now();
    mergeSort(result.tickets, data, comparisons, moves);
    result.timeMs = msSince(start);

    result.comparisons = comparisons;
    result.moves = moves;
    return result;

SortResult runQuickSort(const vector<ticket>& tickets, TicketData data) {
    SortResult r;
    r.name = "Quick Sort (first pivot)";

    auto start = chrono::steady_clock::now();
    r.tickets = do_quick_sort(tickets, data, r.comparisons, r.moves);
    r.timeMs = msSince(start);

    return r;
}

vector<SortResult> runSorts(const vector<ticket>& tickets, TicketData data, int algorithm) {
    vector<SortResult> results;
    if (algorithm == MERGE || algorithm == BOTH) {
        results.push_back(runMergeSort(tickets, data));
    }
    if (algorithm == QUICK || algorithm == BOTH) {
        results.push_back(runQuickSort(tickets, data));
    }
    return results;
}

void display_tickets(const vector<ticket>& tickets, int limit = 15) {
    cout << "\nShowing top " << limit << " results:\n";
    cout << left 
         << setw(12) << "Plate" 
         << setw(8)  << "State" 
         << setw(15) << "Make" 
         << setw(35) << "Violation" 
         << setw(10) << "Fine ($)"
         << setw(15) << "Color"
         << ""Date"<< endl;
         
    cout << string(110, '-') << endl;

    int count = 0;
    for (const auto& t : tickets) {
        if (count >= limit) break; 
        
        cout << left 
             << setw(12) << t.plate_number
             << setw(8)  << t.state
             << setw(15) << t.vehicle_make
             << setw(35) << t.violation.substr(0, 33) 
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

// menu options

void sortByField(const vector<ticket>& tickets) {
    TicketData data = chooseField("Sort by:");
    int algorithm = chooseAlgorithm();

    cout << endl << "Sorting..." << endl;
    vector<SortResult> results = runSorts(tickets, data, algorithm);

    // show the first 10 tickets from a sort that finished
    for (const auto& r : results) {
        if (r.finished) {
            cout << endl << "First 10 tickets sorted by " << fieldName(data)
                 << " (" << r.name << "):" << endl;
            display_tickets(r.tickets);
            break;
        }
    }
    printResults(results, data);
}


int main() {
    vector<ticket> tickets = load_csv("../parking_citations_expanded.csv");

    if (tickets.empty()) {
            cerr << "Could not load the ticket file. Please try again with a different path." << endl;
        return 1;
    }
    cout << "Loaded " << tickets.size() << " tickets." << endl;

    int merge = 1;
    int quick = 2;
    int both = 3;

    while (true) {
        printMenu(tickets.size());
        int choice = getNumber(1, 6);

        if (choice == 1) {
            sortByField(tickets);
    
        } 
        else if (choice == 2) {
            cout << "Two-level sort not implemented yet." << endl;
        } 
        else if (choice == 3) {
            display_top_ten(tickets, TicketData::Plate_Number);
        } 
        else if (choice == 4) {
            display_top_ten(tickets, TicketData::Location);
        } 
        else if (choice == 5) {
        } 
        else if (choice == 6) {
            cout << "Exiting." << endl;
            break;
        }
    }


  
}

