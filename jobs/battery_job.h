/**
 * The battery reading job. Reads the battery status every
 * BATTERY_UPDATE_INTERVAL seconds and updates the internal cache with the
 * value.
 */
#ifndef BATTERY_JOB_H
#define BATTERY_JOB_H

/**
 * Read interval for battery. Set to something lower if you want more
 * samples.
 */
#define BATTERY_UPDATE_INTERVAL 300

/**
 * Initialize SAADC and start battery reading job.
 */
void battery_job_init(void);

#endif
