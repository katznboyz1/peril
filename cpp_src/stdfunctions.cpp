#include <stdio.h>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <iostream>

using namespace std;

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
            last_string = "";

        } else {

            last_string += str[i];
        }
    }

    return split_strings;
}

int randint(int min, int max) {

    int random_number;

    std::random_device rd;
    std::mt19937 rd_gen(rd());
    std::uniform_int_distribution<> rd_gen_dist(min, max);

    random_number = rd_gen_dist(rd_gen);

    return random_number;
}

// from https://stackoverflow.com/a/30338543
enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};
std::vector<std::string> readCSVRow(const std::string &row) {
    CSVState state = CSVState::UnquotedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}