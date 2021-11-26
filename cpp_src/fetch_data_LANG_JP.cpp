#include <string>
#include <curl/curl.h>
#include <sqlite3.h>
#include <iostream>
#include <fstream>

#include "stdfunctions.hpp"

#include "fetch_data_LANG_JP.hpp"

using namespace std;

int fetch_data_LANG_JP_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds) {

    //https://gist.githubusercontent.com/katznboyz1/9c679680ca7e661a5bc6ae8fc2062bc9/raw/e1beecbdeba1006dd9c62543a687adc544727ab3/anki-1552733819.csv

    CURL *curl[6];
    for (int i = 0; i < 6; i++) curl[i] = curl_easy_init();

    bool curl_init_was_success = true;
    for (int i = 0; i < 6; i++) curl_init_was_success = (curl_init_was_success && curl[i]);

    if (curl_init_was_success) {

        FILE *files[6];

        std::string urls[6] = {
            "https://gist.githubusercontent.com/katznboyz1/9c679680ca7e661a5bc6ae8fc2062bc9/raw/e1beecbdeba1006dd9c62543a687adc544727ab3/anki-1552733819.csv",
            "about:blank",
            "about:blank",
            "about:blank",
            "about:blank",
            "about:blank"
        };

        std::string output_files[6];
        output_files[0] = LANG_JP_DATA_HIRAGANA;
        output_files[1] = LANG_JP_DATA_KATAKANA;
        output_files[2] = LANG_JP_DATA_KANJI;
        output_files[3] = LANG_JP_DATA_WORDS;
        output_files[4] = LANG_JP_DATA_GREETINGS;
        output_files[5] = LANG_JP_DATA_PHRASES;

        for (int i = 0; i < 6; i++) {

            files[i] = fopen((tmp_download_path + output_files[i]).c_str(), "wb");

            CURLcode res;

            curl_easy_setopt(curl[i], CURLOPT_FAILONERROR, 1);
            curl_easy_setopt(curl[i], CURLOPT_URL, urls[i].c_str());
            curl_easy_setopt(curl[i], CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl[i], CURLOPT_WRITEDATA, files[i]);
            curl_easy_setopt(curl[i], CURLOPT_TIMEOUT, curl_timeout_seconds);

            res = curl_easy_perform(curl[i]);
            curl_easy_cleanup(curl[i]);

            fclose(files[i]);

            std::ifstream anki_db_csv_input_file(tmp_download_path + output_files[i]);
            std::string line;
            ofstream anki_db_csv_output_file;
            anki_db_csv_output_file.open(category_data_path + output_files[i]);
            int current_line = 0;

            while (std::getline(anki_db_csv_input_file, line)) {

                if (current_line != 0) {
                    
                    std::vector<std::string> split_line = string_split(line, '|');
                    anki_db_csv_output_file << split_line[split_line.size() - 4][split_line[split_line.size() - 4].size()] << "|" << split_line[split_line.size() - 3] << "\n";
                }

                current_line++;
            }

            anki_db_csv_output_file.close();
        }
    }

    return 0;
}