#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

#include "stdfunctions.hpp"

#include "fetch_data_LANG_FR.hpp"

using namespace std;

/*
    nouns: s
    adjectives: j
    verbs: v
    adverbs: d
*/

int fetch_data_LANG_FR_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds) {

    CURL *curl;
    CURLcode res;

    std::string output_path = tmp_download_path + category_data_path;
    
    curl = curl_easy_init();

    if (curl) {

        FILE *file;

        // fetch the entire dictionary and output it to a file
        file = fopen(const_cast<char*>(output_path.c_str()), "wb");

        curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/pquentin/wiktionary-translations/master/frwiktionary-20140612-euradicfmt.csv");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, curl_timeout_seconds);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        fclose(file);

        if (res != CURLE_OK) return 1;
    }

    return 0;
}