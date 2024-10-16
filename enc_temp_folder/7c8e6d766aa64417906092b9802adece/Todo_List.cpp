#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

bool isRunning = true;

struct Tasks {
    string timeAdded;
    string dateAdded;
    string item;
    string importance;
};

vector<Tasks> todolist;

void addItem(string item, string importance); 
void deleteItem(int index);
void completeTask(int index);
void displayList();
string getCurrentDate();
string getCurrentTime();

int main()
{
    int choice;

    cout << " ---{[ Todo List ]}--- " << endl;
    cout << endl;
    while (isRunning) {

        displayList();

        cout << endl;
        cout << endl;

        cout << " Please Select an Option: \n \n 1. Add task. \n 2. Delete task \n 3. Mark Task Complete \n 4. Exit \n 5. Display List" << endl; 
        cout << endl;
        cout << " Your Choice: ";
        cin >> choice;
        cin.ignore();

        

        switch (choice) {
        case 1: {
            string item, importance;
            cout << "Please write a short task description: " << endl;
            getline(cin, item); 
            cout << endl;
            cout << "Please select a task importance (Low, Medium, High): ";
            cin >> importance;

            addItem(item, importance);
            system("cls");
            break;
        }
        case 2: {
            displayList();  
            int index;
            cout << "Enter task number to delete: ";
            cin >> index;
            deleteItem(--index);
            system("cls");
            break;
        }
        case 3: {
            displayList();
            int index;
            cout << "Enter task number to mark complete: ";
            cin >> index;
            completeTask(--index); 
            system("cls");
            break;
        }
        case 4: {
            isRunning = false;
            break;
        }
        case 5: {
            displayList();
            system("cls");
            break;
        }
        default:
            cout << "You've input something wrong, try again." << endl;
        }
    }
}

void addItem(string item, string importance) {
    string timeAdded = getCurrentTime();
    string dateAdded = getCurrentDate(); 

    Tasks newTask = { timeAdded, dateAdded, item, importance };  
    todolist.push_back(newTask);

    cout << "Task added: " << item << " at " << timeAdded << " on " << dateAdded << endl;
}

void deleteItem(int index) {
    if (index < 0 || index >= todolist.size()) {
        cout << "Invalid task number." << endl;
        return;
    }
    cout << "Task deleted: " << todolist[index].item << endl;
    todolist.erase(todolist.begin() + index);  
}

void completeTask(int index) {
    if (index < 0 || index >= todolist.size()) {
        cout << "Invalid task number." << endl;
        return;
    }
    cout << "Task completed: " << todolist[index].item << endl;
    todolist.erase(todolist.begin() + index);  
}

void displayList() {
    if (todolist.empty()) {
        cout << "The task list is empty." << endl;
        return;
    }
    for (int i = 0; i < todolist.size(); ++i) {
        cout << i + 1 << ". " << todolist[i].item << " (Importance: " << todolist[i].importance
            << ", Added: " << todolist[i].timeAdded << " on " << todolist[i].dateAdded << ")" << endl;
    }
}

string getCurrentDate() {
    auto currentTime = chrono::system_clock::now();
    time_t currentTimeT = chrono::system_clock::to_time_t(currentTime);
    tm localTime;
    localtime_s(&localTime, &currentTimeT);

    char buffer[11];  
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);  
    return string(buffer);
}

string getCurrentTime() {
    auto currentTime = chrono::system_clock::now();
    time_t currentTimeT = chrono::system_clock::to_time_t(currentTime);
    tm localTime;
    localtime_s(&localTime, &currentTimeT);

    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", &localTime);  
    return string(buffer);  
}