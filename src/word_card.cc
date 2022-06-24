#include "word_card.h"

y0_word_card::word_card::word_card()
{
  // today_date = get_today();
}

void y0_word_card::word_card::print_menu()
{
  std::system("clear");
  std::cout << "please input select number!!!!11!"  << '\n'
            << "1: study"                           << '\n'
            << "2: print all item"                  << '\n'
            << "3: add data"                        << '\n'
            << "4: delete data"                     << '\n'
            << "5: quit"                            << std::endl;
}

void y0_word_card::word_card::word_card_processing()
{
  read_xml_to_dictionary(data_file_path);

  while(1) {
    print_menu();
    int select_number = getch() - '1' + 1;
    std::cout << select_number << std::endl;
    if (STUDY > select_number || QUIT < select_number) {
      std::cout << "please folow menu." << std::endl;
      getch();
      continue;
    }
    if (QUIT == select_number)
      break;
    do_function(select_number);
  }
}

void y0_word_card::word_card::study_processing()
{
  date_struct  today_date  = get_today();
  unsigned int study_count = calc_number_of_study(today_date);
  study(today_date, study_count);
}

void y0_word_card::word_card::study(
    const date_struct &today_date, unsigned int &study_count)
{
  std::map<int, int> map_interval
    = { {1, 1}, {2, 2}, {3, 5}, {4, 7}, {5, 9} };
  std::map<int, int> map_interval_to_index
    = { {1, 1}, {2, 2}, {5, 3}, {7, 4}, {9, 5} };
  auto word_map = dictionary_.get_word_map();
  for (auto itr = word_map.begin();
      itr != word_map.end(); ++itr) {

    unsigned int difference_date_score
      = calc_difference_date_score(
          today_date,
          itr->second.year, itr->second.month, itr->second.date);

    if (difference_date_score > itr->second.interval)
      continue;

    std::system("clear");
    std::cout << study_count << std::endl;
    --study_count;
    std::cout << itr->first << std::endl;
    getchar();
    std::cout << itr->second.mean << std::endl;
    switch(gain_understand()) {
      case 'c':
        break;
      case 'y':
        if (itr->second.interval < map_interval.rbegin()->second)
          itr->second.interval
            = map_interval[map_interval_to_index[itr->second.interval] + 1];
        break;
      case 'n':
        if (map_interval.begin()->second < itr->second.interval)
          itr -> second.interval
            = map_interval[map_interval_to_index[itr->second.interval] - 1];
        break;
    }
  }
}

char y0_word_card::word_card::gain_understand ()
{
  while (1) {
    std::cout << "Do you understand? y/n/s/c" << std::endl;
    char understand = getch();
    if (understand == 'y' || understand == 'n'
        || understand == 's' || understand == 'c')
      return understand;
    std::cout << "please input y or n or s or c" << std::endl;
  } 
}

unsigned int y0_word_card::word_card::calc_difference_date_score(
    const date_struct &today_date,
    const int &year,
    const int &month,
    const int &date)
{
  return (today_date.year*365
      + today_date.month*12
      + today_date.date)
      -(year*365 + month*12 + date);
}

/*
 * what: calucrate number of study words
 */
unsigned int y0_word_card::word_card::calc_number_of_study(
    date_struct &today_date)
{
  auto word_map = dictionary_.get_word_map();
  unsigned int study_counter = 0;
  for (auto itr = word_map.begin (); itr != word_map.end (); ++itr) {
    unsigned int difference_date_score
      = calc_difference_date_score(
          today_date, itr->second.year, itr->second.month, itr->second.date);
    if (difference_date_score > itr->second.interval)
      continue;
    ++study_counter;
  }
  return study_counter;
}

void y0_word_card::word_card::do_function(const int &select_num)
{
  switch (select_num) {
    case STUDY:
      study_processing();
      write_dictionary_to_xml(data_file_path);
      std::cout << "finish" << '\n';
      break;

    case PRINT_ALL_ITEM:
      print_all_item();
      break;

    case ADD_DATA:
      add_processing();
      write_dictionary_to_xml(data_file_path);
      break;

    case DELETE_DATA:
      print_all_item();
      delete_processing();
      write_dictionary_to_xml(data_file_path);
      break;
  }
}

void y0_word_card::word_card::print_all_item()
{
  std::system("clear");
  auto word_map = dictionary_.get_word_map();
  for (auto itr = word_map.begin();
      itr != word_map.end(); ++itr) {
    std::cout << itr -> first << '\n'
      << itr -> second.mean << "\n\n";
  }
  puts ("");
  getch();
}

void y0_word_card::word_card::add_processing()
{
  date_struct today_date = get_today();
  std::string word, mean;
  std::cout
    << "please input add word and its mean. if you skip, pleae press enter."
    << "." << '\n';
  std::cout << "word: " << std::flush;
  getline (std::cin, word);

  if ("" == word)
    return;

  std::cout << "mean: ";
  getline (std::cin, mean);
  bool is_success = dictionary_.add_data_word_map(
      word,
      {
        mean,
        today_date.year,
        today_date.month,
        today_date.date,
        1
      }); // default interval

  if (!is_success)
    std::cout << word << "is already exist." << '\n';
  while (getchar() !=  '\n');
}

void y0_word_card::word_card::delete_processing ()
{
  std::string word;

  std::cout << "input delete word: " << '\n';
  getline(std::cin, word);
  std::cout << "realy delete " << word << "? y/n" << '\n';
  char c = getchar();
  if ('n' == c)
    return;
  bool is_delete = dictionary_.delete_data_word_map(word);
  std::cout << "word "
    << (is_delete ? "is deleted." : "does not exist. ") << '\n';
}

void y0_word_card::word_card::read_xml_to_dictionary(const std::string file_path)
{
  y0_word_card::operate_xml operate_xml;
  operate_xml.read(file_path, dictionary_);
}

void y0_word_card::word_card::write_dictionary_to_xml(const std::string file_path)
{
  y0_word_card::operate_xml operate_xml;
  operate_xml.write(file_path, get_today(), dictionary_);
}
