#ifndef SRC_DICTIONARY
#define SRC_DICTIONARY

#include <map>
#include <string>

#include "word_meta.h"

namespace y0_word_card
{
  class dictionary
  {
    private:
      std::map<std::string, word_meta> word_map_;

    public:
      bool add_data_word_map(const std::string &, const word_meta &);
      bool delete_data_word_map(const std::string &);
      const std::map<std::string, word_meta>
        get_word_map();
  };
} // namespace y0_word_card

#endif
