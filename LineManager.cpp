#include <iostream>
#include <fstream>
#include <algorithm>

#include "LineManager.h"
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;

namespace seneca {
	//extern deque<CustomerOrder> g_pending;
	//extern deque<CustomerOrder> g_completed;
	//extern deque<CustomerOrder> g_incomplete;
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		Utilities ut;
		std::string stationName;
		std::string temp;
		bool more = false;
		fstream f(file);
		if (!f)
		{
			throw "Error opening the file";
		}

		while (getline(f, temp)) {
			size_t next_pos = 0;
			more = false;
			ut.setDelimiter('|');
			stationName = ut.extractToken(temp, next_pos, more);
			auto it = find_if(stations.begin(), stations.end(), [&](Workstation* ws) { return ws->getItemName() == stationName;});
			
			if (it == stations.end()) {
				throw std::runtime_error("Station not found: " + stationName);
			}

			m_activeLine.push_back(*it);
			if (more) {
				stationName = ut.extractToken(temp, next_pos, more);
				auto nextIt = find_if(stations.begin(), stations.end(), [&](Workstation* ws) { return ws->getItemName() == stationName;});
				if (nextIt == stations.end()) {
					throw std::runtime_error("Next station not found: " + stationName);
				}

				m_activeLine.back()->setNextStation(*nextIt);
			}
		}
		auto it = find_if(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* ws) {
			return none_of(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* ws1) {
				return ws1->getNextStation() == ws;
				});

			});

		m_firstStation = *it;


	}


	void LineManager::reorderStations() {
		std::vector<Workstation*> tmp;
		tmp.push_back(m_firstStation);
		while (tmp.back()->getNextStation()) {
			tmp.push_back(move(tmp.back()->getNextStation()));
		}
		m_activeLine = move(tmp);

	}


	bool LineManager::run(std::ostream& os) {
		static size_t iteration = 1;

		os << "Line Manager Iteration: " << iteration << endl;
		if (!g_pending.empty()) {
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
			m_cntCustomerOrder++;
		}
		
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) { ws->fill(os);});
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) { ws->attemptToMoveOrder();});
		iteration++;
		if (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder) {
			return true;
		}
		else {
			return false;
		}
		

	}


	void LineManager::display(std::ostream& os) const {

		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) { ws->display(os);});
	}

}