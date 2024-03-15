#!/bin/sh

#Setup for vcan0 and vcan1. 
sudo ip link set vcan0 up type vcan bitrate 50000 
sudo ip link set vcan1 up type vcan bitrate 50000

#Setup for GPIO pin 4 Drivingmode Up pin
echo  4  > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio4/direction
echo true > /sys/class/gpio/gpio4/value
echo falling > /sys/class/gpio/gpio4/edge #detect on falling
cat /sys/class/gpio/gpio4/value #shoulde be 0

#Setup for GPIO pin 14Drivingmode Down pin
echo  14  > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio14/direction
echo true > /sys/class/gpio/gpio14/value
echo falling > /sys/class/gpio/gpio14/edge #detect on falling
cat /sys/class/gpio/gpio14/value #shoulde be 0


#Setup for GPIO pin 22 TapIndex Up pin
echo  22  > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio22/direction
echo true > /sys/class/gpio/gpio22/value
echo falling > /sys/class/gpio/gpio22/edge #detect on falling
cat /sys/class/gpio/gpio22/value #shoulde be 0


#Setup for GPIO pin 23 TapIndex Down pin
echo  23  > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio23/direction
echo true > /sys/class/gpio/gpio23/value
echo falling > /sys/class/gpio/gpio23/edge #detect on falling
cat /sys/class/gpio/gpio23/value #shoulde be 0


#Setup for GPIO pin 3 deadman button pin
echo  3  > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio3/direction
echo true > /sys/class/gpio/gpio3/value
echo falling > /sys/class/gpio/gpio3/edge #detect on falling
cat /sys/class/gpio/gpio3/value #shoulde be 0

#Setup for GPIO pin 2 Hapic Feedback pin
echo  2  > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio2/direction
echo false > /sys/class/gpio/gpio2/value
cat /sys/class/gpio/gpio2/value #shoulde be 0

