# The Remora: Remotely Activated Niskin Bottles for Automated Surface Vehicles

A wireless control system for remotely triggering Niskin bottle closures on an Automated Surface Vehicle (ASV), enabling automated water sampling for oceanographic research.

## Project Overview

The Remora is a remote activation system for Niskin bottles mounted on an ASV. The system allows researchers to trigger water sample collection at precise locations or time periods without physical contact with the sampling equipment, enabling autonomous or semi-autonomous water sampling operations. 

Specifically, it was designed to be mounted on the [WasteShark](https://www.ranmarine.io/wastesharkclassic/) ASV and collect samples at different time intervals or at user-specified locations.

### Key Features

- **Wireless Control**: 915 MHz encrypted RF communication using RFM69HCW modules
- **Eight-Channel Operation**: Independent control of up to eight Niskin bottles
- **Safety Features**: Physical enable/disable switch and auto-deactivation after 1 second to prevent solenoid damage
- **Acknowledgment System**: Visual confirmation of successful activation via LED indicators
- **Real-Time Feedback**: Three-color LED system provides instant status updates
- **Marine-Ready Design**: Built for deployment on ASV platforms
- **650mL Sample Volume**: Optimized for water quality analysis

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
- MCP23X17 I2C I/O expander (8-channel output)
- 8 solenoid valves for Niskin bottle actuation
- Onboard LED (Pin 13): Solenoid active indicator
- Power supply system (12V for solenoids, 5V/3.3V for electronics)

## Hardware Components

### Electronics

**Microcontrollers & Communication:**
- **Microcontroller**: Teensy 4.0 (x2)
- **Radio Modules**: RFM69HCW 915MHz (x2)
- **I/O Expander**: Adafruit MCP23X17 (receiver side)
- **Antennas**: 915MHz whip antennas (x2)

**Control & Feedback:**
- **Buttons**: Tactile push buttons (x8) - Transmitter
- **Safety Switch**: SPST toggle switch (x1) - Transmitter
- **Status LEDs**: 5mm LEDs - Yellow, Green, Red (x1 each) - Transmitter
- **LED Resistors**: 220Ω (x3) - Transmitter

**Actuation:**
- **Solenoids**: Adafruit 413 Solenoid Pull Intermittent 12V (x8)
- **Solenoid Driver**: Built into MCP23X17 board or external MOSFET array

**Power:**
- 12V power supply for solenoids
- 5V/3.3V for microcontrollers and logic
- [Specific power supply details TBD]

### Mechanical

- Niskin bottle mounting hardware
- Solenoid mounting brackets
- Waterproof enclosures (IP66 rated)
- Cable assemblies and cable glands
- Rubber stoppers and release mechanisms

*Note: Complete Bill of Materials available in `/hardware/BOM.md`*

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

**Communication Features:**
- AES-128 encryption for security
- 2-second ACK timeout
- Automatic retry capability (future enhancement)
- RSSI monitoring (future enhancement)

### Operation Sequence

1. **User arms system** by flipping safety switch to ARMED position
2. **User presses button** corresponding to desired Niskin bottle (0-7)
3. **Transmitter sends encrypted ACTIVATE command** and flashes yellow LED
4. **Receiver activates corresponding solenoid** and sends ACK
5. **Transmitter receives ACK:**
   - ✅ **Success**: Green LED flashes (1 second)
   - ❌ **Timeout**: Red LED flashes (1 second) - receiver may be out of range
6. **Solenoid remains active for 1 second**, then automatically deactivates
7. **Onboard LEDs** on both units provide visual feedback during activation

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

### ✅ Completed

- [x] Wireless communication system (RFM69HCW)
- [x] Eight-channel control system
- [x] Acknowledgment protocol with visual feedback
- [x] Safety switch implementation
- [x] Auto-deactivation safety feature (1-second solenoid pulse)
- [x] I2C I/O expansion for 8-channel solenoid control
- [x] Three-LED status indication system
- [x] Transmitter/receiver firmware with ACK timeout handling

### 🚧 In Progress

- [ ] ASV integration (12V power for solenoids, 3.3V/5V for Teensy)
- [ ] Comprehensive build/assembly guide update
- [ ] Troubleshooting documentation
- [ ] Waterproof electronics enclosure design
- [ ] Field testing and range validation
- [ ] Power consumption optimization

### 📋 Planned

- [ ] Extended range testing (target: 500m over water)
- [ ] Battery voltage monitoring
- [ ] RSSI (signal strength) monitoring and display
- [ ] Data logging (GPS coordinates, timestamp, bottle number)
- [ ] Integration with WasteShark navigation system
- [ ] Water sample analysis protocols
- [ ] Depth profiling capability
- [ ] Float/buoy design for sample recovery

## Usage

### Basic Operation

1. **Pre-Deployment:**
   - Power on transmitter unit (USB or battery)
   - Power on receiver unit (ASV power system)
   - Verify both units initialize (check Serial Monitor or onboard LEDs)
   - Ensure safety switch is in DISARMED position

2. **Arming the System:**
   - Flip safety switch to ARMED position
   - Serial Monitor displays: "System Armed — buttons active"

3. **Triggering Sampling:**
   - Press button corresponding to desired bottle (0-7)
   - Observe LED feedback:
     - **Yellow flash**: Command transmitted
     - **Green flash**: Success! Bottle activated
     - **Red flash**: Failed! Receiver not responding
   - Serial Monitor shows: "Button X pressed — Solenoid X"

4. **Automatic Deactivation:**
   - Solenoid automatically deactivates after 1 second
   - Preserves solenoid lifespan and prevents overheating

5. **Disarming:**
   - Flip safety switch to DISARMED position when finished
   - Serial Monitor displays: "System Disarmed — buttons disabled"

### LED Status Reference

| LED Color | Meaning | Duration | Action Required |
|-----------|---------|----------|-----------------|
| 🟡 Yellow | Signal transmitted | 1 second | Wait for green or red |
| 🟢 Green | ACK received, bottle activated | 1 second | Success! No action needed |
| 🔴 Red | No ACK, activation failed | 1 second | Move closer or check receiver |
| 💡 Onboard (Pin 13) | Radio transmission | Brief flash | Normal operation |

## Technical Specifications

### Radio System

- **Frequency**: 915 MHz (ISM band)
- **Output Power**: 20 dBm (100 mW)
- **Encryption**: AES-128
- **Modulation**: FSK (Frequency Shift Keying)
- **Range**: 
  - Line of sight: ~500m (to be validated)
  - Over water: ~500m (to be validated)
  - Through obstacles: ~100m (estimated)

### Timing Parameters

- **Solenoid Active Time**: 1 second (configurable in code)
- **ACK Timeout**: 2 seconds
- **LED Flash Duration**: 1 second
- **Button Debounce**: 20 ms
- **Switch Debounce**: 250 ms
- **Communication Latency**: <100 ms (typical)
- **ACK Response Delay**: 200 ms

### Electrical Specifications

**Transmitter:**
- Operating Voltage: 3.3V (via Teensy regulator)
- Input Power: 5V USB or 3.7-5.5V battery
- Current Draw: ~100mA typical, ~200mA during transmission

**Receiver:**
- Logic Voltage: 3.3V/5V
- Solenoid Voltage: 12V DC
- Solenoid Current: ~1.5A per channel (12A max for 8 channels)
- Total System Current: ~200mA (logic) + up to 12A (solenoids)

## Safety & Best Practices

### Electrical Safety

- Always test system on land before water deployment
- Verify solenoid deactivation to prevent burnout
- Use appropriate wire gauge for solenoid current (18 AWG minimum)
- Include fuses in solenoid power circuit (15A recommended)
- Check battery levels before each deployment
- Never exceed 1-second solenoid activation time

### RF Communication

- Maintain RF communication line of sight when possible
- Test range in deployment environment before mission
- Monitor ACK success rate during operation
- Keep antennas vertical and unobstructed
- Follow marine electronics waterproofing standards

### Mechanical Safety

- Ensure rubber band in tube has enough tension to seal properly
- Verify bottle closes with watertight seal on its own
- Inspect solenoid mounting before each deployment
- Check release mechanism for consistent operation
- Test trigger force and stopper release in controlled environment

### Operational Safety

- **Always keep safety switch DISARMED during:**
  - Transport
  - Setup and installation
  - Maintenance
  - When not actively sampling
- Double-check bottle number before activation
- Maintain deployment log with timestamps and locations
- Have backup manual trigger method available

## Troubleshooting

### LED Indicator Troubleshooting

| Symptom | Possible Cause | Solution |
|---------|---------------|----------|
| No LEDs light up | Power issue | Check USB/battery connection |
| Only yellow LED | Receiver offline | Check receiver power and initialization |
| Frequent red LEDs | Out of range | Move units closer or check antenna |
| Yellow + Red | ACK timeout | Check encryption key match, verify receiver running |

### Common Issues

**Red LED (No ACK) Appears:**
- Receiver may be out of range
- Check receiver is powered on and initialized
- Verify encryption keys match on both units
- Check antenna connections
- Reduce distance between units

**Safety Switch Not Working:**
- Verify switch is connected to Pin 16
- Check switch orientation (normally HIGH when disarmed)
- Monitor Serial output for "Armed/Disarmed" messages

**Button Press No Response:**
- Ensure safety switch is ARMED
- Check button wiring and connections
- Verify button pins in code match physical wiring
- Test individual button with multimeter

**Multiple Bottles Activate:**
- This should not occur with current design
- Check for wiring short circuits
- Verify MCP23X17 addressing and connections

For additional troubleshooting, see `/docs/troubleshooting.md`

## Future Enhancements

### Near-Term
- Battery voltage monitoring with low-battery warning LED
- RSSI (signal strength) display
- Solenoid continuity check before deployment
- Waterproof enclosure finalization and testing

### Mid-Term
- Integration with WasteShark navigation system for automated sampling
- GPS coordinate logging with timestamp
- SD card data logging
- Multi-unit support (multiple receivers on one ASV)

### Long-Term
- Depth profiling with pressure sensors
- Temperature and salinity sensors integration
- Autonomous sampling based on sensor triggers
- Satellite communication for remote operation
- Sample recovery float/buoy system

## Contributing

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
