# PZEM004T
Arduino communication library for Peacefair PZEM-004T Energy monitor 

Serial communication    
This module is equipped with TTL serial data communication interface, you can read and set the relevant parameters via the serial port; but if you want to communicate with a device which has USB or RS232 (such as computer), you need to be equipped with different TTL pin board (USB communication needs to be equipped with TTL to USB pin board; RS232 communication needs to be equipped with TTL to RS232 pin board), the specific connection type as shown in Figure 2. In the below table are the communication protocols of this module: 

| No  | Function| Head  |Data1- Data5|Sum|
| ----|:---------:|:----:|----------|:---:|
|1a|Voltage Req|B0|C0 A8 01 01 00 (Computer sends a request to read the voltage value)|1A|
|1b|Voltage Resp|A0|00 E6 02 00 00 (Meter reply the voltage value is 230.2V)|88|
|2a|Current Req|B1|C0 A8 01 01 00 (Computer sends a request to read the current value)|1B|
|2b|Current Resp|A1|00 11 20 00 00 (Meter reply the current value is 17.32A)|D2|
|3a|Active power Req|B2|C0 A8 01 01 00 (Computer sends a request to read the active power value)|1C|
|3b|Active power Resp|A2|08 98 00 00 00 (Meter reply the active power value is 2200w)|42|
|4a|Read energy Req|B3|C0 A8 01 01 00 (Computer sends a request to read the energy value)|1D|
|4b|Read energy Resp|A3|01 86 9f 00 00 (Meter reply the energy value is 99999wh)|C9|
|5a|Set the module address Req|B4|C0 A8 01 01 00 (Computer sends a request to set the address, the address is 192.168.1.1)|1E|
|5b|Set the module address resp|A4|00 00 00 00 00 (Meter reply the address was successfully set)|A4|
|6a|Set the power alarm threshold Req|B5|C0 A8 01 01 14 (computer sends a request to set a power alarm threshold)|33|
|6b|Set the power alarm threshold Resp|A5|00 00 00 00 00 (Meter reply the power alarm threshold  was successfully set)|A5|


Illustration of the communication protocol example: 

1. Set the communication address: 192.168.1.1   
Send command: B4 C0 A8 01 01 00 1E    
Reply data: A4 00 00 00 00 00 A4    
*Note*: The above example illustrate that setting the communication address as 192.168.1.1 (the user can set their own address based on their preferences and needs).    

Sending commands and replying data automatically are as shown above, the data are expressed in hexadecimal; the last byte of the sending and replying data are 1E and A4, belong to cumulative sum. At sending commands: B4 + C0 + A8 + 01 + 01 + 00 = 21E (use the hexadecimal addition), the cumulative sum data is 21E, take the last two bytes 1E to be used the cumulative sum data in sending commands; data in reply: A4 + 00 + 00 + 00 + 00 + 00 = A4 (use the hexadecimal addition),the cumulative sum data is A4,which is the cumulative sum data in reply.    
The explanation of the cumulative sum is now finished, the following parameter examples are the same as this, there is no explanation any more.

2. Set the power alarm threshold:20 KW    
Send command: B5 C0 A8 01 01 14 33    
Reply data: A5 00 00 00 00 00 A5    
*Note*: 14 in the sending command is the alarm value (14 is a hexadecimal data representation, which converted to decimal is 20). What you should note is the power alarm value of this module is based on KW units, which means the minimum alarm value is 1KW, the maximum value is 22KW.    

3. Read the current voltage    
Send command: B0 C0 A8 01 01 00 1A    
Reply data: A0 00 E6 02 00 00 88    
*Note*: Reply voltage data is D1D2D3 = 00 E6 02, 00 E6 represent the integer-bit of the voltage, 02 represent the decimal of the voltage, the decimal is one digit, converts 00 E6 to decimal is 230; converts 02 to decimal is 2, so the current voltage value is 230.2V.    

4. Read the current current    
Send command: B1 C0 A8 01 01 00 1B    
Reply data: A1 00 11 20 00 00 D2    
*Note*: Reply current data is D2D3 = 11 20, 11 represent the integer-bit of the current, 20 represent the decimal of the current, the current decimal is two digits, converts 11 to decimal is 17; converts 20 to decimal is 32, so the current current value is 17.32 A.    

5. Read the current power    
Send command: B2 C0 A8 01 01 00 1C     
Reply data: A2 08 98 00 00 00 42    
*Note*: Reply power data is D1D2 = 08 98, converts 08 98 to decimal is 2200, so the current voltage value is 2200W.    

6. Read the energy    
Send command: B3 C0 A8 01 01 00 1D     
Reply data: A3 01 86 9F 00 00 C9     
*Note*: Reply energy data is D1D2D3 = 01 86 9F, converts 01 86 9F to decimal is 99999, so the accumulated power is 99999Wh.   
