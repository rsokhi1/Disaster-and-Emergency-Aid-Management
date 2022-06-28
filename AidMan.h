#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "iProduct.h"

namespace sdds
{
	const int sdds_max_num_items = 100;
	class AidMan
	{
		char* m_filename;
		Menu m_menu;
		iProduct* m_products[sdds_max_num_items]{};
		int m_noOfProd;
	public:
		AidMan();
		~AidMan();
		unsigned int menu()const;
		void run();
		//ms 51
		void save();
		void deallocate();
		bool load();
		int list(const char* sub_desc = nullptr);

		int search(int sku)const;
		void addItem();
		void remove(int index);
		void removeItem();
		void updateQuantity();
		void sort();
		void shipItems();
	};
}
#endif