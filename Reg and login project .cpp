
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function declarations
void registerUser();
bool userExists(const string& username);
bool authenticateUser(const string& username, const string& password);

int main() {
    int choice;
    string username, password;

    while (true) {
        cout << "Welcome to the system\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (authenticateUser(username, password))
                    cout << "Login successful!\n";
                else
                    cout << "Invalid username or password\n";
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// Function to register a new user
void registerUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();

    cout << "Registration successful!\n";
}

// Function to check if a user already exists
bool userExists(const string& username) {
    string line;
    ifstream infile("users.txt");

    while (getline(infile, line)) {
        if (line.substr(0, line.find(' ')) == username) {
            infile.close();
            return true;
        }
    }

    infile.close();
    return false;
}

// Function to authenticate a user
bool authenticateUser(const string& username, const string& password) {
    string line;
    ifstream infile("users.txt");

    while (getline(infile, line)) {
        size_t pos = line.find(' ');
        string storedUsername = line.substr(0, pos);
        string storedPassword = line.substr(pos + 1);

        if (storedUsername == username && storedPassword == password) {
            infile.close();
            return true;
        }
    }

    infile.close();
    return false;
}
