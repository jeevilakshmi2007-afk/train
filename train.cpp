#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Coach {
    string name;
    Coach* next;
    Coach(const string& n) : name(n), next(nullptr) {}
};

class Train {
private:
    Coach* head;

public:
    Train() : head(nullptr) {}

    // Free all nodes when the object is destroyed
    ~Train() {
        while (head != nullptr) {
            Coach* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Add a coach at the beginning
    void addAtBeginning(const string& name) {
        Coach* newCoach = new Coach(name);
        newCoach->next = head;
        head = newCoach;
        cout << "\"" << name << "\" added at the beginning.\n";
    }

    // Add a coach at the end
    void addAtEnd(const string& name) {
        Coach* newCoach = new Coach(name);
        if (head == nullptr) {
            head = newCoach;
        } else {
            Coach* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newCoach;
        }
        cout << "\"" << name << "\" added at the end.\n";
    }

    // Remove a coach by name
    void removeCoach(const string& name) {
        if (head == nullptr) {
            cout << "Train is empty. Nothing to remove.\n";
            return;
        }

        // If the coach to remove is the first one
        if (head->name == name) {
            Coach* temp = head;
            head = head->next;
            delete temp;
            cout << "\"" << name << "\" removed.\n";
            return;
        }

        Coach* current = head;
        while (current->next != nullptr && current->next->name != name)
            current = current->next;

        if (current->next == nullptr) {
            cout << "\"" << name << "\" not found in the train.\n";
        } else {
            Coach* temp = current->next;
            current->next = temp->next;
            delete temp;
            cout << "\"" << name << "\" removed.\n";
        }
    }

    // Display all coaches
    void display() const {
        if (head == nullptr) {
            cout << "Train is empty.\n";
            return;
        }
        Coach* temp = head;
        while (temp != nullptr) {
            cout << temp->name << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

int main() {
    Train train;
    int choice = 0;
    string name;

    do {
        cout << "\n===== TRAIN MENU =====\n";
        cout << "1. Add coach at the beginning\n";
        cout << "2. Add coach at the end\n";
        cout << "3. Remove a coach\n";
        cout << "4. Display all coaches\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a number between 1 and 5.\n";
            choice = 0;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter coach name (e.g. Coach1): ";
                getline(cin, name);
                if (name.empty()) cout << "Name cannot be empty.\n";
                else train.addAtBeginning(name);
                break;
            case 2:
                cout << "Enter coach name (e.g. Coach4): ";
                getline(cin, name);
                if (name.empty()) cout << "Name cannot be empty.\n";
                else train.addAtEnd(name);
                break;
            case 3:
                cout << "Enter coach name to remove: ";
                getline(cin, name);
                train.removeCoach(name);
                break;
            case 4:
                train.display();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Enter 1 to 5.\n";
        }
    } while (choice != 5);

    return 0;
}
