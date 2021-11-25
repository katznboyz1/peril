// main file that downloads all the available language trivia

#include <iostream>
#include <string>

#include "fetch_data_LANG_FR.hpp"
#include "fetch_data_LANG_JP.hpp"

using namespace std;

const std::string CATEGORY_DATA_PATH = "../category_data/";
const std::string TMP_DOWNLOAD_PATH = "/tmp/";

const int CURL_TIMEOUT_SECONDS = 5;

int main() {

    std::cout << "fetch_data_LANG_FR_all() = " << std::to_string(fetch_data_LANG_FR_all(CATEGORY_DATA_PATH, TMP_DOWNLOAD_PATH, CURL_TIMEOUT_SECONDS)) << endl;
    std::cout << "fetch_data_LANG_JP_all() = " << std::to_string(fetch_data_LANG_JP_all(CATEGORY_DATA_PATH, TMP_DOWNLOAD_PATH, CURL_TIMEOUT_SECONDS)) << endl;

    std::cout << "main() = 0" << endl;

    return 0;
}