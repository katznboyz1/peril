#include <string>

const std::string LANG_JP_DATA_HIRAGANA = "data.hiragana.lang.jp.txt"; // completed
const std::string LANG_JP_DATA_KATAKANA = "data.katakana.lang.jp.txt"; // completed
const std::string LANG_JP_DATA_KANJI = "data.kanji.lang.jp.txt"; // completed
const std::string LANG_JP_DATA_WORDS = "data.words.lang.jp.txt"; // completed
const std::string LANG_JP_DATA_SENTENCES = "data.sentences.lang.jp.txt"; // completed
const std::string LANG_JP_DATA_PHRASES = "data.phrases.lang.jp.txt"; // completed

int fetch_data_LANG_JP_all(const std::string &category_data_path, const std::string &tmp_download_path, const int &curl_timeout_seconds);