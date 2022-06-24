#include "operate_xml.h"

int y0_word_card::operate_xml::read(
    const std::string filename, y0_word_card::dictionary &dictionary)
{
  using ptree = boost::property_tree::ptree;

  try {
    std::string data_map_key;
    std::string word_replaced;
    std::string mean_replaced;
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(filename, pt);

    BOOST_FOREACH(
        const ptree::value_type& child,
        pt.get_child(kitem_construction_)) {//"root.item")) {
      auto [tag, data] = child;

      if (boost::optional<std::string> word_get
          = data.get_optional<std::string>("word")) {
        word_replaced = word_get.get();
      }

      if (boost::optional<std::string> mean_get
          = data.get_optional<std::string>("mean")) {
        mean_replaced = mean_get.get();
      }

      dictionary.add_data_word_map(
          word_replaced,
          {
            mean_replaced,
            data.get<int>(klast_answered_year_),
            data.get<int>(klast_answered_month_),
            data.get<int>(klast_answered_date_),
            data.get<int>(kinterval_)
          });
    }
  }
  catch (boost::property_tree::xml_parser_error& e) {
    std::wcout << L"ERROR : " << e.what() << std::endl;
    return 1;
  }
  catch (boost::property_tree::ptree_bad_path& e) {
    std::wcout << L"ERROR : " << e.what() << std::endl;
    return 1;
  }
  catch (...) {
    std::wcout << L"ERROR : unknown error::" << __FILE__ << "::" << __LINE__ << std::endl;
    return 2;
  }
  return 0;
}

std::string y0_word_card::operate_xml::replace_newline_char_for_write(std::string mean)
{
  std::string result;
  std::regex re(R"(\n)");
  result = std::regex_replace(mean, re, "//n");

  return result;
}

int y0_word_card::operate_xml::write(
    const std::string filename,
    const date_struct &today_date,
    y0_word_card::dictionary &dictionary)
{
  try {
    const int indent = 2;
    boost::property_tree::ptree pt;
    std::string word_replaced;
    std::string mean_replaced;

    auto word_map = dictionary.get_word_map();

    for (auto itr = word_map.begin (); itr != word_map.end(); ++itr) {
      boost::property_tree::ptree& child = pt.add(kdata_construction_, "");

      word_replaced = replace_newline_char_for_write(itr->first);
      child.add(kword_constraction_, word_replaced);

      mean_replaced = replace_newline_char_for_write(itr->second.mean);
      child.add(kmean_constraction_, mean_replaced);

      child.add(klast_answered_year_,  today_date.year);
      child.add(klast_answered_month_, today_date.month);
      child.add(klast_answered_date_,  today_date.date);

      child.add(kinterval_, itr -> second.interval);
    }

    boost::property_tree::write_xml(filename, pt, std::locale(),
        boost::property_tree::xml_writer_make_settings<std::string>(' ', indent));

  }
  catch (boost::property_tree::xml_parser_error& e) {
    std::wcout << L"ERROR : " << e.what() << std::endl;
    return 1;
  }
  catch (...) {
    std::wcout << L"ERROR : unknown error::" << __FILE__ << "::" << __LINE__ << std::endl;
    return 2;
  }
  return 0;
}

