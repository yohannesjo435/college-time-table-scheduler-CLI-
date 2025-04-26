#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Graph
{
    unordered_map<string, vector<string>> adj;

public:
    Graph()
    {
        adj["Disctete Maths"] = {};
        adj["DSA1021"] = {};
        adj["ADB1032"] = {};
        adj["oop"] = {};
        adj["FDB"] = {};
        adj["Basic Programming"] = {};


         adj["DSA1021"].push_back("Disctete Maths");
         adj["ADB1012"].push_back("FDB");
         adj["oop"].push_back("Basic Programming");
         adj["FDB"].push_back("Disctete Maths");
         adj["DSA1021"].push_back("Basic Programming");

    }


    void addCourse(const string &course)
    {
        adj[course];

    }


    void addPrerequisite(const string &course, const string &prerequisite)
    {

        for (const auto &pair : adj)
        {
            if (pair.first == course)
            {
                for (const auto &prereq : pair.second)
                {
                    if (prereq == prerequisite)
                    {
                        cout << "Prerequisite already exists between " << course << " and " << prerequisite << endl;
                        return;
                    }
                }
                adj[course].push_back(prerequisite);
                cout << "Prerequisite added: " << prerequisite << " for course " << course << endl;
                return;
            }
        }

        cout << "Course not found: " << course << endl;
    }


    void deleteCourse(const string &course)
    {
        if (adj.erase(course))
        {

            cout << "Course deleted: " << course << endl;
        }
        else
        {
            cout << "Course not found: " << course << endl;
        }
    }


    void updatePrerequisite(const string &course, const string &oldPrerequisite, const string &newPrerequisite)
    {
        if (adj.find(course) != adj.end())
        {
            for (auto &prerequisite : adj[course])
            {
                if (prerequisite == oldPrerequisite)
                {
                    prerequisite = newPrerequisite;
                    cout << "Prerequisite updated from " << oldPrerequisite << " to " << newPrerequisite << " for course " << course << endl;
                    return;
                }
            }
            cout << "Old prerequisite not found" << endl;
        }
        else
        {
            cout << "Course not found: " << course << endl;
        }
    }


    void displayTimetable()
    {
        cout << "College Timetable (Prerequisites):" << endl;
        for (const auto &pair : adj)
        {
            cout << pair.first << " has prerequisites: ";
            if (pair.second.empty())
            {
                cout << "None" << endl;
            }
            else
            {
                for (const auto &prereq : pair.second)
                {
                    cout << prereq << " ";
                }
                cout << endl;
            }
        }
    }




   void BFS(const string &start)
{
    if (adj.find(start) == adj.end())
    {
        cout << "Error: Course '" << start << "' does not exist" << endl;
        return;
    }

    queue<string> q;
    unordered_map<string, bool> visited;

    q.push(start);
    visited[start] = true;

    cout << "BFS Traversal: ";

    while (!q.empty())
    {
        string course = q.front();
        q.pop();
        cout << course << " ";

        for (const auto &prerequisite : adj[course])
        {
            if (!visited[prerequisite])
            {
                visited[prerequisite] = true;
                q.push(prerequisite);
            }
        }
    }
    cout << endl;
}


   void DFSHelper(const string &course, unordered_map<string, bool> &visited)
{
    visited[course] = true;
    cout << course << " ";

    for (const auto &prerequisite : adj[course])
    {
        if (!visited[prerequisite])
        {
            DFSHelper(prerequisite, visited);
        }
    }
}

    void DFS(const string &start)
    {
        if (adj.find(start) == adj.end())
        {
            cout << "Error: Course '" << start << "' does not exist" << endl;
            return;
        }

        unordered_map<string, bool> visited;
        cout << "DFS Traversal: ";
        DFSHelper(start, visited);
        cout << endl;
    }

    void displayGraph()
    {
        cout << "Course Prerequisite Graph:" << endl;
        for (const auto &course : adj)
        {
            cout << course.first << " -> ";
            if (course.second.empty())
            {
                cout << "No prerequisites" << endl;
            }
            else
            {
                for (const auto &prerequisite : course.second)
                {
                    cout << prerequisite << " ";
                }
                cout << endl;
            }
        }
    }
};

int main()
{
    Graph timetable;
    int choice;
    string course, prerequisite, newPrerequisite;

    for (choice = 1; choice <= 9; choice++)
    {
        cout << "College Timetable Scheduler" << endl;
        cout << "1. Add Course" << endl;
        cout << "2. Add Prerequisite" << endl;
        cout << "3. Delete Course" << endl;
        cout << "4. Update Prerequisite" << endl;
        cout << "5. Display Timetable" << endl;
        cout << "6. BFS Traversal" << endl;
        cout << "7. DFS Traversal" << endl;
        cout << "8. Display Graph" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter course name: " << endl;
            cin >> course;
            timetable.addCourse(course);
            break;
        case 2:
            cout << "Enter course name: " << endl;
            cin >> course;
            cout << "Enter prerequisite course: " << endl;
            cin >> prerequisite;
            timetable.addPrerequisite(course, prerequisite);
            break;
        case 3:
            cout << "Enter course name to delete: " << endl;
            cin >> course;
            timetable.deleteCourse(course);
            break;
        case 4:
            cout << "Enter course name: " << endl;
            cin >> course;
            cout << "Enter old prerequisite: " << endl;
            cin >> prerequisite;
            cout << "Enter new prerequisite: " << endl;
            cin >> newPrerequisite;
            timetable.updatePrerequisite(course, prerequisite, newPrerequisite);
            break;
        case 5:
            timetable.displayTimetable();
            break;
       case 6:
            cout << "Enter starting course for BFS: " << endl;
            cin >> course;
            timetable.BFS(course);
            break;
        case 7:
            cout << "Enter starting course for DFS: " << endl;
            cin >> course;
            timetable.DFS(course);
            break;
        case 8:
            timetable.displayGraph();
            break;
        case 9:
            cout << "Exiting" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
