# SimpleMixerSW

This repository contains the development files for a mixer software and hardware project, split into two main components managed with Vivado and Vitis tools. 

## Structure

The repository is organized into two main directories:

### `Vivado`

This folder houses the Vivado project files for hardware and Programmable Logic development. It includes all necessary design files, constraints, and synthesis configurations required to build the hardware side of the project.

### `Vitis`

The Vitis directory contains the software components of the mixer project, structured as follows:

- **Platform**: Contains the necessary settings and configurations to set up the hardware platform that the software will run on.
- **FreeRTOS Application**: Includes the FreeRTOS-based application code that handles the operational logic for the mixer.
- **First Stage Bootloader (FSBL)**: Provides the initial boot loading mechanism required to prepare the system for the software application.

## Getting Started

To get started with this project, clone the repository and navigate to the respective project directories.

For hardware setup:
```bash
cd Vivado
# Follow specific instructions or scripts here to build the hardware project
