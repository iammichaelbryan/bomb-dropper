# bomb-dropper
Ground control of airborne attack simulation

# Ground Control of Airborne Attack Simulation

This repository contains a solo project, "Ground Control of Airborne Attack Simulation," developed by Michael Bryan for a systems programming class. The project is a simulation of airborne attack control, allowing users to launch planes, refuel them, and initiate bomb drops.

## Overview

The simulation involves the following functionalities:

- **Launch**: Launch a bomber plane.
- **Refuel**: Refuel an airborne plane.
- **Bomb**: Trigger a bomb drop from an airborne plane.
- **Quit**: Exit the simulation.

## Code Structure

The primary components of the code include:

- **Signal Handling**: The program uses signals (SIGUSR1 and SIGUSR2) for handling bomb drops and refueling.
- **Forking**: The `fork()` system call is employed to create child processes representing airborne planes.

## Usage

To run the simulation, compile and execute the program. The user is prompted to enter commands for launching planes, refueling, initiating bomb drops, or quitting the simulation.

gcc plane.c -o plane
./plane
# Ground Control of Airborne Attack Simulation

This repository contains a solo project, "Ground Control of Airborne Attack Simulation," developed by Michael Bryan for a systems programming class. The project is a simulation of airborne attack control, allowing users to launch planes, refuel them, and initiate bomb drops.

## Commands

- **Launch (l):** Launches a bomber plane.
- **Refuel (r):** Refuels an airborne plane.
- **Bomb (b):** Initiates a bomb drop from an airborne plane.
- **Quit (q):** Exits the simulation.

## Notes

- Fuel consumption and refueling rates are predefined constants in the code.
- Each plane has its own process ID (PID) for identification.
- The simulation provides real-time updates on fuel levels during flight.

## Contributing

This is a solo project; however, contributions, suggestions, and improvements are welcome. Feel free to open issues or pull requests.
