#include <string>
#include <curl/curl.h>
#include <sqlite3.h>
#include <iostream>

#include "stdfunctions.hpp"

#include "fetch_data_LANG_JP.hpp"

using namespace std;

// from https://videlais.com/2018/12/13/c-with-sqlite3-part-3-inserting-and-selecting-data/
int callback(void *not_used, int argc, char **argv, char **azColName) {

    std::cout << "TABLE START" << endl;

    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value
    for(int i = 0; i < argc; i++) {
        
        // Show column name, value, and newline
        std::cout << azColName[i] << ": " << argv[i] << endl;
    }

    // Insert a newline
    std::cout << endl;

    // Return successful
    return 0;
}

int fetch_data_LANG_JP_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds) {

    char *err_msg;

    // this relies on build_data existing with the right files!
    sqlite3* db_hiragana;
    int res_hiragana = sqlite3_open("../build_data/anki-1552733819.db", &db_hiragana);
    if (!res_hiragana) {

        // fetch the needed data
        sqlite3_exec(db_hiragana, "SELECT * FROM notes;", callback, 0, &err_msg);

    } else return 3;
    sqlite3_close(db_hiragana);

    return 0;
}