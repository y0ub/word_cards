#ifndef SRC_WORD_META_H
#define SRC_WORD_META_H

struct word_meta
{
  std::string mean;

  // last access date
  int year;
  int month;
  int date;

  int interval;
};

#endif
