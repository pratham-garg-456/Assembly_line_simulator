#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include <string>
#include <ostream>

#include "CustomerOrder.h"
#include "Station.h"

namespace seneca {



	class Workstation : public Station{

		std::deque<CustomerOrder> m_orders; // order placed on the station
		Workstation* m_pNextStation{}; // pointer to the next workstation in the assembly line

	public:

		Workstation(const std::string& str);
		Workstation(const Workstation& src) = delete;
		Workstation& operator = (const Workstation& src) = delete;
		Workstation(const Workstation&& src) = delete;
		Workstation& operator = (const Workstation&& src) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station) noexcept;
		Workstation* getNextStation() const noexcept;
		void display(std::ostream& os) const noexcept;
		Workstation& operator+=(CustomerOrder&& newOrder) noexcept;
	};

	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

}

#endif// !WORKSTATION_H