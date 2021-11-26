#include <string>
#include <curl/curl.h>
#include <iostream>
#include <fstream>

#include "stdfunctions.hpp"

#include "fetch_data_LANG_JP.hpp"

using namespace std;

int fetch_data_LANG_JP_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds) {

    CURL *curl[6];
    for (int i = 0; i < 6; i++) curl[i] = curl_easy_init();

    bool curl_init_was_success = true;
    for (int i = 0; i < 6; i++) curl_init_was_success = (curl_init_was_success && curl[i]);

    if (curl_init_was_success) {

        FILE *files[6];

        std::string urls[6] = {
            "https://gist.githubusercontent.com/katznboyz1/9c679680ca7e661a5bc6ae8fc2062bc9/raw/af616a91e36a0fef9e62115a49aa63c6a6c5268b/anki-1552733819.csv",
            "https://gist.githubusercontent.com/katznboyz1/8d4ed9d8b7fa43f20a1eef97db88de32/raw/652294fad46d48e24967250fe9eec945edc2c20f/anki-1770270429.csv",
            "https://gist.githubusercontent.com/katznboyz1/a413cb17bcd033c7c955166d60afd781/raw/0a42632ef54808d25f11d63cea1789fa6b94234c/anki-1142282583.csv",
            "https://gist.githubusercontent.com/katznboyz1/9255cdb41fd633d97295c1507a422855/raw/8ef8c34d3c9e49134ce6d42cdf784a7b9ec3b911/anki-2003963453.csv",
            "https://gist.githubusercontent.com/katznboyz1/9df4206c3797dfb404f1b69515f74f43/raw/c78288dc41f9caf89d18a00b6eddf295bbf9d8e3/anki-1604798747.csv",
            "https://gist.githubusercontent.com/katznboyz1/d495c5f6a8807ef9355972db455e6b02/raw/0a4fddbf50d03effe3c00a37f9c2b73db055c874/anki-4625398.csv"
        };

        std::string output_files[6];
        output_files[0] = LANG_JP_DATA_HIRAGANA;
        output_files[1] = LANG_JP_DATA_KATAKANA;
        output_files[2] = LANG_JP_DATA_KANJI;
        output_files[3] = LANG_JP_DATA_WORDS;
        output_files[4] = LANG_JP_DATA_SENTENCES;
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

                    std::string newline = "\n";
                    
                    if (i == 0 || i == 1) {

                        std::vector<std::string> split_line = readCSVRow(line);

                        if (i == 0) anki_db_csv_output_file << split_line[split_line.size() - 5] << "|" << split_line[split_line.size() - 4] << newline;
                        if (i == 1) anki_db_csv_output_file << split_line[split_line.size() - 4] << "|" << split_line[split_line.size() - 5] << newline;

                    } else if (i == 2 || i == 3 || i == 4 || i == 5) {

                        std::vector<std::string> split_line = readCSVRow(line);
                        std::string answer;
                        if (i == 2) answer = string_split(split_line[split_line.size() - 5], '\037')[3];
                        if (i == 3 || i == 5) answer = string_split(split_line[split_line.size() - 5], '|')[1];
                        if (i == 4) answer = string_split(split_line[split_line.size() - 5], '\037')[1];

                        if (i == 2) anki_db_csv_output_file << split_line[split_line.size() - 4] << "|" << answer << newline;
                        if (i == 3 || i == 5 || i == 4) anki_db_csv_output_file << answer << "|" << split_line[split_line.size() - 4] << newline;
                    }
                }

                current_line++;
            }

            anki_db_csv_output_file.close();

            remove((tmp_download_path + output_files[i]).c_str());
        }
    }

    return 0;
}