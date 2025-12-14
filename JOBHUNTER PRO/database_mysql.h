#ifndef DATABASE_MYSQL_H
#define DATABASE_MYSQL_H

#include "database.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <vector>
#include <string>

using namespace std;

class DatabaseMySQL {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    bool connected;

public:
    // Constructor & Destructor
    DatabaseMySQL(const string& host, const string& user,
        const string& pass, const string& database);
    ~DatabaseMySQL();

    // Connection management
    bool connect();
    void disconnect();
    bool isConnected();
    bool getConnectionStatus() const;

    // CRUD operations
    vector<Lowongan> loadAllLowongan();
    int createLowongan(const Lowongan& l);
    bool updateLowongan(const Lowongan& l);
    bool deleteLowongan(int id);

    // Utility functions
    int getTotalLowongan();
    void clearAllData();
    int generateSampleData(int count);

private:
    // Helper function
    Lowongan resultSetToLowongan(sql::ResultSet* res);
};

#endif // DATABASE_MYSQL_H