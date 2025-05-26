#include <iostream>
#include <deque>

#include "Workstation.h"

using namespace std;

namespace seneca
{
	// Global deque to hold orders in different states
	deque<CustomerOrder> g_pending;
	deque<CustomerOrder> g_completed;
	deque<CustomerOrder> g_incomplete;

	// one argument constructor
	Workstation::Workstation(const std::string &str) : Station(str) {}

	// Fills the order at the front of the m_orders deque
	void Workstation::fill(std::ostream &os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}
	// Attempts to move the order at the front of m_orders to the next station or move to g_completed or g_incomplete if no next station exists
	bool Workstation::attemptToMoveOrder()
	{
		if (m_orders.empty())
		{
			return false;
		}

		// Check if order should be moved: either completely filled, current item filled, or no stock
		bool shouldMove = m_orders.front().isOrderFilled() ||
						  m_orders.front().isItemFilled(this->getItemName()) ||
						  this->getQuantity() == 0;

		if (shouldMove)
		{
			if (!m_pNextStation)
			{
				// No next station - move to appropriate global deque
				if (m_orders.front().isOrderFilled())
				{
					g_completed.push_back(std::move(m_orders.front()));
				}
				else
				{
					g_incomplete.push_back(std::move(m_orders.front()));
				}
			}
			else
			{
				// Move to next station
				*m_pNextStation += std::move(m_orders.front());
			}
			m_orders.pop_front();
			return true;
		}

		return false;
	}
	// Sets the next station in the assembly line
	void Workstation::setNextStation(Workstation *station) noexcept
	{
		m_pNextStation = station;
	}

	// Returns the next station in the assembly line
	Workstation *Workstation::getNextStation() const noexcept
	{
		return m_pNextStation;
	}

	// Displays the workstation and its next station
	void Workstation::display(std::ostream &os) const noexcept
	{

		os << this->getItemName() << " --> ";
		if (m_pNextStation)
		{
			os << m_pNextStation->getItemName();
		}
		else
		{
			os << "End of Line";
		}
		os << std::endl;
	}

	// Adds a new order to the workstation's order queue
	Workstation &Workstation::operator+=(CustomerOrder &&newOrder) noexcept
	{
		m_orders.push_back(std::move(newOrder)); // Use std::move
		return *this;
	}

	// Additional utility methods implementation
	// Note: hasOrders() and getOrderCount() are implemented inline in the header

	// Check if the station can process an order (has orders and either has stock or order doesn't need this item)
	bool Workstation::canProcessOrder() const noexcept
	{
		if (m_orders.empty())
		{
			return false;
		}

		const auto &currentOrder = m_orders.front();
		return this->getQuantity() > 0 ||
			   currentOrder.isItemFilled(this->getItemName()) ||
			   currentOrder.isOrderFilled();
	}
}