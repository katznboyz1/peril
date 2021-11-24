#include <string>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <fstream>

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

    std::string output_path = tmp_download_path + "LANG_FR_all.txt";
    char* output_path_char = const_cast<char*>(output_path.c_str());
    
    curl = curl_easy_init();

    if (curl) {

        FILE *file;

        // fetch the entire dictionary and output it to a file
        file = fopen(output_path_char, "wb");

        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
        curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/pquentin/wiktionary-translations/master/frwiktionary-20140612-euradicfmt.csv");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, curl_timeout_seconds);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        fclose(file);

        if (res != CURLE_OK) return 1;

    } else return 2;

    // parse the file into different sections
    std::ifstream dictionary_file(output_path_char);
    std::string line;

    ofstream lang_fr_nouns_stream;
    ofstream lang_fr_adjectives_stream;
    ofstream lang_fr_verbs_stream;

    lang_fr_nouns_stream.open(category_data_path + LANG_FR_DATA_VOCAB_NOUNS);
    lang_fr_adjectives_stream.open(category_data_path + LANG_FR_DATA_VOCAB_ADJECTIVES);
    lang_fr_verbs_stream.open(category_data_path + LANG_FR_DATA_VERB_VOCABULARY);

    while (std::getline(dictionary_file, line)) {

        // will be in the format [word_fr, word_type_fr, TR-FR-EN, word_en, word_type_en]
        std::vector<std::string> split_line = string_split(line, ';');
        std::string word_type = split_line[1];
        std::string word_FR = split_line[0];
        std::string word_EN = split_line[3];
        std::string actual_line_output_contents = split_line[0] + ";" + split_line[3];

        // unfortunately else if statements break this, I will investigate later.
        if (word_type.compare("S")) lang_fr_nouns_stream << actual_line_output_contents << "\n";
        if (word_type.compare("V")) lang_fr_verbs_stream << actual_line_output_contents << "\n";
        if (word_type.compare("J")) lang_fr_adjectives_stream << actual_line_output_contents << "\n";
    }

    lang_fr_nouns_stream.close();
    lang_fr_adjectives_stream.close();
    lang_fr_verbs_stream.close();

    return 0;
}