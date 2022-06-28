#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<iomanip>
#include <string>
#include<sstream>
#include"Utils.h"
#include"Item.h"
using namespace std;
namespace sdds
{
    bool Item::linear() const
    {
        return m_linear;
    }
    
    Item::Item()
    {
        m_price = 0.0;
        m_qty = 0;
        m_qtyNeeded = 0;
        m_desc = nullptr;
        m_linear = false;
        
    }
    
    Item::Item(const Item& I)
    {
        operator=(I);
    }
    
    Item& Item::operator=(const Item& I)
    {
        if(this != &I){
           if (I.m_desc != nullptr) {
              if (m_desc != nullptr) {
                 delete[] m_desc;
                 m_desc = nullptr;
              }
              m_price = I.m_price;
              m_qty = I.m_qty;
              m_qtyNeeded = I.m_qtyNeeded;
              m_desc = new char[strlen(I.m_desc) + 1];
              strcpy(m_desc, I.m_desc);
              m_state = I.m_state;
              m_sku = I.m_sku;
           }
        }
        return *this;
    }
    
    
    Item::~Item()
    {
        delete [] m_desc;
    }
    
    int Item::qtyNeeded() const
    {
        return m_qtyNeeded;
    }
    
    int Item::qty() const
    {
        return m_qty;
    }
    
    Item::operator double() const
    {
        return m_price;
    }
    
    Item::operator bool() const
    {
        return m_state && m_sku != 0;
    }
    
    int Item::operator-=(int qty)
    {
         m_qty -= qty;
         return m_qty;
    }
    
    int Item::operator+=(int qty)
    {
         m_qty += qty;
         return m_qty;
    }

    void Item::linear(bool isLinear)
    {
        m_linear = isLinear;        
    }
    
    void Item::clear()
    {
        m_price = 0.0;
        m_qty = 0;
        m_qtyNeeded = 0;
        delete [] m_desc;
        m_desc = nullptr;
        m_linear = false;
        m_state = nullptr;
        m_sku = 0;
    }
    
    bool Item::operator==(int sku) const
    {
        return m_sku == sku;
    }
    
    bool Item::operator==(const char* description) const
    {
        return strstr(m_desc,description);
    }
    
    std::ofstream& Item::save(std::ofstream& ofstr) 
    {
       if (m_linear == false) {
          ofstr << m_sku << '\t' << m_desc << '\t' << m_qty << '\t' << m_qtyNeeded << '\t' << fixed << setprecision(2) << m_price;
       }
       else {
          ofstr.width(5);
          ofstr << m_sku << " | ";
          int i = 0;
          if (m_desc != nullptr) {
             for (i = 0; i < 35; i++) {

                if (m_desc[i] == '\0') {
                   break;
                }
                else {
                   ofstr << m_desc[i];
                }
             }
          }
          while (i < 35) {
             ofstr << " ";
             i++;
          }

          ofstr << " | ";
          ofstr.fill(' ');
          ofstr.setf(ios::right);
          ofstr.width(4);
          ofstr << m_qty << " | ";
          ofstr.unsetf(ios::right);
          ofstr.setf(ios::right);
          ofstr.width(4);
          ofstr << m_qtyNeeded << " | ";
          ofstr.unsetf(ios::right);
          ofstr.setf(ios::right);
          ofstr.width(7);
          ofstr << fixed << setprecision(2) << m_price << " |";
       }
        return ofstr;
    }
    
    std::ifstream& Item::load(std::ifstream& ifstr)
    {
        delete [] m_desc;
        m_desc = nullptr;
        string desc;

        ifstr >> m_sku;
        ifstr.ignore(10000,'\t');
        getline(ifstr, desc, '\t');
        ifstr >> m_qty;
        ifstr.ignore(10000,'\t');
        ifstr >> m_qtyNeeded;
        ifstr.ignore(10000,'\t');
        ifstr >> m_price;
        ifstr.ignore();
        if (ifstr.bad()) {
           m_state = "Input file stream read failed!";
        }
        
        ut.alocpy(m_desc, desc.c_str());
        return ifstr;

    }
    
    std::ostream& Item::display(std::ostream& ostr) const
    {
        if(!m_state){
            ostr<<m_state;
        }
        else{
           if (m_desc != nullptr) {
              if (m_linear) {
                 ostr.width(5);
                 ostr << m_sku << " | ";
                 int i = 0;
                 if (m_desc != nullptr) {
                    for (i = 0; i < 35; i++) {

                       if (m_desc[i] == '\0') {
                          break;
                       }
                       else {
                          cout << m_desc[i];
                       }
                    }
                 }
                 while (i < 35) {
                    cout << " ";
                    i++;
                 }

                 ostr << " | ";
                 ostr.fill(' ');
                 ostr.setf(ios::right);
                 ostr.width(4);
                 ostr << m_qty << " | ";
                 ostr.unsetf(ios::right);
                 ostr.setf(ios::right);
                 ostr.width(4);
                 ostr << m_qtyNeeded << " | ";
                 ostr.unsetf(ios::right);
                 ostr.setf(ios::right);
                 ostr.width(7);
                 ostr << fixed << setprecision(2) << m_price << " |";
              }
              else {
                 ostr << "AMA Item:" << endl;
                 ostr << m_sku << ": " << m_desc << endl;
                 ostr << "Quantity Needed: " << m_qtyNeeded << endl;
                 ostr << "Quantity Available: " << m_qty << endl;
                 ostr << "Unit Price: $" << m_price << endl;
                 ostr << "Needed Purchase Fund: $" << fixed << setprecision(2) << m_price * (m_qtyNeeded - m_qty) << endl;
              }
           }
        }
        return ostr;
    }
    
    
    int Item::readSku(std::istream& istr)
    {
        int sku;
        sku = ut.getint(40000,99999,"SKU: ");
        m_sku = sku;
        return sku;
    }

    std::istream& Item::read(std::istream& istr)
    {
        string desc;
        cout << "AMA Item:" << endl;
        cout << "SKU: " << m_sku << endl;
        cout << "Description: ";
        getline(istr, desc);
        m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
        m_price = ut.getdouble(0.00, 9999.00, "Unit Price: $");
        if(!istr){
           m_state = "Console entry failed!";
        }
        ut.alocpy(m_desc, desc.c_str());
        return istr;
    }

    const char* Item::descVal()const {
       return m_desc;
    }

    int Item::getSKU()const {
       return m_sku;
    }

    void Item::setSku(int sku) {
       m_sku = sku;
    }
}