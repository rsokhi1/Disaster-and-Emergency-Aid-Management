#ifndef SDDS_MENU_H
#define SDDS_MENU_H
using namespace std;
namespace sdds
{
	class Menu
	{
	private:
		char* m_content{};
		unsigned int m_numOptions{};
	public:
		Menu(unsigned int numOptions = 0, const char* content = nullptr);
		Menu(const Menu& mu);
		Menu& operator=(const Menu& mu);
		Menu& operator=(const char* menu);
		Menu& operator=(int opt);

		
		~Menu();
		int run()const;
	};
}
#endif