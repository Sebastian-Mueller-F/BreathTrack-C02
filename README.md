
# Breath Tracker Co2

## Project Overview

**Breath Tracker Co2** is a project developed for Medical Löwenstein. The primary goal of the project is to simulate CO2 sensor data, process it using different averaging methods (Simple Moving Average and Exponential Moving Average), and present this data in a user-friendly interface. The project focuses on real-time data handling and aims to provide adjustable settings for data averaging directly through the UI.

## Features

- **Sensor Simulation:** Simulates CO2 sensor readings, providing real-time data updates.
- **Data Averaging:** Supports Simple Moving Average (SMA) and Exponential Moving Average (EMA) calculations with adjustable periods.
- **Customizable UI:** Users can adjust the averaging periods for both SMA and EMA in the settings drawer. The type of averaging can be switched directly in the live data view.
- **Backend-Frontend Integration:** A robust interface connects the backend data processing with the frontend UI, ensuring smooth data flow and interaction.

## Installation and Usage

### Installation

Currently, there is no executable available for the project. To compile and run the project, you will need to use Qt. Ensure that you have the necessary dependencies and tools installed:

- **Qt 5.15 or higher**
- **CMake** for project configuration
- **C++17 or higher** for compiling the code

### Usage

To compile and run the project, open the project in Qt Creator and build the application. The project has been designed to run under Linux, so ensure your environment is set up accordingly.

Once the project is compiled, you can run it within Qt Creator. The application interface will allow you to adjust settings and view live CO2 data with the selected averaging method.

## Configuration

- **Averaging Periods:** The user can adjust the averaging periods for SMA and EMA through the settings drawer.
- **Averaging Type:** In the live data view, the user can switch between SMA and EMA by clicking on the respective section.

## Project Structure

The project is organized into several key modules:

### **Sensor Module**
- **I_Sensor, SensorSimulator:** These classes are responsible for simulating CO2 sensor values, providing a consistent stream of data for processing.

### **Data Structures**
- **CircularBuffer, BufferSubscription, I_Subscriber:** Reusable circular buffer structures with subscription possibilities, allowing components to subscribe to data updates.
- **averagerBuffer:** An instance of a circular buffer that stores raw sensor values to be used by the averagers (SMA and EMA).

### **Averager**
- **I_Averager, SMAAverager, EMAAverager:** Interfaces and implementations for calculating averages. `I_Averager` serves as the base interface, with `SMAAverager` and `EMAAverager` providing specific averaging calculations.

### **Data**
- **DataBufferManager:** Manages three circular buffers that store raw, SMA, and EMA values. It handles the data flow between the sensor simulation, the SMA and EMA averagers, and the `TrendDataAPI`. This ensures that data is consistently processed and made available for both real-time display and trend analysis.

### **Backend-Frontend Interface**
- **I_FrontendAPI, LiveDataAPI, TrendDataAPI:** Interfaces and implementations that facilitate communication between the backend data processing modules and the frontend UI, ensuring that data is correctly propagated and displayed.

## Future Enhancements

Several improvements and features are planned for future development:

1. **Introducing Threads:**
   - Sensor Data Thread
   - Data Processing Thread (Averager + Buffer)
   - UI Thread

2. **Unit Tests:** Comprehensive unit tests to ensure code reliability and correctness.

3. **Throttling Mechanism:** Implementing a throttling mechanism in the `FrontendAPI` to optimize data flow and UI performance.

4. **Central Scheduler:** A scheduler to manage timing and synchronization of data processing tasks.

5. **Backend Decoupling from Qt:** Replacing Qt signals with the Observer pattern to make the backend independent of Qt.

## Known Issues and Limitations

- **No Licensing:** The project currently has no associated license.
- **Pending Enhancements:** The project is under active development, with several features still pending implementation as listed above.

## Contact Information

For any issues or questions regarding the project, please contact the project developer directly.
