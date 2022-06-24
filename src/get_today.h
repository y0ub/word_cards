/*
 * get today year, month and date
 */
#ifndef _GET_TODAY
#define _GET_TODAY

#include <iomanip>
#include <sstream>

#include "date_struct.h"

/*struct date_struct {
  int year;
  int month;
  int date;
};*/

inline date_struct get_today()
{
  time_t t = time(nullptr);
  const tm* localTime = localtime(&t);
  date_struct today_date;

  today_date.year  = localTime -> tm_year - 100;
  today_date.month = localTime -> tm_mon + 1;
  today_date.date  = localTime -> tm_mday;
  return today_date;
}

#endif
