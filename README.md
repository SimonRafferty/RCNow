# RCNow Library for ESP32 Using ESP-NOW

## Overview

The `RCNow` library simplifies the use of ESP-NOW for remote control tasks with the ESP32. It allows the transmission and reception of 16 double-precision numbers, which can be utilized as 16 remote control channels or for returning 16 telemetry values. This library is designed to be compact and easy to use, ensuring low latency and reliable communication.  The same sketch or at least the same library can be used interchangably as the sender or receiver or both.

## Features

- **Send and Receive 16 Double Precision Numbers**: Use the library to send and receive up to 16 double-precision numbers.
- **Conversation ID**: Specify a conversation ID in the `begin` method to ensure that only nodes with the same ID participate in the conversation.
- **Bi-directional Communication**: Enables two-way communication between nodes with the same conversation ID.
- **Low Latency**: Leverages the low latency and error detection capabilities of ESP-NOW for efficient and reliable communication.

## Installation

1. **Download the Library**:
   - Clone or download the library as a ZIP file from the GitHub repository.

2. **Install the Library in Arduino IDE**:
   - Open the Arduino IDE.
   - Go to `Sketch` > `Include Library` > `Add .ZIP Library...`.
   - Select the downloaded ZIP file.

3. **Include the Library in Your Sketch**:
   ```cpp
   #include <RCNow.h>

## Conversation ID

Normally, ESPNow uses MAC addresses to specify the source & destination of messages.  This version uses a 'conversation ID' which is specified in the begin method.  Anyy nodes with the same ID participate in the conversation allowing bi-directional communication within a specific group of nodes.  

Example:

    Node A and Node B both initialize the library with begin(0x1234).
    Node A sends data: rcnow.send(1.1, 2.2, ...);
    Node B receives data because it shares the same conversation ID 0x1234.

Nodes with different IDs will not interfere with each other, allowing multiple independent conversations to take place simultaneously.

## License

This library is released under the MIT License. See the LICENSE file for details.

## Contributions

Contributions are welcome! Please feel free to submit a pull request or open an issue if you have any suggestions or bug reports.
