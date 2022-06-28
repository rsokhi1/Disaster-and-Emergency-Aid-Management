#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include <fstream>
#include "iProduct.h"
#include "Status.h"
namespace sdds{
    class Item : public iProduct{
        double m_price;
        int m_qty;
        int m_qtyNeeded; 
        char* m_desc;
        bool m_linear;
    protected:
        Status m_state;
        int m_sku{};
        bool linear()const;
    public:
        Item();
        
        Item(const Item& I);
        Item& operator=(const Item& I);
        ~Item();

        int qtyNeeded()const;
        int qty()const;
        operator double()const;
        operator bool() const;

        int operator-=(int qty);
        int operator+=(int qty);
        void linear(bool isLinear);

        void clear();

        bool operator==(int sku)const;
        bool operator==(const char* description) const;

        std::ofstream& save(std::ofstream& ofstr);
        std::ifstream& load(std::ifstream& ifstr);
        std::ostream& display(std::ostream& ostr)const;
        std::istream& read(std::istream& istr);
        int readSku(std::istream& istr);

        const char* descVal()const;
        int getSKU()const;

        void setSku(int sku);
    };
}

#endif // !SDDS_ITEM_H_