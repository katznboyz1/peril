#include <stdio.h>
#include <vector>
#include <string>

// from https://stackoverflow.com/a/1636415
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

std::vector<std::string> string_split(std::string str, char delimiter);