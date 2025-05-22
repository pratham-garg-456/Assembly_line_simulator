#ifndef UTILITIES_H
#define UTILITIES_H

namespace seneca {

	class Utilities {
		size_t m_widthField{ 1 }; // length of the token extracted
		static char m_delimeter; // the delemiter between the tokens

	public:
		void setFieldWidth(size_t newWidth); 
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		std::string  removeSpace(const std::string& str);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};

}

#endif // !UTILITIES_H