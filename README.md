# The Remora: Remotely Activated Niskin Bottles for Automated Surface Vehicles

A wireless control system for remotely triggering Niskin bottle closures on an Automated Surface Vehicle (ASV), enabling automated water sampling for oceanographic research.

## Project Overview

The Remora is a remote activation system for Niskin bottles mounted on an ASV. The system allows researchers to trigger water sample collection at precise locations or time periods without physical contact with the sampling equipment, enabling autonomous or semi-autonomous water sampling operations. 

Specifically, it was designed to be mounted on the [WasteShark](https://www.ranmarine.io/wastesharkclassic/) ASV and collect samples at different time intervals or at user-specified locations.

### Key Features

- **Wireless Control**: 915 MHz communication using ADAFRUIT RFM69HCW modules
- **Eight-Channel Operation**: Independent control of up to eight Niskin bottles
- **Acknowledgment System**: Visual confirmation of successful activation via LED indicators
- **Marine-Ready Design**
- **650mL Sample Volume**

## System Architecture

The system consists of two main components:

### Transmitter Unit (Handheld/Base Station)

**Hardware:**
- Teensy 4.0 microcontroller
- RFM69HCW radio module (915 MHz)
- 8-button control interface (one button per Niskin bottle)
- Safety enable/disable switch
- Three status LEDs:
  - **Yellow**: Signal transmitted
  - **Green**: Acknowledgment received (activation successful)
  - **Red**: No acknowledgment / receiver out of range
- Onboard LED (Pin 13): Transmission indicator
- Battery power supply or laptop USB power

**Control Interface:**
```
Button Layout:
[0] [1] [2] [3]
[4] [5] [6] [7]

Safety Switch: [ARMED/DISARMED]

Status LEDs:
🟡 Yellow - Signal Sent
🟢 Green  - Success (ACK received)
🔴 Red    - Failed (No ACK)
```

### Receiver Unit (ASV-Mounted)

**Hardware:**
- Teensy 4.0 microcontroller
- RFM69HCW radio module (915 MHz)
- MCP23X17 Solenoid Driver Board
- 8 solenoid Actuators
- Power supply system (12V/24V for solenoids, 5V/3.3V for electronics)

## Hardware Components

## Software

### Dependencies

- [RadioHead Library](http://www.airspayce.com/mikem/arduino/RadioHead/) - RH_RF69 driver for RF communication
- [Adafruit MCP23017 Library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library) - I2C I/O expander control

### Communication Protocol

The system uses a simple string-based command protocol over encrypted RF with acknowledgment confirmation.

**Command Structure:**

| Command | Description | Response |
|---------|-------------|----------|
| `ACTIVATE_0` | Trigger Niskin bottle 0 closure | `ACK` |
| `ACTIVATE_1` | Trigger Niskin bottle 1 closure | `ACK` |
| `ACTIVATE_2` | Trigger Niskin bottle 2 closure | `ACK` |
| `ACTIVATE_3` | Trigger Niskin bottle 3 closure | `ACK` |
| `ACTIVATE_4` | Trigger Niskin bottle 4 closure | `ACK` |
| `ACTIVATE_5` | Trigger Niskin bottle 5 closure | `ACK` |
| `ACTIVATE_6` | Trigger Niskin bottle 6 closure | `ACK` |
| `ACTIVATE_7` | Trigger Niskin bottle 7 closure | `ACK` |


### Operation Sequence

1. **User arms system** by flipping safety switch to ARMED position
2. **User presses button** corresponding to desired Niskin bottle (0-7)
3. **Transmitter sends encrypted ACTIVATE command** and flashes yellow LED
4. **Receiver activates corresponding solenoid** and sends ACK
5. **Transmitter receives ACK:**
   -  **Success**: Green LED flashes (1 second)
   -  **Timeout**: Red LED flashes (1 second) - receiver may be out of range
6. **Solenoid remains active for 1 second**, then automatically deactivates (prevents burnout of electronics)


### Safety Switch Operation

The safety switch prevents accidental bottle activation:

**DISARMED Position (Switch OFF):**
- All buttons disabled
- No commands transmitted when buttons pressed
- System status: "System Disarmed — buttons disabled"

**ARMED Position (Switch ON):**
- All buttons active
- Commands transmitted when buttons pressed
- System status: "System Armed — buttons active"

**Best Practice:** Keep switch in DISARMED position during transport, setup, and when not actively sampling.

## Repository Structure

```
The-Remora/
├── README.md                          # This file
├── hardware/
│   ├── BOM.md                         # Bill of Materials
│   ├── schematics/                    # Circuit diagrams
│   └── enclosures/                    # Enclosure designs/specs
├── software/
│   ├── transmitter/
│   │   └── Transmitter_8Button_3LED_Switch/  # Latest transmitter sketch
│   ├── receiver/
│   │   └── Receiver_8Button_3LED_Switch/     # Latest receiver sketch
│   └── libraries/                     # Required libraries info
├── docs/
│   ├── BUILD_INSTRUCTIONS.md          # Build and assembly guide
│   ├── operation-manual.md            # User guide
│   ├── troubleshooting.md             # Common issues and fixes
│   └── testing-protocol.md            # Testing procedures
└── images/                            # Photos and diagrams
```

## Getting Started

### Prerequisites

- Arduino IDE 1.8.x or 2.x with Teensy support
- Teensyduino add-on installed
- Required libraries (see Software section)

### Installation

1. **Clone the Repository**
   ```bash
   git clone https://github.com/[yourusername]/The-Remora.git
   cd The-Remora
   ```

2. **Install Dependencies**
   - Install RadioHead library via Arduino Library Manager
   - Install Adafruit MCP23017 library via Arduino Library Manager

3. **Hardware Assembly**
   - Refer to `/docs/BUILD_INSTRUCTIONS.md` for detailed assembly instructions
   - See `/hardware/schematics/` for wiring diagrams

4. **Upload Code**
   - Upload `Transmitter_8Button_3LED_Switch.ino` to transmitter Teensy 4.0
   - Upload `Receiver_8Button_3LED_Switch.ino` to receiver Teensy 4.0

5. **Configuration**
   - Verify RF frequency matches your region (915 MHz for US)
   - Adjust encryption key if needed (must match on both devices)
   - Modify `SOLENOID_ON_TIME` if different timing required (default: 1000ms)

### Testing

See `/docs/testing-protocol.md` for comprehensive testing procedures.

**Quick Test:**
1. Power both units
2. Open Serial Monitors (115200 baud) on both units
3. Flip safety switch to ARMED
4. Press Button 0
5. Observe LED sequence: Yellow → Green (if successful) or Red (if failed)
6. Check Serial output for confirmation messages

## Current Development Status

**Project Status**: ~75% Complete

###  Completed

- [x] Wireless communication system (RFM69HCW)
- [x] Eight-channel control system
- [x] Acknowledgment protocol with visual feedback
- [x] Safety switch implementation
- [x] Auto-deactivation safety feature (1-second solenoid pulse)
- [x] I2C I/O expansion for 8-channel solenoid control
- [x] Three-LED status indication system
- [x] Transmitter/receiver firmware with ACK timeout handling
- [x] ASV integration (12V power for solenoids, 3.3V/5V for Teensy)

###  In Progress

- [ ] 
- [ ] Comprehensive build/assembly guide update
- [ ] Troubleshooting documentation
- [ ] Waterproof electronics enclosure design
- [ ] Field testing and range validation
- [ ] Power consumption optimization

###  Planned

- [ ] Extended range testing (target: 500m over water)
- [ ] Data logging (GPS coordinates, timestamp, bottle number)
- [ ] Integration with WasteShark navigation system
- [ ] Water sample analysis protocols
- [ ] Float/buoy design for sampeling without 



### LED Indicator Troubleshooting

This is a thesis project for the Rutgers Masters in Operational Oceanography Program, but suggestions and improvements are welcome. Please open an issue to discuss proposed changes.

## License

Academic/Research Use

## Author

**Elliot C. Brown**  
Rutgers University, Department of Marine and Coastal Science  
Email: elliot.brown.marinetech@gmail.com

## Acknowledgments

- **Thesis Advisors**: Alex Lopez, Max Gorbinov, Oscar Schofield
- **Institution**: Rutgers University, Department of Marine and Coastal Science
- **Previous Work**: This project is a continuation of work started by Bodhi Fox ("THE REMORA: A WATER SAMPLING CAPABILITY FOR THE WASTESHARK AUTONOMOUS SURFACE VEHICLE")
- **Foundation**: Bodhi's work was based on the work done by Andrew Thaler of Oceanography for Everyone and his NISKIN 3D Project (https://github.com/OceanographyforEveryone/Niskin3D)

## References

- RadioHead Library Documentation: http://www.airspayce.com/mikem/arduino/RadioHead/
- Teensy 4.0 Documentation: https://www.pjrc.com/store/teensy40.html
- MCP23017 I/O Expander: https://learn.adafruit.com/adafruit-i2c-to-8-channel-solenoid-driver
- WasteShark ASV: https://www.ranmarine.io/wastesharkclassic/
- Niskin 3D Project: https://github.com/OceanographyforEveryone/Niskin3D

---

*Last Updated: January 2026*  
*Project Status: In Development - Thesis Work*  
*Current Version: 8-Channel with ACK System*
