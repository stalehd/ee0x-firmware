/**!brief Initialize the GPS job via the LMiC scheduler */
#ifndef GPS_JOB_H
#define GPS_JOB_H

/**
 * Interval for GPS fix
 */
#define GPS_FIX_INTERVAL 10

#define GPS_FIX_TIMEOUT (GPS_FIX_INTERVAL/2)
#define GPS_WARMUP_TIME 90


/**
 * Processing interval when waiting for fix
 */
#define GPS_PROCESS_INTERVAL 1

/**
 * Initialize the GPS receiver and start the fix checking job.
 */
void gps_job_init(void);

#endif
