#include <iostream>
#include <string>
#include <iomanip>

#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace seneca {

	// Initialize static members
	size_t Station::m_widthField =0;
	size_t Station::m_idGenerator =0;
	
	// Constructor: use initialization list, check for exceptions, and guard against invalid input
	Station::Station(const std::string& str) {
		Utilities ut;
		size_t pos = 0;
		bool more = true;
		try {
			m_name = ut.extractToken(str, pos, more);
			m_serialNumber = more ? std::stoul(ut.extractToken(str, pos, more)) : 0;
			m_stock = more ? std::stoul(ut.extractToken(str, pos, more)) : 0;

			m_widthField = std::max(ut.getFieldWidth(), m_widthField);

			m_description = more ? ut.extractToken(str, pos, more) : "";

			m_id = ++m_idGenerator;
		}
		catch (const std::exception& e) {
			// Handle or rethrow with more context
			throw std::invalid_argument(std::string("Station parsing error: ") + e.what());
		}
	}

	// Returns the name of the item handled by the station
	const std::string& Station::getItemName() const noexcept {
		return m_name;

	}

	// Returns the next serial number and increments it
	size_t Station::getNextSerialNumber() noexcept{
		return m_serialNumber++;
	}

	// Returns the current quantity in stock
	size_t Station::getQuantity() const noexcept{
		return m_stock;
	}

	// Decrements the stock quantity if greater than zero
	void Station::updateQuantity() noexcept {
		if (m_stock > 0) {
			--m_stock;
		}
	}

	// Displays station information; full details if 'full'
	void Station::display(std::ostream& os, bool full) const {
		os << std::right << std::setfill('0') << std::setw(3) << m_id << " | ";
		os << std::left << std::setfill(' ') << std::setw(m_widthField+1) << m_name << " | ";
		os << std::right << std::setfill('0') << std::setw(6) << m_serialNumber << " | ";

		if (!full) {
			os << std::endl;
		}
		else {
			os << std::right << std::setfill(' ') << std::setw(4) << m_stock << " | ";
			os << m_description << std::endl;
		}
	}

}