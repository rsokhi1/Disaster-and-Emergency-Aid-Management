#ifndef SDDS_DATE_H_
#define SDDS_DATE_H_
#include<iostream>
#include "Status.h"
namespace sdds {
   const int m_currYear = 2022;
   const int max_year = 2030;


   class Date {
      int m_year{};
      int m_month{};
      int m_day{};
      Status m_state{};
      bool m_formatted{};
      
      bool validate(int year, int mon, int day);
      int uniqueInt() const;

   public:
      Date();
      Date(int year, int month, int day);
      Date& operator=(const Date& D);
      bool operator==(const Date& D) const;
      bool operator!=(const Date& D) const;
      bool operator<(const Date& D) const;
      bool operator>(const Date& D) const;
      bool operator<=(const Date& D) const;
      bool operator>=(const Date& D) const;
      void format(bool flag);
      const Status state();
      bool formatted(bool flag);
      operator bool() const;
      std::istream& read(std::istream& istr);
      std::ostream& write(std::ostream& ostr) const;
   };

   std::ostream& operator<<(std::ostream& ostr, const Date& D);
   std::istream& operator>>(std::istream& istr, Date& D);
}


#endif // !SDDS_DATE_H_
