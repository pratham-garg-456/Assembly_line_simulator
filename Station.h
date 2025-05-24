#ifndef STATION_H
#define STATION_H

namespace seneca {

	class Station {

		size_t m_id{}; // station id
		std::string m_name; // item handled by station
		std::string m_description; // station description
		size_t m_serialNumber{}; // next serial number to be assigned to an item
		size_t m_stock{}; // number of items in stock

		static size_t m_widthField; // width of the field for displaying the station name
		static size_t m_idGenerator; // static variable to generate unique station IDs

	public:

		explicit Station(const std::string& str);
		const std::string& getItemName() const noexcept;
		size_t getNextSerialNumber() noexcept;
		size_t getQuantity() const noexcept;
		void updateQuantity() noexcept;
		void display(std::ostream& os, bool full) const;

	};

}

#endif //!STATION_H