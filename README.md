farmbot-arduino-controller
==========================
This software is responsible for receiving G-Codes from the Raspberry Pi, execute them and report back the results.

Technicals
==========================
Created with eclipseArduino V2 - For more details see http://www.baeyens.it/eclipse/

Command line flash tool installation
==========================

```
sudo apt-get install gcc-avr avr-libc avrdude python-configobj python-jinja2 python-serial
mkdir tmp
cd tmp
git clone https://github.com/miracle2k/python-glob2
cd python-glob2
wget https://bootstrap.pypa.io/ez_setup.py -O - | sudo python
sudo python setup.py install
git clone git://github.com/amperka/ino.git
cd ino
sudo make install
```

Command line flash tool use
==========================
From the farmbot-arduino-controller directory,
```
ino build
ino upload
```

Software overview
=================

All files are in /src

Farmbot_arduino_controller contains the setup() and main(). This the main sequence:

```
     +--------------------------+
     |farmbot_arduino_controller|
     +-----------+--------------+
                 v
     +--------------------------+
     |Command                   |
     +-----------+--------------+
                 v
     +--------------------------+
     |GCodeProcessor            |
     +-----------+--------------+
                 v
     +--------------------------+
     |***Handler                |
     +-------+-----------+------+
             |           |
             |           +---+
             v               v
     +--------------+   +-----------+
     |StepperControl|   | PinControl|
     +--------------+   +-----------+

```

Codes used for communication
============================

G-Codes
-------


Code type|Number|Parameters|Function
---------|------|----------|--------
         |      |          |
         |      |          |Codes send to the arduino
         |      |          |
G        |      |          |G-Code, the codes working the same as a 3D printer
G        | 0    |X Y Z S   |Move to location at given speed for axis (don't have to be a straight line), in absolute coordinates
G        | 1    |X Y Z S   |Move to location on a straight line
G        |28    |          |Move home all axis
F        |      |          |Farm commands, commands specially added for the farmbot
F        | 1    |T         |Dose amount of water using time in millisecond
F        | 2    |N         |Dose amount of water using flow meter that measures pulses
F        |11    |          |Home X axis
F        |12    |          |Home Y axis
F        |13    |          |Home Z axis
F        |14    |          |Calibrate X axis
F        |15    |          |Calibrate Y axis
F        |16    |          |Calibrate Z axis
F        |21    |P         |Read parameter
F        |22    |P V       |Write parameter
F        |23    |P V       |Update parameter (during calibration)
F        |31    |P         |Read status
F        |32    |P V       |Write status
F        |41    |P V M     |Set a value on an arduino pin
F        |42    |P M       |Read a value from an arduino pin
F        |43    |P M       |Set the mode of a pin in arduino
F        |44    |P V W T   |Set the value V on an arduino pin, wait for time T, set value W on the arduino pin
F        |51    |E P V     |Set a value on the tool mount with I2C
F        |52    |E P       |Read value from the tool mount with I2C
F        |61    |P V       |Set the servo on the pin (only pin 4 and 5) to the requested angle
F        |81    |          |Report end stop
F        |82    |          |Report current position
F        |83    |          |Report software version
E        |      |          |Emergency stop
         |      |          |
         |      |          |Codes received from the arduino
         |      |          |
R        |      |          |Report messages
R        | 1    |          |Current command started
R        | 2    |          |Current command finished succesfully
R        | 3    |          |Current command finished with error
R        | 4    |          |Current command running
R        |21    |P V       |Report parameter value
R        |31    |P V       |Report status value
R        |41    |P V       |Report pin value
R        |81    |X1 X2 Y1 Y2 Z1 Z2|Reporting end stops - parameters: X1 (end stop x axis min) X2 (end stop x axis max) Y1 Y2 Z1 Z2
R        |82    |X Y Z     |Report current position
R        |83    |C         |Report software version
R        |99    |C         |Debug message


Parameters for commands
-----------------------

Parameters|Description            |Unit of Measurement
----------|-----------------------|-------------------
X         |X movement             |steps
Y         |Y movement             |steps
Z         |Z movement	          |steps
S         |Speed                  |steps/second
Q         |Quanity                |counter ticks
T         |Time                   |seconds
C         |Comment                |text
P         |Parameter/pin number   |#
V         |Value number           |#
W         |Secondary value        |#
L         |Number                 |#
E         |Element (in tool mount)|#
M         |Mode (set pin mode)    |0 = output / 1 = input
M         |Mode (read/write)      |0 = digital / 1 = analog
          |                       |
X1        |End stop minimum x axis|0/1
X2        |End stop maximum x axis|0/1
Y1        |End stop minimum y axis|0/1
Y2        |End stop maximum y axis|0/1
Z1        |End stop minimum z axis|0/1
Z2        |End stop maximum z axis|0/1

Arduino paramter numbers
------------------------

Parameter name               |Parameter id
-----------------------------|------------
PARAM_VERSION                |0
MOVEMENT_TIMEOUT_X           |11
MOVEMENT_TIMEOUT_Y           |12
MOVEMENT_TIMEOUT_Z           |13
MOVEMENT_INVERT_ENDPOINTS_X  |21
MOVEMENT_INVERT_ENDPOINTS_Y  |22
MOVEMENT_INVERT_ENDPOINTS_Z  |23
MOVEMENT_INVERT_MOTOR_X      |31
MOVEMENT_INVERT_MOTOR_Y      |32
MOVEMENT_INVERT_MOTOR_Z      |33
MOVEMENT_STEPS_ACC_DEC_X     |41
MOVEMENT_STEPS_ACC_DEC_Y     |42
MOVEMENT_STEPS_ACC_DEC_Z     |43
MOVEMENT_HOME_UP_X           |51
MOVEMENT_HOME_UP_Y           |52
MOVEMENT_HOME_UP_Z           |53
MOVEMENT_MIN_SPD_X           |61
MOVEMENT_MIN_SPD_Y           |62
MOVEMENT_MIN_SPD_Z           |63
MOVEMENT_MAX_SPD_X           |71
MOVEMENT_MAX_SPD_Y           |72
MOVEMENT_MAX_SPD_Z           |73
MOVEMENT_STEPS_PER_UNIT_X    |901 (not in arduino)
MOVEMENT_STEPS_PER_UNIT_Y    |902 (not in arduino)
MOVEMENT_STEPS_PER_UNIT_Z    |903 (not in arduino)
