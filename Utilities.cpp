#include <iostream>
#include <string>

#include "Utilities.h"

using namespace std;

namespace seneca {

	char Utilities::m_delimeter;

	// sets the field width of the current object to the value of parameter newWidth
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	// returns the field width of the current object
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	// extracts a token from string str referred to by the first parameter.
	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		size_t i = next_pos;
		string token = "";
		more = false;
		if (str[i] == m_delimeter) {
			throw "Delimeter found at next_pos";
		}
		while (str[i] != m_delimeter && str[i] != '\n' && i < str.size()) {
			token += str[i];
			i++;
		}
		token = removeSpace(token);
		if (str[i] == m_delimeter) {
			more = true;
			next_pos = i + 1;
		}
		else {
			more = false;
		}
		if (m_widthField < token.size()) {

			m_widthField = token.size();
		}
		return token;

	}

	// sets the delimiter for this class to the character received
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimeter = newDelimiter;
	}

	// returns the delimiter for this class.
	char Utilities::getDelimiter() {
		return m_delimeter;
	}
	string Utilities::removeSpace(const std::string& str) {
		size_t x = 0;
		size_t y = str.size() - 1;
		string tString = "";
		while (x < str.size() && str[x] == ' ') {
			x++;
		}
		while (y >= 0 && str[y] == ' ') {
			y--;
		}
		tString = str.substr(x, y - x + 1);

		return tString;
	}




}