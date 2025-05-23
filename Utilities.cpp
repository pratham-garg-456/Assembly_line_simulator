#include <iostream>
#include <string>
#include <stdexcept>

#include "Utilities.h"

using namespace std;

namespace seneca {

	// Initialize static members 
	char Utilities::m_delimeter = ',';

	// sets the field width of the current object to the value of parameter newWidth
	void Utilities::setFieldWidth(size_t newWidth) noexcept {
		m_widthField = newWidth;
	}

	// returns the field width of the current object
	size_t Utilities::getFieldWidth() const noexcept {
		return m_widthField;
	}

	// extracts a token from string str referred to by the first parameter.
	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		more = false;
		if (next_pos >= str.size()) {
			return "";
		}

		if (str[next_pos] == m_delimeter) {
			throw std::invalid_argument("Delimiter found at next_pos");
		}
		size_t end_pos = str.find(m_delimeter, next_pos);
		std::string token = removeSpace(str.substr(next_pos, end_pos - next_pos));

		more = (end_pos != std::string::npos);
		next_pos = more ? end_pos + 1 : str.length();

		if (m_widthField < token.length()) {
			m_widthField = token.length();
		}
		return token;
	}

	// sets the delimiter for this class to the character received
	void Utilities::setDelimiter(char newDelimiter) noexcept {
		m_delimeter = newDelimiter;
	}

	// returns the delimiter for this class.
	char Utilities::getDelimiter() noexcept{
		return m_delimeter;
	}

	// Removes leading and trailing spaces from the input string.
	string Utilities::removeSpace(const std::string& str) {
		size_t start = str.find_first_not_of(' ');
		if (start == std::string::npos) return "";
		size_t end = str.find_last_not_of(' ');
		return str.substr(start, end - start + 1);
	}

	/*
	 string Utilities::removeSpace(const string& str) {
        auto start = find_if_not(str.begin(), str.end(), ::isspace);
        if (start == str.end()) return "";
        auto end = find_if_not(str.rbegin(), str.rend(), ::isspace).base();
        return string(start, end);
    }
	*/

}