#ifndef SRC_WORD_CARD_H
#define SRC_WORD_CARD_H

#include <map>
#include <iostream>
#include <string>

#include "dictionary.h"
#include "date_struct.h"
#include "get_today.h"
#include "operate_xml.h"
#include "../util/y0_conio.h"

namespace y0_word_card
{
  class word_card
  {
    private:
      // value
      enum {
        DUMY,
        STUDY,
        PRINT_ALL_ITEM,
        ADD_DATA,
        DELETE_DATA,
        QUIT,
        FUNCTION_MAX
      };

      // data_struct today_date_;
      y0_word_card::dictionary dictionary_;

      const std::string data_file_path = "/Users/y0_/prog/study/data/data.xml";

      // function
      void print_menu();
      void do_function(const int &);
      void study_processing();
      void study(const date_struct &, unsigned int &);
      void print_all_item();
      void add_processing();
      void delete_processing();
      void read_xml_to_dictionary(const std::string);
      void write_dictionary_to_xml(const std::string);
      unsigned int calc_number_of_study(date_struct &);
      unsigned int calc_difference_date_score(
          const date_struct &, const int &, const int &, const int &);
      char gain_understand();
    public:
      // function
      word_card();
      void word_card_processing();
  };
} // namespace y0_word_card

#endif
