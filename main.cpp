#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj; // (course, (next_course, weight))

public:
    void addCourse(const string &course) {
        adj[course]; // Initialize the course in the graph
    }

    void addTimeSlot(const string &course, int hours) {
        adj[course].emplace_back("Hour Block", hours); // Just a placeholder for time slots
    }

    void displayTimetable() {
        cout << "College Timetable:\n";
        for (const auto &pair : adj) {
            cout << pair.first << " has the following time slots:\n";
            for (const auto &timeSlot : pair.second) {
                cout << "  - " << timeSlot.second << " hours\n";
            }
        }
    }
};

int main() {
    Graph timetable;
    int choice;

    do {
        cout << "\nCollege Timetable Scheduler\n";
        cout << "1. Add Course\n";
        cout << "2. Add Time Slot\n";
        cout << "3. Display Timetable\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string course;
            cout << "Enter course name: ";
            cin >> course;
            timetable.addCourse(course);
            cout << "Course added: " << course << endl;
        } else if (choice == 2) {
            string course;
            int hours;
            cout << "Enter course name: ";
            cin >> course;
            cout << "Enter time slot (in hours): ";
            cin >> hours;
            timetable.addTimeSlot(course, hours);
            cout << "Time slot added for " << course << endl;
        } else if (choice == 3) {
            timetable.displayTimetable();
        } else if (choice == 4) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}