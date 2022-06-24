#include "dictionary.h"

bool y0_word_card::dictionary::add_data_word_map(
    const std::string &word, const word_meta &meta)
{
  // already exist
  if (0 != this -> word_map_.count(word))
    return false;

  this -> word_map_[word] = meta;
  return true;
}

bool y0_word_card::dictionary::delete_data_word_map(
    const std::string &word)
{
  // data is nothing
  if (0 == this -> word_map_.count(word))
    return false;

  this -> word_map_.erase(word);
  return true;
}

const std::map<std::string, word_meta>
  y0_word_card::dictionary::get_word_map()
{
  return this -> word_map_;
}
