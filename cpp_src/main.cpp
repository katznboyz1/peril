// main file that downloads all the available language trivia

#include "fetch_data_LANG_FR.hpp"

const std::string category_data_path = "../category_data/";

int main() {

    fetch_data_LANG_FR_all(category_data_path);

    return 0;
}