# Jetson-VESC-UART
A repo of the files necessary for UART communication between a Jetson TX2 and the VESC.

# VESC 
Obtained the following files directly from https://github.com/vedderb/bldc_uart_comm_stm32f4_discovery:

bldc_interface.c / bldc_interface.h
bldc_interface_uart.c / bldc_interface_uart.h
buffer.c / buffer.h
crc.c / crc.h
packet.c / packet.h
datatypes.h

These files are necessary for the UART template as described here: http://vedder.se/2015/10/communicating-with-the-vesc-using-uart/.

# Jetson GPIO
Obtained the following files directly from https://github.com/embeddedarm/gpio-sysfs-demo:

gpiolib.c / gpiolib.h

These files are necessary for reading and writing GPIO pins on the Jetson.
