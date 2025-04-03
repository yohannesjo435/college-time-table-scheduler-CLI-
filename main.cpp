#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph
{
    unordered_map<string, vector<pair<string, int>>> adj;
    unordered_map<string, vector<string>> conflicts;

public:
    Graph()
    {
        adj["Math101"] = {}; // instantiating  constructor so that we dont have to call the function to enter courses inside the main
        conflicts["Math101"] = {};

        adj["DSA1021"] = {};
        conflicts["DSA1021"] = {};

        adj["ADB1032"] = {};
        conflicts["ADB1032"] = {};
    }
    // adding node
    void addCourse(const string &course)
    {
        adj[course];
        conflicts[course];
    }

    void addTimeSlot(const string &course, int duration)
    {
        // Check if the time slot already exists in any course(conflict detection)
        for (const auto &pair : adj)
        {
            for (const auto &timeSlot : pair.second)
            {

                if (timeSlot.second == duration)
                { // Check if the time slot already exists
                    cout << "Time slot of " << duration << " hours already exists for course " << pair.first << ".\n";
                    // Add an edge to show the conflict happening is bidirectional
                    conflicts[course].push_back(pair.first);
                    conflicts[pair.first].push_back(course);
                    return; // Prevent adding the same time slot for any course
                }
            }
        }

        if (adj.find(course) != adj.end())
        {
            adj[course].emplace_back(course, duration); // Add new time slot
            cout << "Time slot added for " << course << endl;
        }
        else
        {
            cout << "Course not found: " << course << endl;
        }
    }

    // deleting node
    void deleteCourse(const string &course)
    {
        if (adj.erase(course))
        {
            conflicts.erase(course); // Remove conflicts associated with the course
            cout << "Course deleted: " << course << endl;
        }
        else
        {
            cout << "Course not found: " << course << endl;
        }
    }
    // updating node
    void updateLastTimeSlot(const string &course, int newDuration)
    {
        if (adj.find(course) != adj.end() && !adj[course].empty())
        {
            adj[course].back().second = newDuration; // Update the last added time slot
            cout << "Last time slot updated for " << course << " to " << newDuration << " hours" << endl;
        }
        else
        {
            cout << "Invalid course or no time slots available" << endl;
        }
    }

    void displayTimetable()
    {
        cout << "College Timetable:" << endl;
        for (const auto &pair : adj)
        {
            cout << pair.first << " has the following time slots:\n";
            for (const auto &timeSlot : pair.second)
            {
                cout << timeSlot.second << " hours" << endl;
                ;
            }
        }
    }

    // Display conflicting courses
    void displayConflicts()
    {
        cout << "Course Conflicts:" << endl;
        for (const auto &pair : conflicts)
        {
            if (!pair.second.empty())
            {
                cout << pair.first << " conflicts with: ";
                for (const auto &conflict : pair.second)
                {
                    cout << conflict << " ";
                }
                cout << endl;
            }
        }
    }

    // BFS traversal
    void BFS(const string &start)
    {
        if (adj.find(start) == adj.end())
        {
            cout << "Error: Course '" << start << "' does not exist" << endl;
            return;
        }

        queue<string> q;
        unordered_map<string, bool> visited; // to ensure each course is visited only once in bfs

        q.push(start);
        visited[start] = true; // preventing the bfs from visitng the start course again

        cout << "BFS Traversal: ";

        while (!q.empty())
        {
            string course = q.front();
            q.pop(); // removes the course that was just visited from the front of the queue
            cout << course << " ";

            // to traverse all courses

            if (adj.find(course) != adj.end())
            { // Ensure course exists in adjacency list
                for (auto &neighbor : adj[course])
                {
                    if (!visited[neighbor.first])
                    {
                        visited[neighbor.first] = true;
                        q.push(neighbor.first);
                    }
                }
            }

            // traversing in bfs when there is cocnflict between courses
            for (auto &conflictCourse : conflicts[course])
            {
                if (!visited[conflictCourse])
                {
                    visited[conflictCourse] = true;
                    q.push(conflictCourse);
                }
            }
        }
        cout << endl;
    }

    // recursive function used in the main dfs function so that it will visit and print the visited courses
    void DFSHelper(const string &course, unordered_map<string, bool> &visited)
    {
        visited[course] = true;
        cout << course << " ";

        for (auto &neighbor : adj[course])
        {
            if (!visited[neighbor.first])
            {
                DFSHelper(neighbor.first, visited);
            }
        }
    }

    void DFS(const string &start)
    {

        if (adj.find(start) == adj.end())
        {
            cout << "Error: Course '" << start << "' does not exist" << endl;
            ;
            return;
        }

        unordered_map<string, bool> visited;
        cout << "DFS Traversal: ";
        DFSHelper(start, visited);
        cout << endl;
        for (auto &conflictCourse : conflicts[start])
        {
            if (!visited[conflictCourse])
            {
                DFSHelper(conflictCourse, visited);
            }
        }
        // printing every neighbouring course even if there is no conflict
        for (auto &coursePair : adj)
        {
            if (!visited[coursePair.first])
            {
                DFSHelper(coursePair.first, visited);
            }
        }
    }
};

int main()
{
    Graph timetable;
    int choice;
    int duration;
    int newDuration;

    timetable.addTimeSlot("ADB1032", 4);
    string course;
    for (choice = 1; choice <= 9; choice++)
    {
        cout << "College Timetable Scheduler" << endl;
        cout << "1. Add Course" << endl;
        cout << "2. Add Time Slot" << endl;
        cout << "3. Delete Course" << endl;
        cout << "4. Update Last Time Slot" << endl;
        cout << "5. Display Timetable" << endl;
        cout << "6. Display Conflicts" << endl;
        cout << "7. BFS Traversal" << endl;
        cout << "8. DFS Traversal" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter course name: " << endl;
            cin >> course;
            timetable.addCourse(course);
            cout << "Course added: " << course << endl;
            break;
        case 2:
            cout << "Enter course name: " << endl;
            cin >> course;
            cout << "Enter time slot (in hours): " << endl;
            cin >> duration;
            timetable.addTimeSlot(course, duration);
            break;
        case 3:
            cout << "Enter course name to delete: " << endl;
            cin >> course;
            timetable.deleteCourse(course);
            break;
        case 4:
            cout << "Enter course name: " << endl;
            cin >> course;
            cout << "Enter new hours for the last time slot: " << endl;
            cin >> newDuration;
            timetable.updateLastTimeSlot(course, newDuration);
            break;
        case 5:
            timetable.displayTimetable();
            break;
        case 6:
            timetable.displayConflicts();
            break;
        case 7:
            cout << "Enter starting course for BFS: " << endl;
            cin >> course;
            timetable.BFS(course);
            break;
        case 8:
            cout << "Enter starting course for DFS: " << endl;
            cin >> course;
            timetable.DFS(course);
            break;
        case 9:
            cout << "Exiting";
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
