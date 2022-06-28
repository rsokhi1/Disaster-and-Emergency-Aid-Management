#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include"Status.h"
using namespace std; 
namespace sdds
{
    Status::Status(const char* desc)
    {
        if(desc != nullptr){
           delete[] m_desc;
            m_desc = new char(strlen(desc) + 1);
            strcpy(m_desc, desc);
        }
        else{
            m_desc = nullptr;
        }
        m_statusCode = 0;
    }
    
    Status::Status(const Status &S)
    {
        if (S.m_desc != nullptr) {
            delete[] m_desc;
            m_desc = new char[strlen(S.m_desc) + 1];
            strcpy(m_desc, S.m_desc);
            m_statusCode = S.m_statusCode;
        }
        else {
            m_desc = nullptr;
        }
    }
    
    Status& Status::operator=(const Status& S)
    {
        if(this != &S && S.m_desc != nullptr){
            delete [] m_desc;
            m_desc = nullptr;
            m_desc = new char[strlen(S.m_desc) + 1];
            strcpy(m_desc,S.m_desc);
            m_statusCode = S.m_statusCode;
        }
        return *this;
    }
    
    Status& Status::operator=(int statusCode)
    {
        m_statusCode = statusCode;
        return *this;
    }
    
    Status& Status::operator=(const char* desc)
    {
       if (desc != nullptr) {
          delete[] m_desc;
          m_desc = nullptr;
          m_desc = new char[strlen(desc) + 1];
          strcpy(m_desc, desc);
       }
       else {
          m_desc = nullptr;
       }
      
         return *this;
    }
    
    Status::~Status()
    {
        delete [] m_desc;
        m_desc = nullptr;
    }
    
    Status::operator int() const
    {
        return m_statusCode;
    }
    
    Status::operator const char*() const
    {
        return m_desc;
    }
    
    Status::operator bool() const
    {
        return m_desc == nullptr;  
    }
    
    Status& Status::clear()
    {
        delete [] m_desc;
        m_desc = nullptr;
        m_statusCode = 0;
        return *this;
    }
    
    ostream& Status::display(ostream& ostr) const
    {
       if (m_statusCode != 0) {

          ostr << "ERR#" << m_statusCode << ": " << m_desc;

       }
       else {

          ostr << m_desc;

       }

       return ostr;
    }
    
   std::ostream& operator<<(std::ostream& ostr,const Status& S){
      if (S.operator bool() == false) {
         S.display(ostr);
      }
      return ostr;
   }



    
}