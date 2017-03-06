#ifndef BATTERY_H
#define BATTERY_H
/**
 * @brief Start det SAADC sampler for battery tests.
 */
void battery_init();

/**
 * @brief Sample battery reading.
 *
 * This will eventually update the battery
 * reading that can be read with battery_get_mv().
 */
void battery_sample();

/**
 * @brief Read last battery value, in mV
 *
 * Get last reading from battery, in millivolts. Check the battery's
 * data sheet to determine an approximate percentage of battery level.
 */
void battery_get_mv(uint16_t* milli_volts);

/**
 * @brief Convert millivolts to a value 1-254 (for LoRa)
 *
 * 0 is external power source
 * 1 is minimum
 * 254 is maximum
 * 255 is unavailable
 */
uint8_t battery_to_byte(const uint16_t milli_volts);

/**
 * The discharge curve for the battery isn't known (according to the
 * data sheet for ER17505 it is flat until almost empty, then it drops
 * steeply) so we'll just use a simple linear curve to determine the
 * battery; 1 is empty (3.0V), 255 is max (3.7V or more)
 */
#define MAX_VOLTAGE 3700
#define MIN_VOLTAGE 3000

#endif
