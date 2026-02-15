
## The Remora: Project Overview

The Remora is a remote activation system for Niskin bottles mounted on an ASV. The system allows researchers to trigger water sample collection at precise locations (or time periods) without physical contact with the sampling equipment, enabling autonomous or semi-autonomous water sampling operations. 

Specifically it was designed to be mounted on the [WasteShark](https://www.ranmarine.io/wastesharkclassic/) ASV, and collect samples at different time intervals or at user specified locations.

### Key Features

- **Wireless Control**: 915 MHz encrypted RF communication using RFM69HCW modules
- **Eight Channel Channel Operation**: Independent control of up to eight Niskin bottles
- **Safety Features**: Auto-deactivation after 3 seconds to prevent solenoid damage
- **Marine-Ready Design**: Built for deployment on ASV platforms
- **650mL Sample Volume**

## System Architecture

The system consists of two main components:

### Transmitter Unit (Handheld/Base Station)
- Teensy 4.0 microcontroller
- RFM69HCW radio module (915 MHz)
- 8-button control interface
- LED status indicator
- Battery power supply (Or Laptop to power Teensy via USB)

### Receiver Unit (ASV-Mounted)
- Teensy 4.0 microcontroller
- RFM69HCW radio module (915 MHz)
- MCP23X17 I2C I/O expander
- Solenoid driver circuitry
- 2 solenoid valves for Niskin bottle actuation
- Power supply system

## Hardware Components

### Electronics
- **Microcontroller**: Teensy 4.0 (x2)
- **Radio Modules**: RFM69HCW 915MHz (x2)
- **I/O Expander**: Adafruit MCP23X17 (receiver side)
- **Solenoids**: Adafruit 413 SOLENOID PULL INTERMITTENT 12V (x8)
- **Power Supply**: [TBD]

### Mechanical
- Niskin bottle mounting hardware
- Solenoid mounting brackets
- Waterproof enclosures
- Cable assemblies

*Note: Complete Bill of Materials available in `/hardware/BOM.md`*

## Software

### Dependencies
- [[RadioHead Library](http://www.airspayce.com/mikem/arduino/RadioHead/)](http://www.airspayce.com/mikem/arduino/RadioHead/) - RH_RF69 driver
- [[Adafruit MCP23017 Library](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library) - I2C I/O expander

### Communication Protocol

The system uses simple string-based commands over encrypted RF and uses the following scheme for bottles 0 to 8:

| Command | Description |
|---------|-------------|
| `ACTIVATE_0` | Trigger Niskin bottle 0 closure |
| `DEACTIVATE_0` | Release solenoid 0 (auto after 3s) |
| `ACTIVATE_1` | Trigger Niskin bottle 1 closure |
| `DEACTIVATE_1` | Release solenoid 1 (auto after 3s) |


### Operation Sequence

1. User presses button on transmitter
2. Transmitter sends encrypted ACTIVATE command
3. Receiver activates corresponding solenoid
4. LED provides visual feedback
5. After 3 seconds, transmitter sends DEACTIVATE command
6. Solenoid releases, preserving equipment lifespan

## Repository Structure

```
niskin-bottle-asv-project/
├── README.md                          # This file
├── hardware/
│   ├── BOM.md                         # Bill of Materials
│   ├── schematics/                    # Circuit diagrams
│   └── enclosures/                    # Enclosure designs/specs
├── software/
│   ├── transmitter/
│   │   └── Transmitter_2Button/       # Arduino sketch
│   ├── receiver/
│   │   └── Receiver_2Button/          # Arduino sketch
│   └── libraries/                     # Required libraries
├── docs/
│   ├── setup-guide.md                 # Build and setup instructions
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
   git clone https://github.com/[yourusername]/niskin-bottle-asv-project.git
   cd niskin-bottle-asv-project
   ```

2. **Install Dependencies**
   - Install RadioHead library via Arduino Library Manager
   - Install Adafruit MCP23017 library via Arduino Library Manager

3. **Hardware Assembly**
   - Refer to `/docs/setup-guide.md` for detailed assembly instructions
   - See `/hardware/schematics/` for wiring diagrams

4. **Upload Code**
   - Upload `Transmitter_2Button.ino` to transmitter Teensy 4.0
   - Upload `Receiver_2Button.ino` to receiver Teensy 4.0

5. **Configuration**
   - Verify RF frequency matches your region (915 MHz for US)
   - Adjust encryption key if needed (line 64 in both sketches)
   - Modify `DEACTIVATE_DELAY` if different timing required

### Testing

See `/docs/testing-protocol.md` for comprehensive testing procedures.

## Current Development Status

**Project Status**: ~50% Complete

### ✅ Completed
- [x] Wireless communication system (RF69)
- [x] Basic transmitter/receiver firmware
- [x] Two-channel control system
- [x] Auto-deactivation safety feature
- [x] I2C I/O expansion for solenoid control

### 🚧 In Progress
- [ ] ASV integration (w/Power 12V for Solenoid, 3.3 or 5 for Teensy)
- [ ] Build/Assembly Guide
- [ ] Troubleshooting Doc
- [ ] Electronics Box
- [ ] Signal Verification LED
- [ ] Successful Trigger LED
- [ ] Connection Lost LED

### 📋 Planned
- [ ] Extended range testing
- [ ] Multi-bottle expansion (>2 bottles)
- [ ] Water Sample Analysis

## Usage

### Basic Operation

1. **Power On** both transmitter and receiver units
2. **Verify Connection** - LED on receiver should initialize
3. **Trigger Sampling**:
   - Press Button 0 for Niskin bottle 0
   - Press Button 1 for Niskin bottle 1
4. **Monitor Status** - LED flashes confirm transmission
5. **Automatic Deactivation** occurs after 3 seconds

## Technical Specifications

### Radio System
- **Frequency**: 915 MHz (ISM band)
- **Output Power**: 20 dBm (100 mW)
- **Encryption**: AES-128
- **Range**: [To be tested and documented]


### Timing
- **Solenoid Active Time**: 3 seconds (configurable)
- **Button Debounce**: 20 ms
- **Communication Latency**: <100 ms (typical)

## Safety & Best Practices

- Always test system on land before water deployment
- Verify solenoid deactivation to prevent burnout
- Check battery levels before each deployment
- Maintain RF communication line of sight when possible
- Follow marine electronics waterproofing standards
- Ensure rubber band in the tube has enough tension to properly seal the tubes
- Ensure bottle is closing with water tight seal on its own.

## Troubleshooting

Common issues and solutions available in `/docs/troubleshooting.md`

## Future Enhancements

- Integration with ASV navigation system for automated sampling
- Bottle depth design
- Float/Buoy Design

## Contributing

This is a thesis project for the Rutgers Masters in Operational Oceanography Program, but suggestions and improvements are welcome. Please open an issue to discuss proposed changes.

## License

Academic/Research Use

## Author

Elliot C. Brown
Rutgers University, Department of Marine and Coastal Science
elliot.brown,marinetech@gmail.com
## Acknowledgments

- Thesis advisor: Alex Lopez, Max Gorbinov, Oscar Schofield
- Institution: Rutgers University, Department of Marine and Coastal Science
- This project is a continuation of work that was startred by Bohdi Fox ("THE REMORA: A WATER SAMPLING CAPABILITY FOR THE WASTESHARK
AUTONOMOUS SURFACE VEHICLE")
- Bhodi's work was based off the work done by Andrew Thaler of Oceanography is for Everyone and his NISKIN 3D Project (https://github.com/OceanographyforEveryone/Niskin3D)

## References

- RadioHead Library Documentation: http://www.airspayce.com/mikem/arduino/RadioHead/
- Teensy 4.0 Documentation: https://www.pjrc.com/store/teensy40.html
- MCP23017 Datasheet: https://learn.adafruit.com/adafruit-i2c-to-8-channel-solenoid-driver


---s://github.com/[yourusername]/niskin-bottle-asv-project.git
   cd niskin-bot

*Last Updated: January 2026*  
*Project Status: In Development - Thesis Work*
