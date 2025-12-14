#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include "database.h"
#include <string>
#include <vector>

using namespace std;

class JSONHandler {
public:
    // Save data to JSON file
    static bool saveToJSON(const vector<Lowongan>& data, const string& filename);

    // Load data from JSON file
    static vector<Lowongan> loadFromJSON(const string& filename);

private:
    // Helper functions
    static string escapeJSON(const string& str);
    static string vectorToJSON(const vector<string>& vec);
    static vector<string> parseJSONArray(const string& str);
};

#endif#pragma once
