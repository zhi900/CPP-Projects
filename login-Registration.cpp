#include <iostream>
#include <string>
#include <unordered_map>

struct User {
    std::string username;
    std::string password;
};

class UserDatabase {
private:
    std::unordered_map<std::string, User> users;

public:
    bool registerUser(const std::string& username, const std::string& password) {
        if (users.find(username) == users.end()) {
            User user;
            user.username = username;
            user.password = password;
            users[username] = user;
            return true;
        }
        return false;
    }

    bool loginUser(const std::string& username, const std::string& password) {
        if (users.find(username) != users.end()) {
            User& user = users[username];
            return user.password == password;
        }
        return false;
    }
};

int main() {
    UserDatabase userDB;
    bool isLoggedIn = false;
    std::string username, password;

    while (!isLoggedIn) {
        int choice;
        std::cout << "1. Register" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (userDB.registerUser(username, password)) {
                    std::cout << "Registration successful!" << std::endl;
                } else {
                    std::cout << "Username already exists!" << std::endl;
                }
                break;
            case 2:
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;
                if (userDB.loginUser(username, password)) {
                    isLoggedIn = true;
                    std::cout << "Login successful!" << std::endl;
                } else {
                    std::cout << "Invalid username or password!" << std::endl;
                }
                break;
            case 3:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
        }

        std::cout << std::endl;
    }

    // Rest of the program for logged-in user

    return 0;
}