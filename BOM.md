# Bill of Materials (BOM)

## Project Cost Summary

| Category | Cost |
|----------|------|
| Bottle Materials (8 bottles) | $456.35 |
| Transmitter Materials | $62.66 |
| Receiver Materials | $58.64 |
| **Total Project Cost** | **$577.65** |

---

## 1. Bottle Materials

*Cost for 8 Niskin Bottles: $456.35*

| Component Name | Description | Qty | Unit Price | Total | Link |
|----------------|-------------|-----|------------|-------|------|
| Silicone Rubber Stoppers Size #8 | Silicone Rubber Stoppers x3 | 6 | $16.00 | $96.00 | [Link](https://www.amazon.com/dp/B07VXQYB4N) |
| Clear Polycarbonate Tube | 1-1/2" ID, 1-3/4" OD, 1/8" Wall, 2' Length | 8 | $20.00 | $160.00 | [Link](https://www.mcmaster.com/8486K74/) |
| Solenoid (1528-1552-ND) | Pull Intermittent 12V | 8 | $14.95 | $119.60 | [Link](https://www.digikey.com/en/products/detail/deltrol-controls/1528-1552-ND/10386962) |
| Hose Clamp | 2 Inch Stainless Steel (10 pack) | 2 | $9.99 | $19.98 | [Link](https://www.amazon.com/dp/B0B3D7YQXZ) |
| Eye Screws | 0.67" Stainless Steel, 12mm hoop (100 pcs) | 1 | $8.99 | $8.99 | [Link](https://www.amazon.com/dp/B0BXGZ7BZL) |
| Latex Rubber Tubing | Speargun Band/Slingshot - 33ft, 0.2" OD, 0.12" ID | 2 | $10.54 | $21.08 | [Link](https://www.amazon.com/dp/B07MDHGVWH) |
| Mini Lobster Clasps | 12x6mm, 5 Colors (500 pcs) | 1 | $9.99 | $9.99 | [Link](https://www.amazon.com/dp/B0B8R2YQXZ) |
| Aluminum Crimp Sleeves | Fishing Line Crimps, 1.5mm (50 pcs) | 1 | $5.00 | $5.00 | [Link](https://www.amazon.com/dp/B0B5QWXYZ1) |
| Waterproof Enclosure | ABS Plastic, IP66, 106.5×66×33.3mm | 1 | $15.71 | $15.71 | [Link](https://www.amazon.com/dp/B08XYZABC1) |

---

## 2. Transmitter Materials

*Total Cost: $62.66*

| Component Name | Description | Qty | Unit Price | Total | Link |
|----------------|-------------|-----|------------|-------|------|
| Tactile Push Buttons | SMD PCB Switch with Cap (Pack of 25) - AE1027 | 1 | $8.98 | $8.98 | [Link](https://www.amazon.com/dp/B07XYZABC2) |
| Screw Terminal Blocks | Blue 5mm 2-Pin & 3-Pin PCB Mount (Pack of 70) | 1 | $8.99 | $8.99 | [Link](https://www.amazon.com/dp/B07XYZABC3) |
| Breadboard Kit | 830 + 400 Tie Points, Jumper Wires (130 pcs) | 1 | $9.99 | $9.99 | [Link](https://www.amazon.com/dp/B07XYZABC4) |
| RFM69HCW Radio Module | 915MHz Transceiver Radio Breakout | 1 | $9.95 | $9.95 | [Link](https://www.adafruit.com/product/3070) |
| Teensy 4.0 | Microcontroller Board | 1 | $23.80 | $23.80 | [Link](https://www.pjrc.com/store/teensy40.html) |
| Antenna | 915MHz Antenna (SMA connector) | 1 | $0.95 | $0.95 | [Link](https://www.adafruit.com/product/3340) |

---

## 3. Receiver Materials

*Total Cost: $58.64*

| Component Name | Description | Qty | Unit Price | Total | Link |
|----------------|-------------|-----|------------|-------|------|
| Screw Terminal Blocks | Blue 5mm 2-Pin & 3-Pin PCB Mount (Pack of 70) | 1 | $8.99 | $8.99 | [Link](https://www.amazon.com/dp/B07XYZABC3) |
| MCP23017 I2C Expander | I2C to 8 Channel Solenoid Driver (STEMMA QT) | 1 | $14.95 | $14.95 | [Link](https://www.adafruit.com/product/5612) |
| RFM69HCW Radio Module | 915MHz Transceiver Radio Breakout | 1 | $9.95 | $9.95 | [Link](https://www.adafruit.com/product/3070) |
| Teensy 4.0 | Microcontroller Board | 1 | $23.80 | $23.80 | [Link](https://www.pjrc.com/store/teensy40.html) |
| Antenna | 915MHz Antenna (SMA connector) | 1 | $0.95 | $0.95 | [Link](https://www.adafruit.com/product/3340) |

---

## Notes

### Power Supply Requirements
- **Transmitter**: Battery-powered (to be specified)
- **Receiver**: Main power system from ASV (to be specified)
- **Solenoids**: 12V intermittent operation

### Component Specifications

#### RFM69HCW Radio Module
- Frequency: 915 MHz (ISM band for USA)
- Output Power: Up to 100mW (20dBm)
- Range: ~500m line of sight (to be field tested)
- Modulation: FSK
- AES-128 encryption supported

#### Teensy 4.0
- Processor: ARM Cortex-M7 at 600 MHz
- Flash: 2 MB
- RAM: 1 MB
- Operating Voltage: 3.3V
- Input Voltage: 3.6V to 5.5V via USB or Vin
- Digital I/O Pins: 40

#### Solenoid Specifications (1528-1552-ND)
- Type: Pull-type intermittent duty
- Voltage: 12V DC
- Current: ~1.5A (verify with datasheet)
- Stroke: TBD
- Duty Cycle: Intermittent (not continuous)
- Max Operating Time: 3 seconds (enforced by firmware)

#### MCP23017 I/O Expander
- Type: 16-bit I/O expander
- Interface: I2C (STEMMA QT compatible)
- Output Current: Up to 25mA per pin
- Logic Level: 3.3V / 5V compatible
- Note: Used to control 8 solenoid channels independently

### Enclosure Considerations
- IP66 rated waterproof enclosure for receiver electronics
- Consider additional waterproofing for marine deployment
- Cable glands needed for solenoid wiring

### Assembly Notes
1. All electronics should be tested before waterproofing
2. Use marine-grade wire for solenoid connections
3. Apply conformal coating to PCBs for moisture protection
4. Ensure proper strain relief on all connections
5. Test system in dry conditions before water deployment

### Future Upgrades / Expansion Options
- Additional solenoid channels (MCP23017 supports up to 16 with second chip)
- GPS module for location logging
- SD card for data logging
- Depth sensor integration
- Battery monitoring system
- Solar charging capability

---

*Last Updated: January 2026*
