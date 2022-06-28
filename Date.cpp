#include<iomanip>
#include <ctime>
#include "Utils.h"
#include"Date.h"
using namespace std;
namespace sdds {
   bool Date::validate(int year, int mon, int day) {
      bool flag = true;
      if (year < 0 && mon < 0 && day < 0) {
         m_state = "Invalid date value";
         m_state = 0;
         flag = false;
      }
      else if (year < m_currYear || year > max_year) {
         m_state = "Invalid year in date";
         m_state = 1;
         flag = false;
      }
      else if (mon < 1|| mon > 12) {
         m_state = "Invalid month in date";
         m_state = 2;
         flag = false;
      }
      else if (day < 1 || day > 31) {
         m_state = "Invalid day in date";
         m_state = 3;
         flag = false;
      }
      else if (year % 4 != 0) {
         if (mon == 2 && day > 28) {
            m_state = "Invalid day in date";
            m_state = 3;
            flag = false;
         }
      }
      else {
         m_state.clear();
      }
      return flag;
   }

   int Date::uniqueInt() const {
      return m_year * 372 + m_month * 31 + m_day;
   }

   Date::Date() {
      ut.getSystemDate(&m_year, &m_month, &m_day);
      m_formatted = true;
   }

   Date::Date(int year, int mon, int day) {
      if (validate(year, mon, day)) {
         m_year = year;
         m_month = mon;
         m_day = day;
         m_formatted = true;
      }
   }

   void Date::format(bool flag) {
      m_formatted = flag;
   }

   bool Date::operator==(const Date& D) const {
      return this->uniqueInt() == D.uniqueInt();
   }

   bool Date::operator!=(const Date& D) const {
      return this->uniqueInt() != D.uniqueInt();
   }

   bool Date::operator<(const Date& D) const {
      return this->uniqueInt() < D.uniqueInt();
   }
   
   bool Date::operator>(const Date& D) const {
      return this->uniqueInt() > D.uniqueInt();
   }

   bool Date::operator<=(const Date& D) const {
      return this->uniqueInt() <= D.uniqueInt();
   }

   bool Date::operator>=(const Date& D) const {
      return this->uniqueInt() >= D.uniqueInt();
   }

   const Status Date::state() {
      return m_state;
   }

   bool Date::formatted(bool flag) {
      m_formatted = flag;
      return *this;
   }

   Date::operator bool()const {
      return m_state;
   }

   std::ostream& Date::write(std::ostream& ostr) const {
      if (m_formatted) {
         ostr.fill('0');
         ostr << m_year << "/";
         ostr.width(2);
         ostr << m_month << "/";
         ostr.width(2);
         ostr << m_day;
      }
      else {
         ostr.fill('0');
         ostr << m_year % 100;
         ostr.width(2);
         ostr << m_month;
         ostr.width(2);
         ostr << m_day;
      }
      return ostr;
   }

   std::istream& Date::read(std::istream& istr) {
      int value = 0;
      Utils test;
      istr >> value;

      if (value <= 0) {
         m_year = -1;
         m_month = -1;
         m_day = -1;
      }

      if (value <= 999999 && value > 99999) {
         m_year = value / 10000;
         m_month = (value - (m_year * 10000)) / 100;
         m_day= (value - (m_year * 10000)) % 100;
         m_year += 2000;
         

      }
      else if (value <= 9999 && value > 999) {
         ut.getSystemDate(&m_year, &m_month, &m_day);
         m_month = value / 100;
         m_day = value - (m_month * 100);
      }
      else if (value > 0 && value <= 999) {
         ut.getSystemDate(&m_year, &m_month, &m_day);
         m_month = value / 100;
         m_day = value - (m_month * 100);
      }

      if (validate(m_year, m_month, m_day) == false) {
         istr.setstate(ios::badbit);
      }
      return istr;
   }

   std::ostream& operator<<(std::ostream& ostr, const Date& D) {
      D.write(ostr);
      return ostr;
   }
   std::istream& operator>>(std::istream& istr, Date& D) {
      D.read(istr);
      return istr;
   }


   Date& Date::operator=(const Date& D) {
      if (D.m_day != 0) {
         m_day = D.m_day;
         m_month = D.m_month;
         m_year = D.m_year;
         m_formatted = true;
      }
      return *this;
   }

}