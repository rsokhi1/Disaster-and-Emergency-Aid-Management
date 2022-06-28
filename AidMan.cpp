#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include "Utils.h"
#include "Perishable.h"
#include "Item.h"
#include "Date.h"
#include "AidMan.h"
using namespace std;

namespace sdds
{

   AidMan::AidMan()
   {
      m_filename = nullptr;
      m_menu = 7;
      m_menu = "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n";
      m_noOfProd = 0;
      m_products[0] = NULL;

   }

   AidMan::~AidMan()
   {
      save();
      deallocate();
   }

   unsigned int AidMan::menu() const
   {
      Date date{};
      cout << "Aid Management System\n";
      cout << "Date: " << date << endl;
      cout << "Data file: ";
      if (m_filename == nullptr)
      {
         cout << "No file" << endl;
      }
      else {
         cout << m_filename << endl;
      }
      cout << "---------------------------------\n";


      return m_menu.run();
   }


   void AidMan::run()
   {
      unsigned int choice = -1;
      do {
         choice = menu();
         if (choice != 0 && m_filename == nullptr && choice != 7) {
            choice = 7;
         }
         if (choice == 1) {
            cout << "\n****List Items****\n";
            int count = list();
            int row = 0;
            if (count != 0) {
               cout << "Enter row number to display details or <ENTER> to continue:" << endl;
               cout << "> ";
            }
            if (cin.peek() != '\n') {
               cin >> row;
            }
            else {
               cin.ignore();
               cout << endl;
            }
            if (row != 0) {
               m_products[row - 1]->linear(false);
               cout << *m_products[row - 1] << endl << endl;
            }
         }
         else if (choice == 2) {
            cout << "\n****Add Item****\n";
            addItem();
            cout << endl;
         }
         else if (choice == 3) {
            cout << "\n****Remove Item****\n";
            removeItem();
         }
         else if (choice == 4) {
            cout << "\n****Update Quantity****\n";
            updateQuantity();
         }
         else if (choice == 5) {
            cout << "\n****Sort****\n";
            sort();
         }
         else if (choice == 6) {
            cout << "\n****Ship Items****\n";
            shipItems();
         }
         else if (choice == 7) {
            cout << "\n****New/Open Aid Database****\n";
            load();
         }
      } while (choice != 0);
      cout << "Exiting Program!\n";
   }


   void AidMan::save() {
      if (m_filename != nullptr) {
         ofstream file(m_filename);
         if (file.is_open()) {
            for (int i = 0; i < m_noOfProd; i++) {
               m_products[i]->linear(false);
               m_products[i]->save(file);
               file << endl;
            }
         }
         file.close();
      }

   }

   void AidMan::deallocate() {
      for (int i = 0; i < m_noOfProd; i++) {
         delete m_products[i];
      }
      delete[] m_filename;
      m_noOfProd = 0;
   }

   bool AidMan::load() {
      save();
      deallocate();
      string filename;

      cout << "Enter file name: ";
      cin >> filename;
      m_filename = new char[strlen(filename.c_str()) + 1];
      strcpy(m_filename, filename.c_str());
      ifstream file(m_filename);
      if (!file.is_open()) {
         int selection = 0;
         cout << "Failed to open " << m_filename << " for reading!" << endl;
         cout << "Would you llike to create a new data file?" << endl;
         cout << "1- Yes!" << endl;
         cout << "0- Exit\n>";
         cin >> selection;
         if (selection == 1) {
            ofstream fptr(m_filename);
            fptr.close();
         }
      }
      else {
         int i = 0;
         while (!file.eof()) {
            char ch{};
            ch = file.peek();
            iProduct* temp = nullptr;
            if (ch > 48 && ch < 52) { // using ascii value
               temp = new Perishable();
            }
            else if (ch >= 52 && ch <= 57) { // using ascii value
               temp = new Item();
            }
            else {
            }
            if (temp == nullptr) {
                  delete[] m_products[i];
               }
            else{
               temp->load(file);
               m_noOfProd++;
               m_products[i] = temp;
            }
            i++;
         }
      }
      cout << m_noOfProd << " records loaded!" << endl << endl;
      return m_noOfProd != 0;
   }
   int AidMan::list(const char* sub_desc) {
      int count = 0;
      cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
      cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
      if (sub_desc == nullptr) {
         for (int i = 0; i < m_noOfProd; i++) {
            m_products[i]->linear(true);
            cout.width(4);
            cout.setf(ios::right);
            cout.fill(' ');
            cout << i + 1 << " | ";
            cout << *m_products[i] << endl;
            count++;
         }
      }
      else {
         for (int i = 0; i < m_noOfProd; i++) {
            if (strstr(m_products[i]->descVal(),sub_desc)) {
               m_products[i]->linear(true);
               cout.width(4);
               cout.setf(ios::right);
               cout.fill(' ');
               cout << i + 1 << " | ";
               cout << *m_products[i] << endl;
               count++;

            }
         }
      }
      cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
     

      if (count == 0) {
         cout << "The list is empty!";
      }
      return count;
   }

   int AidMan::search(int sku)const {
      int flag = -1;
      for (int i = 0; i < m_noOfProd && flag == -1; i++) {
         if (m_products[i]->getSKU() == sku) {
            flag = i;
         }
      }
      return flag;
   }

   void AidMan::addItem() {
      if (m_noOfProd == sdds_max_num_items) {
         cout << "Database full!";
      }
      else {
         int choice = 0;
         Menu addingMenu(2, "1- Perishable\n2- Non-Perishable\n-----------------\n");
         choice = addingMenu.run();
         if (choice != 0) {
            iProduct* temp = nullptr;
            if (choice == 1) {
               temp = new Perishable();
            }
            else {
               temp = new Item();
            }
            int sku = ut.getint(10000, 99999, "SKU: ");
            if (search(sku) != -1) {
               cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl;
               delete temp;
            }
            else {
               temp->setSku(sku);
               temp->read(cin);
               if (temp->operator bool()) {
                  if (m_noOfProd == sdds_max_num_items) {
                     cout << temp;
                     delete temp;
                  }
                  else {
                     m_products[m_noOfProd] = temp;
                     m_noOfProd++;
                     
                  }
               }
            }

         }
         else {
            cout << "Aborted" << endl;
            
         }
      }
   }

   void AidMan::remove(int index) {
      delete m_products[index];
      m_products[index] = nullptr;
      for (int i = index; i < m_noOfProd; i++) {
         m_products[i] = m_products[i + 1];
      }
      m_noOfProd--;
   }

   void AidMan::removeItem() {
      string desc = "";
      
      cout << "Item description: ";
      getline(cin, desc);
      if (list(desc.c_str()) > 0) {
         int flag = ut.getint(10000, 99999, "Enter SKU: ");
         flag = search(flag);
         if (flag != -1) {
            m_products[flag]->linear(false);
            cout << "Following item will be removed: " << endl;
            cout << *m_products[flag] << endl;
            Menu deleteItem(1, "Are you sure?\n1- Yes!\n");
            int choice = deleteItem.run();
            if (choice != 0) {
               remove(flag);
               cout << "Item removed!" << endl << endl;
            }
            else {
               cout << "Aborted!\n";
            }
         }
      }
      else {
         cout << "No matches found!" << endl;
      }
   }

   void AidMan::updateQuantity() {
      string desc = "";
      cout << "Item description: ";
      getline(cin, desc);
      if (list(desc.c_str()) > 0) {
         int flag = ut.getint(10000, 99999, "Enter SKU: ");
         flag = search(flag);
         if (flag != -1) {
            Menu update(2, "1- Add\n2- Reduce\n");
            int choice = update.run();
            if (choice == 1) {
               if (m_products[flag]->qtyNeeded() != m_products[flag]->qty()) {
                  int qty = 0;
                  qty = ut.getint(1, m_products[flag]->qtyNeeded() - m_products[flag]->qty(), "Quantity to add: ");
                  m_products[flag]->operator+=(qty);
                  cout << qty << " items added!" << endl;
               }
               else {
                  cout << "Quantity Needed already fulfilled!\n";
               }
            }
            else if(choice == 2) {
               if (m_products[flag]->qty() != 0) {
                  int qty = 0;
                  
                  qty = ut.getint(1, m_products[flag]->qty(), "Quantity to reduce: ");
                  m_products[flag]->operator-=(qty);
                  cout << qty << " items removed!" << endl;
               }
               else {
                  cout << "Quantity on hand is zero!" << endl;
               }
            }
            else {
               cout << "Aborted!" << endl;
            }
         }
         else {
            cout << "SKU not found!" << endl;
         }
      }
      else {
         cout << "No matches found!" << endl;
      }
      cout << endl;
   }

   void AidMan::sort() {
      iProduct* temp;
      for (int i = 0; i < m_noOfProd; i++) {
         for (int j = i + 1; j < m_noOfProd; j++)
         {
            if ((m_products[j]->qtyNeeded() - m_products[j]->qty()) > (m_products[i]->qtyNeeded() - m_products[i]->qty())) {
               temp = m_products[i];
               m_products[i] = m_products[j];
               m_products[j] = temp;
            }
         }
      }
      cout << "Sort completed!" << endl << endl;
   }

   void AidMan::shipItems() {
      Date date{};
      ofstream file("shippingOrder.txt");
      file << "Shipping Order, Date: " << date << endl;
      file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
      file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
      int count = 0;
      for (int i = 0; i < m_noOfProd; i++) {
         if (m_products[i]->qty() == m_products[i]->qtyNeeded()) {
            m_products[i]->linear(true);
            file.width(4);
            file.setf(ios::right);
            file.fill(' ');
            file << count + 1 << " | ";
            m_products[i]->save(file);
            file << endl;
            count++;
            remove(i);
         }
         
      }
      file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
      cout << "Shipping Order for " << count << " times saved!" << endl << endl;
   }

}