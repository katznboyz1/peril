// main file that downloads all the available language trivia

#include <iostream>
#include <string>

#include "fetch_data_LANG_FR.hpp"

using namespace std;

const std::string CATEGORY_DATA_PATH = "../category_data/";
const std::string TMP_DOWNLOAD_PATH = "/tmp/";

int main() {

    std::cout << "fetch_data_LANG_FR_all() = " << std::to_string(fetch_data_LANG_FR_all(CATEGORY_DATA_PATH, TMP_DOWNLOAD_PATH)) << endl;

    std::cout << "0" << endl;

    return 0;
}