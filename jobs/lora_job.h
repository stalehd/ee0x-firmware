/**
 * LoRa setup and sending. The process itself is very simple and runs in a set
 * loop sending the data cached by the other jobs. Rate is pretty aggressive wrt
 * duty cycle so it should be dialled back a few notches for the final version.
 *
 * In general: Code is quite messy and is more proof-of-concept.
 */
#ifndef LORA_H
#define LORA_H

/**
 * Print status messages
 */
#define DUMP_STATUS 1

/**
 * Send message every N seconds.
 */
#define SEND_RATE 30

/**
 * Dump radio and LoRa status every N seconds
 */
#define STATUS_RATE 30


/**
 * LoRa network ID. ID is 0 for loriot.io (free account)
 */
#define LORAWAN_NET_ID 0x00000000

/**
 * Message ack on/off
 */
#define LORAWAN_CONFIRMED_MSG_ON                    1

/**
 * Port (in LoRa message)
 */
#define LORAWAN_APP_PORT                            13

/**
 * ADR for client on/off
 */
#define LORAWAN_ADR_ON                              1

#define LORAWAN_OTAA 1


/**
 * Public network on/off
 */

#define LORAWAN_PUBLIC_NETWORK true

// Device provisioning - replace this with EUI/device address and NwkSKey + AppSKey as required.

// APB parameters
#define LORAWAN_DEVICE_ADDRESS (uint32_t) 0x01020304
#define LORAWAN_NWKSKEY { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10 }
#define LORAWAN_APPSKEY { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10 }

/*
// OTAA parameters
#define LORAWAN_APP_EUI { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a }
#define LORAWAN_APP_KEY { 0x57, 0x77, 0x32, 0x57, 0x6c, 0x47, 0x79, 0x58, 0x78, 0x4e, 0x78, 0x77, 0x78, 0x72, 0x4a, 0x38 }
#define LORAWAN_DEVICE_EUI { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x66 }
*/
// AppKey: 02bb41c8c9078d1c82fc2172ff022adb
// AppEUI: 00-09-09-00-00-00-00-00
// DevEUI: 00-09-09-00-00-00-00-00
// 
#define LORAWAN_APP_EUI { 0x00, 0x09, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define LORAWAN_APP_KEY { 0x02, 0xbb, 0x41, 0xc8, 0xc9, 0x07, 0x8d, 0x1c, 0x82, 0xfc, 0x21, 0x72, 0xff, 0x02, 0x2a, 0xdb }
#define LORAWAN_DEVICE_EUI { 0x00, 0x09, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00 }

/**
 * Init and start the LoRa sending job.
 */
void lora_job_init(void);

#endif
