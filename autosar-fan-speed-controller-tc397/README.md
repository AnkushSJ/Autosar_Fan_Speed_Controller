# AUTOSAR-Based Electronic Fan Speed Controller

## Project Overview

The AUTOSAR-Based Electronic Fan Speed Controller is an automotive embedded-systems project based on the AUTOSAR Classic Platform and targeting the Infineon AURIX TC397 microcontroller.

The project aims to control an electric fan using an analog input, such as a potentiometer. The analog signal is acquired through the ADC peripheral, processed by the application software, and used to generate a PWM command for fan-speed control.

The software is organized into AUTOSAR-style layers to separate application logic from hardware-dependent functionality.

## Project Objectives

- Acquire analog input signals using the ADC peripheral.
- Process the acquired signal in the application software.
- Generate PWM output to control fan speed.
- Organize software into modular layers for maintainability and hardware abstraction.
- Apply a structured approach to embedded software design and development.

## System Architecture

```text
       Analog Input
      (Potentiometer)
             |
             v
       ADC Peripheral
             |
             v
         ADC MCAL
             |
             v
          IoHwAb
             |
             v
   Application Software
    (Fan-Speed Logic)
             |
             v
         PWM MCAL
             |
             v
      Fan Driver Circuit
             |
             v
        Electric Fan
```

## AUTOSAR Software Layers

| Layer / Module | Responsibility |
|---|---|
| Application Software (ASW) | Implements the fan-speed control logic. |
| ECU Abstraction (IoHwAb) | Provides application-level access to input and output signals while hiding hardware-specific details. |
| Microcontroller Abstraction Layer (MCAL) | Provides low-level drivers for peripherals such as ADC, PWM, PORT, MCU, and interrupts. |
| Configuration | Holds configuration data for software modules. |
| Startup | Supports system and module initialization. |
| Scheduling | Organizes periodic or event-driven software execution. |

## Repository Structure

```text
autosar-fan-speed-controller-tc397/
|
+-- src/
|   +-- asw/                 Application software
|   +-- iohwab/              ECU signal abstraction
|   +-- mcal/
|   |   +-- adc/             ADC driver
|   |   +-- pwm/             PWM driver
|   |   +-- port/            Port driver
|   |   +-- mcu/             MCU support
|   |   +-- interrupt/       Interrupt support
|   +-- config/              Module configuration
|   +-- startup/             Startup and initialization
|   +-- scheduling/          Scheduling support
|
+-- test/
|   +-- unit/                Unit tests
|   +-- integration/         Integration tests
|   +-- stubs/               Test support stubs
|   +-- host_demo/           Host-side demonstration
|
+-- docs/
|   +-- requirements/        Project requirements
|   +-- architecture/        Architecture documentation
|   +-- design/              Design documentation
|   +-- notes/               Engineering notes
|
+-- traceability/            Requirements traceability
|
+-- README.md
```

## Project Technologies

- **Target Microcontroller:** Infineon AURIX TC397
- **Software Architecture:** AUTOSAR Classic Platform
- **Programming Language:** Embedded C
- **Key Peripherals:** ADC and PWM
- **Focus:** Automotive embedded software and modular driver-based architecture

---
