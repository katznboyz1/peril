#include <string>
#include <curl/curl.h>
#include <sqlite3.h>
#include <iostream>

#include "stdfunctions.hpp"

#include "fetch_data_LANG_JP.hpp"

using namespace std;

int fetch_data_LANG_JP_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds) {

    // forgive me

    CURL *curl_hiragana;
    CURL *curl_katakana;
    CURL *curl_kanji;
    CURL *curl_words;
    CURL *curl_greetings;
    CURL *curl_phrases;

    CURLcode res;

    std::string output_path_hiragana = tmp_download_path + "LANG_JP_1.zip";
    std::string output_path_katakana = tmp_download_path + "LANG_JP_2.zip";
    std::string output_path_kanji = tmp_download_path + "LANG_JP_3.zip";
    std::string output_path_words = tmp_download_path + "LANG_JP_4.zip";
    std::string output_path_greetings = tmp_download_path + "LANG_JP_5.zip";
    std::string output_path_phrases = tmp_download_path + "LANG_JP_6.zip";

    std::string output_path_hiragana_db = tmp_download_path + "LANG_JP_1.db";
    std::string output_path_katakana_db = tmp_download_path + "LANG_JP_2.db";
    std::string output_path_kanji_db = tmp_download_path + "LANG_JP_3.db";
    std::string output_path_words_db = tmp_download_path + "LANG_JP_4.db";
    std::string output_path_greetings_db = tmp_download_path + "LANG_JP_5.db";
    std::string output_path_phrases_db = tmp_download_path + "LANG_JP_6.db";

    char* output_path_hiragana_char = const_cast<char*>(output_path_hiragana.c_str());
    char* output_path_katakana_char = const_cast<char*>(output_path_katakana.c_str());
    char* output_path_kanji_char = const_cast<char*>(output_path_kanji.c_str());
    char* output_path_words_char = const_cast<char*>(output_path_words.c_str());
    char* output_path_greetings_char = const_cast<char*>(output_path_greetings.c_str());
    char* output_path_phrases_char = const_cast<char*>(output_path_phrases.c_str());

    char* output_path_hiragana_char_db = const_cast<char*>(output_path_hiragana_db.c_str());
    char* output_path_katakana_char_db = const_cast<char*>(output_path_katakana_db.c_str());
    char* output_path_kanji_char_db = const_cast<char*>(output_path_kanji_db.c_str());
    char* output_path_words_char_db = const_cast<char*>(output_path_words_db.c_str());
    char* output_path_greetings_char_db = const_cast<char*>(output_path_greetings_db.c_str());
    char* output_path_phrases_char_db = const_cast<char*>(output_path_phrases_db.c_str());

    curl_hiragana = curl_easy_init();
    curl_katakana = curl_easy_init();
    curl_kanji = curl_easy_init();
    curl_words = curl_easy_init();
    curl_greetings = curl_easy_init();
    curl_phrases = curl_easy_init();

    if (curl_hiragana && curl_katakana && curl_kanji && curl_words && curl_greetings && curl_phrases) {

        FILE *file_hiragana;
        FILE *file_katakana;
        FILE *file_kanji;
        FILE *file_words;
        FILE *file_greetings;
        FILE *file_phrases;

        // full credit to the author: https://ankiweb.net/shared/info/1552733819
        file_hiragana = fopen(output_path_hiragana_char, "wb");
        curl_easy_setopt(curl_hiragana, CURLOPT_FAILONERROR, 1);
        curl_easy_setopt(curl_hiragana, CURLOPT_URL, "https://dl5.ankiweb.net/shared/downloadDeck2/1552733819?k=WzE1NTI3MzM4MTksIDIzODEwLCAxNjMwNTYxOTU0XQ.ZARuox_JI2NSUp3tf-P-H-OWkFeXaajNlLAY9AlG5r8");
        curl_easy_setopt(curl_hiragana, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl_hiragana, CURLOPT_WRITEDATA, file_hiragana);
        curl_easy_setopt(curl_hiragana, CURLOPT_TIMEOUT, curl_timeout_seconds);
        res = curl_easy_perform(curl_hiragana);
        curl_easy_cleanup(curl_hiragana);
        if (res != CURLE_OK) return 1;

        // unzip the zip file we downloaded
        //unzip -p myarchive.zip path/to/zipped/file.txt >file.txt
        int status_hiragana = system(("unzip -p " + output_path_hiragana + " collection.anki2 > " + output_path_hiragana_db + " &").c_str());
        if (status_hiragana != 0) return 2;

        sqlite3* db_hiragana;
        int res_hiragana = sqlite3_open(output_path_hiragana_char_db, &db_hiragana);
        if (!res_hiragana) {

            // fetch the needed data

        } else return 3;
        sqlite3_close(db_hiragana);
    }

    return 0;
}