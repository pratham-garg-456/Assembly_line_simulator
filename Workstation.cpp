#include <iostream>
#include <deque>

#include "Workstation.h"

using namespace std;

namespace seneca
{

	deque<CustomerOrder> g_pending;
	deque<CustomerOrder> g_completed;
	deque<CustomerOrder> g_incomplete;

	Workstation::Workstation(const std::string &str) : Station(str) {}

	void Workstation::fill(std::ostream &os)
	{
		if (!m_orders.empty())
		{ // Check if m_orders is not empty before accessing front()
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		if (m_orders.empty())
		{ // Prevent accessing front() on empty deque
			return false;
		}

		if (m_orders.front().isOrderFilled() || (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0))
		{
			if (!m_pNextStation)
			{
				if (!m_orders.front().isOrderFilled())
				{
					g_incomplete.push_back(std::move(m_orders.front()));
				}
				else
				{
					g_completed.push_back(std::move(m_orders.front()));
				}
			}
			else
			{
				*m_pNextStation += std::move(m_orders.front());
			}
			m_orders.pop_front(); // Remove the moved order
			return true;
		}

		return false;
	}

	void Workstation::setNextStation(Workstation *station = nullptr) noexcept
	{
		m_pNextStation = station;
	}

	Workstation *Workstation::getNextStation() const noexcept
	{
		return m_pNextStation;
	}

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

	Workstation &Workstation::operator+=(CustomerOrder &&newOrder) noexcept
	{
		m_orders.push_back(std::move(newOrder)); // Use std::move
		return *this;
	}
}