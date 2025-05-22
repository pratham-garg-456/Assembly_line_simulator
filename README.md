# Assembly Line Simulation Project

## Project Overview

This project is a simulation of an assembly line using C++ and Object-Oriented Programming principles. The assembly line consists of multiple stations, each managing its own inventory and responsible for filling parts of customer orders. The simulation is broken down into three milestones, guiding the step-by-step implementation of core components: utilities and stations, customer orders, and the assembly line workflow.

The main flow:
- **Stations** hold stock items and fill customer orders if possible.
- **Customer Orders** specify required items and move along the line.
- The **Line Manager** coordinates the movement of orders through the stations.
- At the end, orders are reported as complete or incomplete, depending on inventory availability.

---

## Milestones & Modules

### Milestone 1: Utilities and Station Classes

- **Utilities**: Parses delimited strings from input files, manages token extraction, and field width for display formatting.
    - Shared delimiter and field width for all objects.
    - Exception handling for invalid token extraction.
- **Station**: Represents a station on the assembly line.
    - Stores station ID, item name, description, serial number, and quantity.
    - Supports formatted display and inventory management.
    - Created by parsing one line of input using `Utilities`.

### Milestone 2: CustomerOrder Class

- **CustomerOrder**: Models a customer's order of items.
    - Stores customer name, product name, and a dynamic list of items requested.
    - Manages resources explicitly (no copy allowed, only move semantics).
    - Supports filling items at a station, checking filled status, and formatted display.
    - Uses `Utilities` for parsing and field width management.

### Milestone 3: Workstation and LineManager Classes

- **Workstation**: Extends `Station` to handle a queue of customer orders.
    - Processes orders: fills items, moves orders to next station or completion queues.
    - Cannot be copied or moved (to avoid logic errors).
- **LineManager**: Oversees the assembly line.
    - Configures the line from a configuration file.
    - Moves orders step-by-step through the stations.
    - Reports completed and incomplete orders after processing is finished.
    - Uses STL containers and algorithms for efficient management.

---

## Usage & Structure

- All code is within the `sdds` namespace.
- Each module is implemented with proper header and source files (`*.h`, `*.cpp`).
- All files begin with a comment block including your name, student ID, email, and completion confirmation.
- Tester code and input files are provided—**do not modify tester modules**.
- Sample outputs are available for each milestone for verification.

### File List

- `Utilities.h`, `Utilities.cpp`
- `Station.h`, `Station.cpp`
- `CustomerOrder.h`, `CustomerOrder.cpp`
- `Workstation.h`, `Workstation.cpp`
- `LineManager.h`, `LineManager.cpp`
- `reflect.txt` (for milestone 3, with your project reflections)

---



