#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj; // (course, (time_slot, hours))
    unordered_map<string, vector<string>> conflicts; // (course, list of conflicting courses)

public:
    void addCourse(const string &course) {
        adj[course]; // Initialize the course in the graph
        conflicts[course]; // Initialize conflict edges for the course
    }

    void addTimeSlot(const string &course, int hours) {
        // Check if the time slot already exists in any course
        for (const auto &pair : adj) {
            for (const auto &timeSlot : pair.second) {
                if (timeSlot.second == hours) {
                    cout << "Time slot of " << hours << " hours already exists for course " << pair.first << ".\n";

                    // Add an edge to indicate conflict
                    conflicts[course].push_back(pair.first);
                    conflicts[pair.first].push_back(course);
                    return; // Prevent adding the same time slot for any course
                }
            }
        }

        if (adj.find(course) != adj.end()) {
            adj[course].emplace_back("Hour Block", hours); // Add time slot
            cout << "Time slot added for " << course << endl;
        } else {
            cout << "Course not found: " << course << endl;
        }
    }

    void deleteCourse(const string &course) {
        if (adj.erase(course)) {
            conflicts.erase(course); // Remove conflicts associated with the course
            cout << "Course deleted: " << course << endl;
        } else {
            cout << "Course not found: " << course << endl;
        }
    }

    void updateLastTimeSlot(const string &course, int newHours) {
        if (adj.find(course) != adj.end() && !adj[course].empty()) {
            adj[course].back().second = newHours; // Update the last added time slot
            cout << "Last time slot updated for " << course << " to " << newHours << " hours.\n";
        } else {
            cout << "Invalid course or no time slots available.\n";
        }
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

    // Display conflicting courses
    void displayConflicts() {
        cout << "Course Conflicts:\n";
        for (const auto &pair : conflicts) {
            if (!pair.second.empty()) {
                cout << pair.first << " conflicts with: ";
                for (const auto &conflict : pair.second) {
                    cout << conflict << " ";
                }
                cout << endl;
            }
        }
    }

    // BFS traversal
    void BFS(const string &start) {
        if (adj.find(start) == adj.end()) {
            cout << "Error: Course '" << start << "' does not exist.\n";
            return;
        }

        queue<string> q;
        unordered_map<string, bool> visited;

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal: ";

        while (!q.empty()) {
            string course = q.front();
            q.pop();
            cout << course << " ";

            for (auto &neighbor : adj[course]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    // DFS helper function
    void DFSHelper(const string &course, unordered_map<string, bool> &visited) {
        visited[course] = true;
        cout << course << " ";

        for (auto &neighbor : adj[course]) {
            if (!visited[neighbor.first]) {
                DFSHelper(neighbor.first, visited);
            }
        }
    }

    // DFS traversal
    void DFS(const string &start) {
        if (adj.find(start) == adj.end()) {
            cout << "Error: Course '" << start << "' does not exist.\n";
            return;
        }

        unordered_map<string, bool> visited;
        cout << "DFS Traversal: ";
        DFSHelper(start, visited);
        cout << endl;
    }
};

int main() {
    Graph timetable;
    int choice;

    do {
        cout << "\nCollege Timetable Scheduler\n";
        cout << "1. Add Course\n";
        cout << "2. Add Time Slot\n";
        cout << "3. Delete Course\n";
        cout << "4. Update Last Time Slot\n";
        cout << "5. Display Timetable\n";
        cout << "6. Display Conflicts\n";
        cout << "7. BFS Traversal\n";
        cout << "8. DFS Traversal\n";
        cout << "9. Exit\n";
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
        } else if (choice == 3) {
            string course;
            cout << "Enter course name to delete: ";
            cin >> course;
            timetable.deleteCourse(course);
        } else if (choice == 4) {
            string course;
            int newHours;
            cout << "Enter course name: ";
            cin >> course;
            cout << "Enter new hours for the last time slot: ";
            cin >> newHours;
            timetable.updateLastTimeSlot(course, newHours);
        } else if (choice == 5) {
            timetable.displayTimetable();
        } else if (choice == 6) {
            timetable.displayConflicts();
        } else if (choice == 7) {
            string course;
            cout << "Enter starting course for BFS: ";
            cin >> course;
            timetable.BFS(course);
        } else if (choice == 8) {
            string course;
            cout << "Enter starting course for DFS: ";
            cin >> course;
            timetable.DFS(course);
        } else if (choice == 9) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
