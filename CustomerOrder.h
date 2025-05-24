#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include "Station.h"

namespace seneca{

	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& str) : m_itemName(str) {};
	};

	class CustomerOrder
	{
		std::string m_name; // name of the customer
		std::string m_product; // name of the product being assembled
		size_t m_cntItem{ 0 }; // number of items in the order
		Item** m_lstItem{ nullptr }; // dynamically allocated array of pointers to Item objects

		static size_t m_widthField;
	public:
		CustomerOrder() = default; 
		CustomerOrder(const std::string& str);
		CustomerOrder(const CustomerOrder& src) = delete;
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&& src) noexcept;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		~CustomerOrder();

		bool isOrderFilled() const noexcept;
		bool isItemFilled(const std::string& itemName) const noexcept;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !CUSTOMERORDER_H
