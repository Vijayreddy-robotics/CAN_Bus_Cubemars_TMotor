# CAN_Bus_Cubemars_TMotor

## Cubemars motors are mainly used in Humanoid robots and Quadruped/legged robots.
CAN Bus protocol is used to communicate with Cubemars AK70 Tmotor using PSoC5 and Cypress MCU Cy8C55xx 

For more details on cubemars motors, Go to the [Motor datasheet](https://github.com/Vijayreddy-robotics/CAN_Bus_Cubemars_TMotor/blob/main/cubemars_datasheet.pdf).

## Controller Area Network (CAN) is a reliable communication protocol enabling microcontrollers and devices to interact in real-time without the need for a host computer. 
CAN Bus communication is widely used in Automotive, aerospace and robotic applications due to the capabilities of 
  1. prioritizing the messages
  2. Error checking and handling
  3. Multi-master capability: Any device can send data and any device can recieve data.

For more details on CAN bus protocol, Go to the [PSoC CAN bus data sheet](https://github.com/Vijayreddy-robotics/CAN_Bus_Cubemars_TMotor/blob/main/Infineon-AN52701_PSoC_3_and_PSoC_5LP-Getting_Started_with_Controller_Area_Network-ApplicationNotes-v13_00-EN.pdf).


 ### We used a **TJA1050 CAN Controller Bus Driver Interface Module** to interface between the Controller Area Network (CAN) protocol controller and the physical bus. The device provides differential transmit capability to the bus and differential receive capability to the CAN controller. 
 
 Data sheet : [TJA1050 CAN Controller Bus Driver Interface Module](https://github.com/Vijayreddy-robotics/CAN_Bus_Cubemars_TMotor/blob/main/TJA1050.pdf)

![me](https://github.com/Vijayreddy-robotics/CAN_Bus_Cubemars_TMotor/blob/main/driver_module.jpg)

Two motors with sinusoidal exication can be observed here:

![me](cubemars2.gif)
