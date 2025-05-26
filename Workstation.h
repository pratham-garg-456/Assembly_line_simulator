#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include <string>
#include <ostream>

#include "CustomerOrder.h"
#include "Station.h"

namespace seneca {

	/**
	 * @brief Workstation class representing a station on the assembly line
	 * 
	 * Inherits from Station and manages a queue of customer orders.
	 * Orders are processed, filled, and moved to the next station or completion queues.
	 */
	class Workstation : public Station{

		std::deque<CustomerOrder> m_orders; // order placed on the station
		Workstation* m_pNextStation{}; // pointer to the next workstation in the assembly line

	public:
		// Constructor
		explicit Workstation(const std::string& str);
		
		// Deleted copy/move constructors and assignment operators
		Workstation(const Workstation& src) = delete;
		Workstation& operator = (const Workstation& src) = delete;
		Workstation(Workstation&& src) = delete;
		Workstation& operator = (Workstation&& src) = delete;
		
		// Core operations
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		
		// Station management
		void setNextStation(Workstation* station = nullptr) noexcept;
		Workstation* getNextStation() const noexcept;
		
		// Display and utility
		void display(std::ostream& os) const noexcept;
		Workstation& operator+=(CustomerOrder&& newOrder) noexcept;
		
		// Additional utility methods
		bool hasOrders() const noexcept { return !m_orders.empty(); }
		size_t getOrderCount() const noexcept { return m_orders.size(); }
		
		// Debug/monitoring methods
		bool canProcessOrder() const noexcept;
	};

	// Global deques for order management
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

}

#endif// !WORKSTATION_H