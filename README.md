# IMU-data-at-insane-speed
To read and write IMU data from a Arduino NIcla Vision at very high sampling rate(~6660hz) is very challenging due to slow operation on the SD card. The procedure to write data to SD card involves opening a file writing the data and then closing it. Although the writing data part itself do not take excessive time, the other operartions does take some constant time which is in milliseconds and can slow down the write operation. Thus I used a multicore-processing approach to write the data to the SD card.

The two core inside of the Arduino Nicla Vision(M4 and M7), both read the sensor data and write it at a assigned memory space, from where the data is written to the SD card.

This is a highly optimized code for writing IMU data on a SD card.
