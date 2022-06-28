#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H_
#include "Item.h"
#include "Date.h"
namespace sdds {
   class Perishable : public Item {
      Date m_expiry{};
      char* m_instructions{};
   public:
      Perishable();
      Perishable(const Perishable& P);
      Perishable& operator=(const Perishable& P);
      ~Perishable();
      const Date& expiry()const;
      int readSku(std::istream& is);
      std::ofstream& save(std::ofstream& ofstr);
      std::ifstream& load(std::ifstream& ifstr);
      std::ostream& display(std::ostream& ostr)const;
      std::istream& read(std::istream& istr);

      int getSKU()const;
      void setSku(int sku);
   };
}



#endif // !SDDS_PERISHABLE_H_