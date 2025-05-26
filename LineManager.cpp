#include <iostream>
#include <fstream>
#include <algorithm>

#include "LineManager.h"
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;

namespace seneca
{
	// Constructor that initializes the assembly line with stations from the vector of Workstation pointers in the order given in a file
	LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
	{
		Utilities ut;
		std::string stationName;
		std::string temp;
		bool more = false;
		fstream f(file);

		if (!f.is_open())
		{
			throw std::runtime_error("Error: Unable to open file: " + file);
		}

		while (getline(f, temp))
		{
			size_t next_pos = 0;
			more = false;
			ut.setDelimiter('|');
			stationName = ut.extractToken(temp, next_pos, more);

			auto it = find_if(stations.begin(), stations.end(),
							  [&stationName](const Workstation *ws)
							  {
								  return ws->getItemName() == stationName;
							  });

			if (it == stations.end())
			{
				throw std::runtime_error("Station not found: " + stationName);
			}

			m_activeLine.push_back(*it);

			if (more)
			{
				stationName = ut.extractToken(temp, next_pos, more);
				auto nextIt = find_if(stations.begin(), stations.end(),
									  [&stationName](const Workstation *ws)
									  {
										  return ws->getItemName() == stationName;
									  });
				if (nextIt == stations.end())
				{
					throw std::runtime_error("Next station not found: " + stationName);
				}

				m_activeLine.back()->setNextStation(*nextIt);
			}
		}

		// Find the first station (one that is not referenced as next by any other station)
		auto firstIt = find_if(m_activeLine.begin(), m_activeLine.end(),
							   [this](const Workstation *ws)
							   {
								   return none_of(m_activeLine.begin(), m_activeLine.end(),
												  [ws](const Workstation *ws1)
												  {
													  return ws1->getNextStation() == ws;
												  });
							   });

		if (firstIt == m_activeLine.end())
		{
			throw std::runtime_error("No starting station found in assembly line");
		}

		m_firstStation = *firstIt;
	}
	// Reorders the stations in the assembly line based on the next station pointers
	void LineManager::reorderStations()
	{
		if (!m_firstStation)
		{
			return; // Nothing to reorder if no first station is set
		}

		std::vector<Workstation *> orderedStations;
		orderedStations.reserve(m_activeLine.size()); // Reserve space for efficiency

		Workstation *current = m_firstStation;
		while (current)
		{
			orderedStations.push_back(current);
			current = current->getNextStation();
		}

		m_activeLine = std::move(orderedStations);
	} // Runs the assembly line for one iteration, filling orders and moving them through the stations
	bool LineManager::run(std::ostream &os)
	{
		static size_t iteration = 1;

		os << "Line Manager Iteration: " << iteration << endl;

		// Move pending order to first station if available
		if (!g_pending.empty() && m_firstStation)
		{
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
			m_cntCustomerOrder++;
		}

		// Fill orders at each station
		for (auto *station : m_activeLine)
		{
			station->fill(os);
		}

		// Attempt to move orders through the line
		for (auto *station : m_activeLine)
		{
			station->attemptToMoveOrder();
		}

		iteration++;

		// Check if all orders are processed using the new utility method
		return isProcessingComplete();
	}
	// Displays the current state of the assembly line, showing each workstation and its next station
	void LineManager::display(std::ostream &os) const
	{
		for (const auto *station : m_activeLine)
		{
			station->display(os);
		}
	}

	size_t LineManager::getTotalOrders() const noexcept { return m_cntCustomerOrder; }

	// Utility methods implementation
	size_t LineManager::getCompletedOrders() const noexcept
	{
		return g_completed.size();
	}

	size_t LineManager::getIncompleteOrders() const noexcept
	{
		return g_incomplete.size();
	}

	bool LineManager::isProcessingComplete() const noexcept
	{
		return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
	}

}