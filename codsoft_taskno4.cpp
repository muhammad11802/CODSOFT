#include <iostream>
#include <string>
using namespace std;

class Task {
    static int nextId;
    int id;
    string name;
    bool status;

public:
    Task() : id(nextId++), name(""), status(false) {}

    Task(string n, bool s) :id(nextId++), name(n), status(s) {}

    void setname(string n) {
        name = n;
    }
    string getname() const {
        return name;
    }
    void setstatus(bool s) {
        status = s;
    }
    bool getstatus() const {
        return status;
    }

    void display() const {
        cout << "Task " << id << ":"<<endl;

        cout << "Task Name: " << name << "  "<<endl;
        if (status) {
            cout << "Status = completed" << endl;
        }
        else {
            cout << "Status = not completed" << endl;
        }
        cout << endl;
    }
};
int Task::nextId = 1;

class Node {
public:
    Task t;
    Node* next;

    Node(Task em) : t(em), next(nullptr) {} // Constructor

    ~Node() {} // Destructor
};

class LinkedList {
private:
    Node* head;
    Node* last;

public:
    LinkedList() : head(nullptr), last(nullptr) {} // Constructor

    ~LinkedList() { // Destructor
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(Task t) {
        Node* temp = new Node(t);
        if (head == nullptr) {
            head = temp;
            last = temp;
        }
        else {
            last->next = temp;
            last = temp;
        }
    }

    void remove(string n) {
        if (head == nullptr) {
            cout << "EMPTY LIST!" << endl;
            return;
        }

        Node* curr = head;
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->t.getname() == n) {
                if (prev == nullptr) {
                    head = curr->next;
                }
                else {
                    prev->next = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }

        cout << "Task not found :(" << endl;
    }

    void printList() const {
        Node* temp = head;
        while (temp != nullptr) {
            temp->t.display();
            temp = temp->next;
        }
    }
    void markcompleted(string n) {

        Node* temp = head;
        bool taskFound = false;
        while (temp != nullptr) {
            if (temp->t.getname() == n) {
                temp->t.setstatus(true);
                taskFound = true;
                break;
            }
            temp = temp->next;
        }

        if (taskFound) {
            cout << "Task marked as completed successfully." << endl;
        }
        else {
            cout << "Task not found :(" << endl;
        }
    }
};

int main() {
   

    LinkedList todoList;

    while (true) {
        system("cls");
        cout << "-----TO-DO LIST-----" << endl << endl;
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Completed" << endl;
        cout << "4. Remove Task" << endl;
        cout << "5. Exit" << endl;

        int choice;
        int choice2;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            system("cls");
            string taskName;
            cout << "Enter task name: ";
            cin.ignore(); 
            getline(cin, taskName);
            Task newTask(taskName, false);
            todoList.insert(newTask);

            break;
        }
        case 2: {
            system("cls");
            cout << "Tasks:" << endl;
            todoList.printList();
            cout << "Press any digit to go back: ";
            cin >> choice2;
            break;
        }
        case 3: {
            system("cls");
            string taskName;
            cout << "Enter task name to mark as completed: ";
            cin.ignore();
            getline(cin, taskName);
            todoList.markcompleted(taskName);
            cout << "Press any digit to go back: ";
            cin >> choice2;

            break;
        }

        case 4: {
            system("cls");
            string taskName;
            cout << "Enter task name to remove: ";
            cin.ignore();
            getline(cin, taskName);
            todoList.remove(taskName);
            cout << "Press any digit to go back: ";
            cin >> choice2;
            break;
        }
        case 5: {
            system("cls");
            cout << "Exiting..." << endl;
            return 0;
        }
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
