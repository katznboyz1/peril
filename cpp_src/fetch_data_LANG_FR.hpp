#include <string>

// this should not be a relative or absolute path, it should just be the filename of the output file
// should be in the format "data.CATEGORY_NAME.lang.LANGUAGE_CODE"
const std::string LANG_FR_DATA_VOCAB_NOUNS = "data.vocab_nouns.lang.fr.txt"; // completed
const std::string LANG_FR_DATA_VOCAB_ADJECTIVES = "data.vocab_adjectives.lang.fr.txt"; // completed
const std::string LANG_FR_DATA_PHRASES = "data.phrases.lang.fr.txt";
const std::string LANG_FR_DATA_VERB_CONJUGATIONS = "data.verb_conjugations.lang.fr.txt"; // completed
const std::string LANG_FR_DATA_VERB_VOCABULARY = "data.verb_vocabulary.lang.fr.txt"; // completed
const std::string LANG_FR_DATA_CONVERSATION_PROMPTS = "data.conversation_prompts.lang.fr.txt";

// should return 0 if it is successful
int fetch_data_LANG_FR_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds);