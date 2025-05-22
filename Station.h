#ifndef STATION_H
#define STATION_H

namespace seneca {

	class Station {

		int m_id{}; // station id
		std::string m_name{}; // item handled by station
		std::string m_description{}; // station description
		unsigned int m_serialNumber{}; // next serial number to be assigned to an item
		unsigned int m_stock{}; // number of items in stock

		static size_t m_widthField;
		static size_t id_generator;

	public:

		Station(std::string& str);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};

}

#endif //!STATION_H