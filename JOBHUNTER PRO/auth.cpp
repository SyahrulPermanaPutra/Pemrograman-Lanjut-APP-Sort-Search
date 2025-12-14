#include "auth.h"
#include <iostream>

using namespace std;

AuthSystem::AuthSystem() {
    currentUser = nullptr;
    isLoggedIn = false;
    registerDefaultUsers();
}

void AuthSystem::registerDefaultUsers() {
    // Register admin
    User admin;
    admin.username = "admin";
    admin.password = "admin123";
    admin.role = ROLE_ADMIN;
    users[admin.username] = admin;

    // Register default user
    User user;
    user.username = "user";
    user.password = "user123";
    user.role = ROLE_USER;
    users[user.username] = user;
}

bool AuthSystem::login(const string& username, const string& password) {
    auto it = users.find(username);

    if (it != users.end() && it->second.password == password) {
        currentUser = new User(it->second);
        isLoggedIn = true;
        return true;
    }

    return false;
}

void AuthSystem::logout() {
    if (currentUser) {
        delete currentUser;
        currentUser = nullptr;
    }
    isLoggedIn = false;
}

bool AuthSystem::isUserLoggedIn() const {
    return isLoggedIn;
}

UserRole AuthSystem::getCurrentUserRole() const {
    if (currentUser) {
        return currentUser->role;
    }
    return ROLE_USER;
}

string AuthSystem::getCurrentUsername() const {
    if (currentUser) {
        return currentUser->username;
    }
    return "";
}