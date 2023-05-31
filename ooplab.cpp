#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    bool present;
};

void saveAttendance(string course, string date, vector<Student>& students) {
    ofstream outfile("attendance.txt", ios::app);
    outfile << course << "," << date << endl;
    for (int i = 0; i < students.size(); i++) {
        outfile << students[i].name << "," << students[i].present << endl;
    }
    outfile.close();
    cout << "Attendance data saved to file." << endl;
}

void viewAttendance(string course, string date) {
    ifstream infile("attendance.txt");
    string line;
    bool found = false;
    while (getline(infile, line)) {
        string temp_course, temp_date;
        temp_course = line.substr(0, line.find(","));
        line.erase(0, line.find(",") + 1);
        temp_date = line.substr(0, line.find(","));
        line.erase(0, line.find(",") + 1);
        if (temp_course == course && temp_date == date) {
            cout << "Attendance for " << course << " on " << date << ":" << endl;
            while (getline(infile, line)) {
                if (line.empty()) {
                    break;
                }
                string temp_name, temp_present;
                temp_name = line.substr(0, line.find(","));
                line.erase(0, line.find(",") + 1);
                temp_present = line.substr(0, line.find(","));
                line.erase(0, line.find(",") + 1);
                cout << temp_name << ": " << (temp_present == "1" ? "Present" : "Absent") << endl;
            }
            found = true;
            break;
        }
    }
    infile.close();
    if (!found) {
        cout << "Attendance data not found." << endl;
    }
}

int main() {
    cout << "Attendance Management System" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Enter attendance data" << endl;
    cout << "2. View attendance data" << endl;
    cout << "3. Exit" << endl;
    int choice;
    do {
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        if (choice == 1) {
            string course, date;
            cout << "Enter the name of the course: ";
            cin >> course;
            cout << "Enter the date of the attendance (DD/MM/YYYY): ";
            cin >> date;
            vector<Student> students;
            int num_students;
            cout << "Enter the number of students: ";
            cin >> num_students;
            for (int i = 0; i < num_students; i++) {
                string name;
                cout << "Enter the name of student " << i + 1 << ": ";
                cin >> name;
                char present;
                cout << "Is " << name << " present? (Y/N): ";
                cin >> present;
                students.push_back({ name, (present
            == 'Y' || present == 'y' )});
        }
        saveAttendance(course, date, students);
    } else if (choice == 2) {
        string course, date;
        cout << "Enter the name of the course: ";
        cin >> course;
        cout << "Enter the date of the attendance (DD/MM/YYYY): ";
        cin >> date;
        viewAttendance(course, date);
    } else if (choice != 3) {
        cout << "Invalid choice. Please try again." << endl;
    }
} while (choice != 3);
return 0;
}
