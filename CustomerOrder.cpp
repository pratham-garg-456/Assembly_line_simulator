#include <iostream>
#include <iomanip>

#include "CustomerOrder.h"
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace seneca
{

	size_t CustomerOrder::m_widthField = 0;

	// Constructor: Parses the input string to initialize the customer's name, product, and list of items and description.
	CustomerOrder::CustomerOrder(const std::string &str)
	{
		Utilities ut;
		size_t pos = 0;
		size_t pos2 = 0;
		bool more = true;
		size_t numOfItems = 0;
		m_name = ut.extractToken(str, pos, more);
		m_product = ut.extractToken(str, pos, more);
		pos2 = pos;
		while ((pos2 = str.find_first_of(ut.getDelimiter(), pos2)) != std::string::npos)
		{
			numOfItems++;
			pos2++;
		}
		numOfItems++;
		m_lstItem = new Item *[numOfItems];
		for (size_t i = 0; i < numOfItems; i++)
		{
			std::string itemName = ut.extractToken(str, pos, more);
			Item *item = new Item(itemName);
			m_lstItem[i] = item;
			m_cntItem++;
		}
		// Only update if the new field width is greater
		m_widthField = max(m_widthField, ut.getFieldWidth());
	}

	// Move constructor
	CustomerOrder::CustomerOrder(CustomerOrder &&src) noexcept
	{
		*this = move(src);
	}

	// Move assignment operator
	CustomerOrder &CustomerOrder::operator=(CustomerOrder &&src) noexcept
	{
		if (this != &src)
		{

			if (m_lstItem)
			{
				for (size_t i = 0; i < m_cntItem; i++)
				{
					delete m_lstItem[i];
					m_lstItem[i] = nullptr;
				}
				delete[] m_lstItem;
				m_lstItem = nullptr;
			}
			m_name = std::move(src.m_name);
			m_product = std::move(src.m_product);

			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
			src.m_cntItem = 0;
		}
		return *this;
	}

	// Destructor
	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
			delete[] m_lstItem;
			m_lstItem = nullptr;
		}
		m_cntItem = 0;
	}

	// Checks if all items in the order are filled.
	bool CustomerOrder::isOrderFilled() const noexcept
	{
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem && isFilled; i++)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				isFilled = false;
			}
		}
		return isFilled;
	}

	// Checks if all items with the given name are filled.
	bool CustomerOrder::isItemFilled(const std::string &itemName) const noexcept
	{
		bool isFilled = true;
		for (size_t i = 0; i < m_cntItem && isFilled; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (!m_lstItem[i]->m_isFilled)
				{
					isFilled = false;
				}
			}
		}
		return isFilled;
	}

	// Attempts to fill an item in the order using the provided station.
	void CustomerOrder::fillItem(Station &station, std::ostream &os)
	{
		std::string itemName = station.getItemName();
		if (!isItemFilled(itemName))
		{
			if (station.getQuantity() == 0)
			{
				for (size_t i = 0; i < m_cntItem; i++)
				{ // Iterate through all items in the order
					if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
					{
						// If this item matches the station's item and is not filled
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << itemName << "]" << endl;
					}
				}
			}
			else
			{
				for (size_t i = 0; i < m_cntItem; i++)
				{
					if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
					{
						m_lstItem[i]->m_isFilled = true;
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						station.updateQuantity();
						break;
					}
				}
				os << "    Filled " << m_name << ", " << m_product << " [" << itemName << "]" << endl;
			}
		}
	}

	// Displays the order details and the status of each item.
	void CustomerOrder::display(std::ostream &os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i)
		{
			os << "["
			   << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber
			   << "] "
			   << std::left << std::setw(m_widthField) << std::setfill(' ')
			   << m_lstItem[i]->m_itemName
			   << "   - "
			   << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED")
			   << std::endl;
		}
	}

}