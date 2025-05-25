#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <string>
#include <ostream>

#include "Workstation.h"

namespace seneca {

	class LineManager
	{
		std::vector<Workstation*> m_activeLine; // collection of workstations on current line
		size_t m_cntCustomerOrder{}; // the total number of CustomerOrder objects
		Workstation* m_firstStation{}; // points to the first active station on the current line

	public:

		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};

}

#endif // !LINEMANAGER_H

