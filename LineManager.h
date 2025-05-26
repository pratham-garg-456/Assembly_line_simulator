#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <string>
#include <ostream>

#include "Workstation.h"

namespace seneca
{

	/**
	 * @brief LineManager class that oversees the assembly line operations
	 *
	 * Manages the flow of customer orders through workstations,
	 * coordinates filling and movement of orders, and tracks completion status.
	 */
	class LineManager
	{
		std::vector<Workstation *> m_activeLine; // collection of workstations on current line
		size_t m_cntCustomerOrder{};			 // the total number of CustomerOrder objects
		Workstation *m_firstStation{};			 // points to the first active station on the current line

	public:
		// Constructor
		LineManager(const std::string &file, const std::vector<Workstation *> &stations);

		// Deleted copy constructor and assignment operator (prevent accidental copying)
		LineManager(const LineManager &) = delete;
		LineManager &operator=(const LineManager &) = delete;

		// Core operations
		void reorderStations();
		bool run(std::ostream &os);
		void display(std::ostream &os) const;

		// Utility methods
		size_t getTotalOrders() const noexcept;
		size_t getCompletedOrders() const noexcept;
		size_t getIncompleteOrders() const noexcept;
		bool isProcessingComplete() const noexcept;
	};

}

#endif // !LINEMANAGER_H
