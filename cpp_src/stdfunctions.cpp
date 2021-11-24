#include <stdio.h>
#include <vector>
#include <string>

// from https://stackoverflow.com/a/1636415
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


std::vector<std::string> string_split(std::string str, char delimiter) {

    std::vector<std::string> split_strings;
    std::string last_string;

    for (int i = 0; i < str.size(); i++) {

        if (str[i] == delimiter) {

            split_strings.push_back(last_string);
        } else {

            last_string += str[i];
        }
    }

    return split_strings;
}