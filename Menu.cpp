#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds
{

   Menu::Menu(unsigned int numOptions, const char* content)
   {
      if (numOptions >= 0 && numOptions <= 15 && content != nullptr)
      {
         this->m_numOptions = numOptions;
         if (m_content != nullptr) {
            delete[] this->m_content;
         }
         this->m_content = new char[strlen(content) + 1];
         strcpy(this->m_content, content);
      }
      else {
         m_content = nullptr;
         m_numOptions = 0;
      }
   }

   Menu::Menu(const Menu& mu)
   {
      *this = mu;
   }

   Menu& Menu::operator=(const Menu& mu)
   {
      if (this != &mu && mu.m_content != nullptr)
      {
         delete[] m_content;
         this->m_content = nullptr;
         this->m_content = new char[strlen(mu.m_content) + 1];
         strcpy(this->m_content, mu.m_content);
         this->m_numOptions = mu.m_numOptions;
      }
      return *this;
   }


   Menu::~Menu()
   {
      if (m_content != NULL) {
         delete[] m_content;
      }
   }

   int Menu::run()const
   {
      cout << m_content;
      cout << "0- Exit" << endl;
      cout << "> ";
      unsigned int choice = 0;
      choice = ut.getint(0, m_numOptions);
      return choice;
   }

   Menu& Menu::operator=(const char* menu) {
      if (menu != nullptr) {
         if (m_content != nullptr) {
            delete[] m_content;
         }
         m_content = new char[strlen(menu) + 1];
         strcpy(m_content, menu);
      }
      return *this;
   }

   Menu& Menu::operator=(int opt) {
      if (opt != 0) {
         m_numOptions = opt;
      }
      return *this;
   }


}