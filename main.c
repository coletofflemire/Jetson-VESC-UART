/*
Implementation of UART communication between a Jetson TX2 with the VESC. 

By Cole Tofflemire
*/

#include <time.h>

// VESC Libraries
#include <string.h>
#include "packet.h"
#include "crc.h"
#include "bldc_interface.h"
#include "bldc_interface_uart.h"
#include "buffer.h"
#include "datatypes.h"

// GPIO Libraries
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gpiolib.h"

#define GPIO_TX 8 // GPIO pin for transmitting
#define GPIO_RX 10 // GPIO pin for receiving

// A function that will send the bytes in *data with length len on the UART
static void send_packet(unsigned char *data, unsigned int len) {
	int bitLen = len * 8;

	for(int bit=0;bit<bitLen;bit++)
	{
		gpio_write(GPIO_TX, ((data >> bit) & 0x01)); // Write data bits to GPIO
		nanosleep(&baud, (struct timespec *)NULL);
	}
}
 
// Init function
void comm_uart_init(void) {
	
	// Initialize GPIO
	gpio_export(GPIO_TX);    
    gpio_direction(GPIO_TX, 1);

	// Initialize timespec for Tx loop
	struct timespec baud = {0};
	baud.tv_sec = 0;
	baud.tv_nsec = 8681L; // Corresponds to baud rate of 115200

	// Initialize the bldc interface and provide send function
	bldc_interface_uart_init(send_packet);
}

// Processing of data received
void bldc_val_received(mc_values *val) {
	
	/*
	printf("Input voltage: %.2f V\r\n", val->v_in);
	printf("Temp:          %.2f degC\r\n", val->temp_pcb);
	printf("Current motor: %.2f A\r\n", val->current_motor);
	printf("Current in:    %.2f A\r\n", val->current_in);
	printf("RPM:           %.1f RPM\r\n", val->rpm);
	printf("Duty cycle:    %.1f %%\r\n", val->duty_now * 100.0);
	printf("Ah Drawn:      %.4f Ah\r\n", val->amp_hours);
	printf("Ah Regen:      %.4f Ah\r\n", val->amp_hours_charged);
	printf("Wh Drawn:      %.4f Wh\r\n", val->watt_hours);
	printf("Wh Regen:      %.4f Wh\r\n", val->watt_hours_charged);
	printf("Tacho:         %i counts\r\n", val->tachometer);
	printf("Tacho ABS:     %i counts\r\n", val->tachometer_abs);
	printf("Fault Code:    %s\r\n", bldc_interface_fault_to_string(val->fault_code));
	*/
}

int main() 
{
	// Initialize timespec for while loop
	struct timespec req = {0};
	req.tv_sec = 0;
	req.tv_nsec = 1000000L; // Sleep time in nanoseconds
	
	// UART Interface
	comm_uart_init();

	// Call bldc_val_received when data is received
	bldc_interface_set_rx_value_func(bldc_val_received);

	while(1) 
	{
		//Set duty cycle:
		//bldc_interface_set_duty_cycle(dutyCycle)

		//Set motor current:
		//bldc_interface_set_current(current)

		//Reboot:
		//bldc_interface_reboot

		//Set motor pos:
		//bldc_interface_set_pos(pos)

		//Set Motor rpm:					(From controller)
		//bldc_interface_set_rpm(rpm)

		//Set servo pos:					(From controller)
		//bldc_interface_set_servo_pos(pos)

		//Read Data:						(TODO)
		//bldc_interface_get_values()
		
		//Every time a byte is received:	(TODO)
		//bldc_interface_uart_process_byte(b)

		bldc_interface_uart_run_timer();
		nanosleep(&req, (struct timespec *)NULL);
	}
	return 0;
}
