#include <stdio.h>
#include <vector>
#include <string>
#include <random>
#include <zip.h>

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

// from https://stackoverflow.com/a/10440251
std::string unzip_and_get_file(const char *file_to_unzip, const char *file_to_search_for) {

    //Open the ZIP archive
    int err = 0;
    zip *z = zip_open(file_to_unzip, 0, &err);

    //Search for the file of given name
    const char *name = file_to_search_for;
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, name, 0, &st);

    //Alloc memory for its uncompressed contents
    char *contents = new char[st.size];

    //Read the compressed file
    zip_file *f = zip_fopen(z, "file.txt", 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);

    std::string output(contents);

    return output;
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