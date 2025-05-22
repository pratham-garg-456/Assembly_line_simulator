#include <iostream>
#include <string>
#include <iomanip>

#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace seneca {

	size_t Station::m_widthField =0;
	size_t Station::id_generator =0;
	

	

	Station::Station(std::string& str) {
		Utilities ut;
		size_t pos = 0;
		bool more = true;
		m_name = ut.extractToken(str,pos,more);
		if (more) {
			m_serialNumber = stoi(ut.extractToken(str, pos, more));
		}
		if (more) {
			m_stock = stoi(ut.extractToken(str, pos, more));
		}

		Station::m_widthField = max(ut.getFieldWidth(), Station::m_widthField);
		if (more) {
			m_description = ut.extractToken(str, pos, more);
		}
		m_id = ++id_generator;
		
	}
	const std::string& Station::getItemName() const {
		return m_name;

	}
	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}
	size_t Station::getQuantity() const {
		return m_stock;
	}
	void Station::updateQuantity() {
		m_stock = m_stock > 0 ? m_stock - 1 : m_stock;
	}
	void Station::display(std::ostream& os, bool full) const {
		os << std::right << std::setfill('0') << std::setw(3) << m_id << " | ";
		os << std::left << std::setfill(' ') << std::setw(m_widthField+1) << m_name << " | ";
		os << std::right << std::setfill('0') << std::setw(6) << m_serialNumber << " | ";
		os << std::left;

		if (!full) {
			os << std::endl;
		}
		else {
			os << std::right << std::setfill(' ') << std::setw(4) << m_stock << " | ";
			os << m_description << std::endl;
			os << std::left;
		}
	}

}