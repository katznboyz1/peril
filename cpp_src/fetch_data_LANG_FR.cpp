#include <string>

#include "lib/curl.h"

#include "fetch_data_LANG_FR.hpp"

/*
    nouns: s
    adjectives: j
    verbs: v
    adverbs: d
*/

int fetch_data_LANG_FR_all(std::string category_data_path, std::string tmp_download_path) {

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {

        // fetch the entire dictionary
        curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/pquentin/wiktionary-translations/master/frwiktionary-20140612-euradicfmt.csv");
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) return -1;
    }

    return 0;
}