#ifndef SRC_OPERATE_XML_H
#define SRC_OPERATE_XML_H

#include <iostream>
#include <regex>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "date_struct.h"
#include "dictionary.h"
#include "word_meta.h"

namespace y0_word_card
{
  class operate_xml
  {
    private:
      // value
      /*tag name for xml*/
      const std::string kitem_construction_       = "root.info.item";
      const std::string kdata_construction_       = "root.info.item.data";
      //const std::string id_constraction_         = data_construction_ + ".id";
      const std::string kword_constraction_       = "word";
      const std::string kmean_constraction_       = "mean";
      const std::string klast_answered_date_root_ = "last-date";
      const std::string klast_answered_year_      = klast_answered_date_root_ + ".<xmlattr>.year";
      const std::string klast_answered_month_     = klast_answered_date_root_ + ".<xmlattr>.month";
      const std::string klast_answered_date_      = klast_answered_date_root_ + ".<xmlattr>.day";
      const std::string kinterval_                = "interval";

      // function
      std::string replace_newline_char_for_write(std::string mean);

    public:
      // function
      int read(const std::string, y0_word_card::dictionary &);
      int write(
          const std::string,
          const date_struct &,
          y0_word_card::dictionary &);
  };
} // namespace y0_word_card
#endif
