/**
 * Hardware setup and interface for Firefly X1 receiver. Not a lot of custom
 * code (just a single NMEA sentence to put the chip into sleep mode). Uses the
 * UART.
 */
#include "app_uart.h"

#define PMTK161 "$PMTK161,0*28\r\n"
#define PMTK400 "$PMTK400*36\r\n"

/**
 * Initialise library. Sets up UART and internal event handling.
 */
void gps_init(const app_uart_comm_params_t* uart_params);

/**
 * Wake up receiver.
 */
void gps_wakeup();

/**
 * Put receiver into sleep mode.
 */
void gps_sleep();


