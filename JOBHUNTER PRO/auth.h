#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <map>

using namespace std;

enum UserRole {
    ROLE_ADMIN,
    ROLE_USER
};

struct User {
    string username;
    string password;
    UserRole role;
};

class AuthSystem {
private:
    map<string, User> users;
    User* currentUser;
    bool isLoggedIn;

public:
    AuthSystem();
    bool login(const string& username, const string& password);
    void logout();
    bool isUserLoggedIn() const;
    UserRole getCurrentUserRole() const;
    string getCurrentUsername() const;
    void registerDefaultUsers();
};

#endif