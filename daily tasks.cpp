
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

struct Task {
    string date;
    string day;
    string description;
    int priority;      // 1 = High, 2 = Medium, 3 = Low
    bool completed;
};

vector<Task> tasks;

// ---------------- SAVE TASKS ----------------
void saveTasks() {
    ofstream file("tasks.txt");
    for (size_t i = 0; i < tasks.size(); i++) {
        file << tasks[i].date << "|"
             << tasks[i].day << "|"
             << tasks[i].description << "|"
             << tasks[i].priority << "|"
             << tasks[i].completed << "\n";
    }
    file.close();
}

// ---------------- LOAD TASKS ----------------
void loadTasks() {
    tasks.clear();
    ifstream file("tasks.txt");
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        Task t;

        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        size_t p4 = line.find("|", p3 + 1);

        t.date = line.substr(0, p1);
        t.day = line.substr(p1 + 1, p2 - p1 - 1);
        t.description = line.substr(p2 + 1, p3 - p2 - 1);
        t.priority = atoi(line.substr(p3 + 1, p4 - p3 - 1).c_str());
        t.completed = (line.substr(p4 + 1) == "1");

        tasks.push_back(t);
    }
    file.close();
}

// -------------- SHOW PRIORITY NAME -------------
string getPriorityName(int p) {
    if (p == 1) return "High";
    if (p == 2) return "Medium";
    return "Low";
}

// ---------------- ADD TASK ----------------
void addTask() {
    system("cls");
    Task t;

    cout << "Enter date (DD/MM/YYYY): ";
    cin >> t.date;

    cout << "Enter day: ";
    cin >> t.day;
    cin.ignore();

    cout << "Enter task description: ";
    getline(cin, t.description);

    cout << "Select priority:\n1. High\n2. Medium\n3. Low\nEnter: ";
    cin >> t.priority;

    t.completed = false;

    tasks.push_back(t);
    saveTasks();

    cout << "\nTask added.";
}

// ---------------- VIEW ALL TASKS ----------------
void viewTasks() {
    system("cls");

    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "======== TASK LIST ========\n\n";

    for (size_t i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". ["
             << (tasks[i].completed ? "X" : " ")
             << "] " << tasks[i].date << " (" << tasks[i].day << ")\n";

        cout << "   Task: " << tasks[i].description << "\n";
        cout << "   Priority: " << getPriorityName(tasks[i].priority) << "\n\n";
    }
}

// ---------------- MARK COMPLETED ----------------
void markTask() {
    viewTasks();
    int index;
    cout << "Enter task number to mark completed: ";
    cin >> index;

    if (index < 1 || index > (int)tasks.size()) {
        cout << "Invalid number.";
        return;
    }

    tasks[index - 1].completed = true;
    saveTasks();

    cout << "Task marked completed.";
}

// ---------------- UNMARK COMPLETED ----------------
void unmarkTask() {
    viewTasks();
    int index;
    cout << "Enter task number to unmark: ";
    cin >> index;

    if (index < 1 || index > (int)tasks.size()) {
        cout << "Invalid number.";
        return;
    }

    tasks[index - 1].completed = false;
    saveTasks();

    cout << "Task unmarked.";
}

// ---------------- DELETE TASK ----------------
void deleteTask() {
    viewTasks();
    int index;
    cout << "Enter task number to delete: ";
    cin >> index;

    if (index < 1 || index > (int)tasks.size()) {
        cout << "Invalid number.";
        return;
    }

    tasks.erase(tasks.begin() + (index - 1));
    saveTasks();

    cout << "Task deleted.";
}

// ---------------- EDIT TASK ----------------
void editTask() {
    viewTasks();
    int index;
    cout << "Enter task number to edit: ";
    cin >> index;

    if (index < 1 || index > (int)tasks.size()) {
        cout << "Invalid number.";
        return;
    }

    cin.ignore();
    cout << "Enter new description: ";
    getline(cin, tasks[index - 1].description);

    cout << "Update priority (1=High, 2=Medium, 3=Low): ";
    cin >> tasks[index - 1].priority;

    saveTasks();
    cout << "Task updated.";
}

// -------- MOVE TASK UP (MANUAL REORDER) --------
void moveUp() {
    viewTasks();
    int index;
    cout << "Enter task number to move up: ";
    cin >> index;

    if (index <= 1 || index > (int)tasks.size()) {
        cout << "Cannot move up.";
        return;
    }

    Task temp = tasks[index - 1];
    tasks[index - 1] = tasks[index - 2];
    tasks[index - 2] = temp;

    saveTasks();
    cout << "Task moved up.";
}

// -------- MOVE TASK DOWN (MANUAL REORDER) --------
void moveDown() {
    viewTasks();
    int index;
    cout << "Enter task number to move down: ";
    cin >> index;

    if (index < 1 || index >= (int)tasks.size()) {
        cout << "Cannot move down.";
        return;
    }

    Task temp = tasks[index - 1];
    tasks[index - 1] = tasks[index];
    tasks[index] = temp;

    saveTasks();
    cout << "Task moved down.";
}

// ---------------- MAIN MENU ----------------
int main() {
    loadTasks();
    int choice;

    while (true) {
        system("cls");

        cout << "==== DAILY TASK MANAGER ====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Edit Task\n";
        cout << "4. Delete Task\n";
        cout << "5. Mark Completed\n";
        cout << "6. Unmark Completed\n";
        cout << "7. Move Task Up\n";
        cout << "8. Move Task Down\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        system("cls");

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: editTask(); break;
            case 4: deleteTask(); break;
            case 5: markTask(); break;
            case 6: unmarkTask(); break;
            case 7: moveUp(); break;
            case 8: moveDown(); break;
            case 9: return 0;
            default: cout << "Invalid choice."; break;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    return 0;
}

