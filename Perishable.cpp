#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Utils.h"
#include "Perishable.h"
using namespace std;

namespace sdds {
   Perishable::Perishable() {
      m_instructions = nullptr;
   }

   Perishable::Perishable(const Perishable& P){
      *this = P;
   }

   Perishable& Perishable::operator=(const Perishable& P) {
      if (this != &P) {
            if (m_instructions != nullptr) {
               delete[] m_instructions;
               m_instructions = nullptr;
            }
            if (P.m_instructions != nullptr) {
               m_instructions = new char[strlen(P.m_instructions) + 1];
               strcpy(m_instructions, P.m_instructions);
            }
            m_expiry = P.m_expiry;
            Item::operator=(P);
           
      }
      return *this;
   }

   Perishable::~Perishable() {
      delete[] m_instructions;
      m_instructions = nullptr;
   }

   const Date& Perishable::expiry()const {
      return m_expiry;
   }

   int Perishable::readSku(istream& is) {
      m_sku = ut.getint(10000, 39999, "SKU: ");
      return m_sku;
   }

   ofstream& Perishable::save(ofstream& ofstr) {
      if (Item::operator bool()) {
         if (!Item::linear()) {
            Item::save(ofstr);
            ofstr << "\t";
            if (m_instructions != nullptr) {
               ofstr << m_instructions;
            }
            ofstr << "\t";
            m_expiry.formatted(false);
            ofstr << m_expiry;
         }
         else {
            Item::save(ofstr);
            if (m_instructions != nullptr) {
               if (m_instructions[0] != '\0') {
                  ofstr << "*";
               }
               else {
                  ofstr << " ";
               }
            }
            else {
               ofstr << " ";
            }
            ofstr << m_expiry;

         }
      }
      return ofstr;
   }

   ifstream& Perishable::load(ifstream& ifstr) {
      Item::load(ifstr);
      string instruction{};
      getline(ifstr, instruction, '\t');
      ifstr >> m_expiry;
      ifstr.ignore(10000, '\n');
      ifstr.clear();
      if (ifstr.bad()){
         m_state = "Input file stream read (perishable) failed!";
         ifstr.clear();
      }
      ut.alocpy(m_instructions, instruction.c_str());
      return ifstr;
   }

   ostream& Perishable::display(ostream& ostr)const {
      if (Item::m_sku != 0) {
         if (!Item::operator bool()) {
            ostr << m_state;
         }
         else if (Item::linear()) {
            Item::display(ostr);
            
            if (m_instructions != nullptr) {
               if (m_instructions[0] != '\0') {
                  ostr << "*";
               }
	       else {
                  ostr << " ";
               }
            }
            else {
               ostr << " ";
            }
            

            ostr << m_expiry;
         }
         else {
            ostr << "Perishable ";
            Item::display(ostr);
            ostr << "Expiry date: ";
            ostr << m_expiry;
            if (m_instructions != nullptr) {
               if (m_instructions[0] != '\0') {
                  ostr << "\nHandling Instructions: " << m_instructions;
               }
            }
            ostr << endl;
         }
      }
      return ostr;
   }

   istream& Perishable::read(istream& istr) {
      Item::read(istr);
      if (m_instructions) {
         delete[] m_instructions;
         m_instructions = nullptr;
      }
      string instructions;
      cout << "Expiry date (YYMMDD): ";
      istr >> m_expiry;
      istr.ignore(10000, '\n');
      m_expiry.formatted(true);
      cout << "Handling Instructions, ENTER to skip: ";
      if (istr.peek() != '\n') {
         getline(istr,instructions);
         ut.alocpy(m_instructions, instructions.c_str());
      }
      else {
         istr.ignore();
         m_instructions = nullptr;
      }
      if (istr.fail()) {
         m_state = "Perishable console date entry failed!";
      }
      return istr;
   }

   int Perishable::getSKU()const {
      return Item::m_sku;
   }

   void Perishable::setSku(int sku) {
      Item::m_sku = sku;
   }

}