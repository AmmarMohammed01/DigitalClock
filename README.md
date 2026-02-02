# DigitalClock
## Project Structure
### Archive
- This folder contains code from early to mid 2025.

### CircuitDesign
- This folder contains KiCad hardware design files

### Software/DigitalClock
- This folder contains the microcontroller code, stored as a PlatformIO project

## Project Hardware
Current hardware used:
- ESP32-WROOM-32E
- USB Cable
- OLED I2C
- Breadboard & 4 wires

## How To Use
When plugged in, the time is initially set to 12:00AM, then the time increments each second.<br>

How to set the time:
- First, if you have not already, download and open the LightBlue app.
- Next, connect to the device's bluetooth access point: "Digital Clock"
- Then, "write" the UTF-8 String value in this format "HHMMSSI"
    - HH stands for hours
    - MM stands for minutes
    - SS stands for seconds
    - I stands for isPM: if AM type 0, else if PM type 1
- Example: To set Digital Clock to time 8:53PM, type "0853001"
