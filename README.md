# SimpleMixerSW

This repository contains the development files for a mixer software and hardware project, split into two main components managed with Vivado and Vitis tools. The goal of this project is just to explore how the Zynq SoC can be utilized for an audio mixer application. This is a hobby project done in part time and without ANY guarantee that it works in all cases. It is just a showcase and of course the project has been tested and verified with an audio loopback.

## Hardware Requirements for Demo:
- Digilent Zynq 7020 Board ARTY Z7: The hardware project is specifically designed to run on the Digilent Zynq 7020 development board.
- PMOD Audio Adapter Pmod I2S2: This demo requires a PMOD Audio adapter with both input and output jacks.

## Structure

The repository is organized into two main directories:

### `Vivado`

This folder houses the Vivado project files for hardware and Programmable Logic development. It includes all necessary design files, constraints, and synthesis configurations required to build the hardware side of the project. Below is a schematic diagram illustrating the architecture of the hardware setup in the Vivado project. This diagram shows the configuration of all major components and their interconnections, including the Zynq Processing System, various I/O components, and peripheral modules.

![Vivado Hardware Architecture](docs/block_diagram.png)

This diagram is crucial for understanding how the hardware components are integrated and interact within the system.
The Hardware in Vivado utilizes the following IPs:
- Audio Formatter
- I2S Receiver and Transmitter
- Clock Wizard Generator
- GIC (Generic Interrupt Controller)
- I2C driver to a GPIO expansion board

### `Vitis`

The Vitis directory contains the software components of the mixer project, structured as follows:

- **Platform**: Contains the necessary settings and configurations to set up the hardware platform that the software will run on.
- **FreeRTOS Application**: Includes the FreeRTOS-based application code with 3 cyclic tasks (1ms, 10ms, 100ms) and a special audio task.
- **First Stage Bootloader (FSBL)**: Provides the initial boot loading mechanism required to prepare the system for the software application.

**Note:** Working with relative paths in Vitis can be challenging. Users may need to adapt the paths in the project to match their specific setup.

## Getting Started

To get started with this project, clone the repository and navigate to the respective project directories.

For hardware setup:
```bash
cd Vivado
# Follow specific instructions or scripts here to build the hardware project
