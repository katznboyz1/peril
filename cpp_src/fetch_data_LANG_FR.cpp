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

    CURL *curl_1;
    CURL *curl_2;
    CURLcode res;

    std::string output_path_str_1 = tmp_download_path + "LANG_FR_1.txt";
    std::string output_path_str_2 = tmp_download_path + "LANG_FR_2.txt";

    char* output_path_char_1 = const_cast<char*>(output_path_str_1.c_str());
    char* output_path_char_2 = const_cast<char*>(output_path_str_2.c_str());
    
    curl_1 = curl_easy_init();
    curl_2 = curl_easy_init();

    if (curl_1 && curl_2) {
        
        FILE *file_1;
        FILE *file_2;

        // fetch the entire dictionary and output it to a file
        file_1 = fopen(output_path_char_1, "wb");

        curl_easy_setopt(curl_1, CURLOPT_FAILONERROR, 1);
        curl_easy_setopt(curl_1, CURLOPT_URL, "https://raw.githubusercontent.com/pquentin/wiktionary-translations/master/frwiktionary-20140612-euradicfmt.csv");
        curl_easy_setopt(curl_1, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl_1, CURLOPT_WRITEDATA, file_1);
        curl_easy_setopt(curl_1, CURLOPT_TIMEOUT, curl_timeout_seconds);

        res = curl_easy_perform(curl_1);
        curl_easy_cleanup(curl_1);

        fclose(file_1);

        if (res != CURLE_OK) return 2;

        // fetch the entire dictionary and output it to a file
        file_2 = fopen(output_path_char_2, "wb");

        curl_easy_setopt(curl_2, CURLOPT_FAILONERROR, 1);
        curl_easy_setopt(curl_2, CURLOPT_URL, "https://raw.githubusercontent.com/ianmackinnon/inflect/master/french-verb-conjugation.csv");
        curl_easy_setopt(curl_2, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl_2, CURLOPT_WRITEDATA, file_2);
        curl_easy_setopt(curl_2, CURLOPT_TIMEOUT, curl_timeout_seconds);

        res = curl_easy_perform(curl_2);
        curl_easy_cleanup(curl_2);

        fclose(file_2);

        if (res != CURLE_OK) return 3;

    } else return 1;

    // parse the file into different sections
    std::ifstream dictionary_file(output_path_char_1);
    std::string line_1;

    ofstream lang_fr_nouns_stream;
    ofstream lang_fr_adjectives_stream;
    ofstream lang_fr_verbs_stream;

    lang_fr_nouns_stream.open(category_data_path + LANG_FR_DATA_VOCAB_NOUNS);
    lang_fr_adjectives_stream.open(category_data_path + LANG_FR_DATA_VOCAB_ADJECTIVES);
    lang_fr_verbs_stream.open(category_data_path + LANG_FR_DATA_VERB_VOCABULARY);

    while (std::getline(dictionary_file, line_1)) {

        // will be in the format [word_fr, word_type_fr, TR-FR-EN, word_en, word_type_en]
        std::vector<std::string> split_line = string_split(line_1, ';');
        std::string word_type = split_line[1];
        std::string actual_line_output_contents = "What is the meaning of " + split_line[0] + " in English?" + "|" + split_line[3];

        // unfortunately else if statements break this, I will investigate later.
        if (word_type.compare("S")) lang_fr_nouns_stream << actual_line_output_contents << "\n";
        if (word_type.compare("V")) lang_fr_verbs_stream << actual_line_output_contents << "\n";
        if (word_type.compare("J")) lang_fr_adjectives_stream << actual_line_output_contents << "\n";
    }

    lang_fr_nouns_stream.close();
    lang_fr_adjectives_stream.close();
    lang_fr_verbs_stream.close();

    std::ifstream verb_conjugation_list_file(output_path_char_2);
    std::string line_2;

    int line_count_2 = 0;

    std::vector<std::string> verb_conjugation_list_file_columns;

    ofstream lang_fr_verb_conjugations_stream;

    lang_fr_verb_conjugations_stream.open(category_data_path + LANG_FR_DATA_VERB_CONJUGATIONS);

    while (std::getline(verb_conjugation_list_file, line_2)) {

        if (line_count_2 == 0) { // top of the csv list where the definitions of each column are

            verb_conjugation_list_file_columns = string_split(line_2, '|');

        } else { // normal data

            std::vector<std::string> current_parsed_verb_conjugation_line = string_split(line_2, ',');

            for (int i = 0; i < verb_conjugation_list_file_columns.size(); i++) {

                if (i > verb_conjugation_list_file_columns.size() - 1) continue;
                
                lang_fr_verb_conjugations_stream << "What is the " << verb_conjugation_list_file_columns[i] << " form of the verb " << current_parsed_verb_conjugation_line[0] << "?|" << current_parsed_verb_conjugation_line[i] << "\n";
            }
        }

        line_count_2++;
    }

    // delete (or try to delete) the tmp files
    // dont check the return value, what happens happens
    // its in /tmp/ so itll be deleted later anyhow
    remove(output_path_char_1);
    remove(output_path_char_2);

    return 0;
}