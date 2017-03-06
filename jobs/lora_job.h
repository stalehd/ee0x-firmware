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
#define LORAWAN_DEVICE_EUI { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

// APB parameters
#define LORAWAN_DEVICE_ADDRESS (uint32_t) 0x01020304
#define LORAWAN_NWKSKEY { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define LORAWAN_APPSKEY { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

// OTAA parameters
#define LORAWAN_APP_KEY { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define LORAWAN_APP_EUI { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

/**
 * Init and start the LoRa sending job.
 */
void lora_job_init(void);

#endif
