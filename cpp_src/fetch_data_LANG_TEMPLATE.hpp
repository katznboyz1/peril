#include <string>

/*
    Should have a bunch of `const std::string` variables for the different paths used by this language
    Each path should be in the format `data.CATEGORY_NAME.lang.LANGUAGE_CODE.txt`
    The file must be a `.txt` file, and it should not include any slashes so that the fetch_data_LANG_XXX_all function can handle the placement
*/
const std::string LANG_TEMPLATE_DATA_EXAMPLE = "data.example.lang.template.txt";

/*
    Should return 0 if it is successful, and should return >0 if it is not successful
    Inside this function, all of the language data downloading should happen
    Make sure to ONLY use the LANG_XXX variables made in THIS file - you should not be modifying other languages' data!
*/
int fetch_data_LANG_TEMPLATE_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds);