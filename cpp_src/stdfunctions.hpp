#include <stdio.h>
#include <vector>
#include <string>
#include <random>

// from https://stackoverflow.com/a/1636415
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

std::vector<std::string> string_split(std::string str, char delimiter);

int randint(int max, int min);

std::vector<std::string> readCSVRow(const std::string &row);