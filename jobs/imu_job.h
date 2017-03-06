#ifndef IMU_JOB_H
#define IMU_JOB_H

/**
 * Read inteval for IMU.
 */
#define IMU_INTERVAL 30

// I2C addresses for magnetometer + accelerometer/gyro
#define LSM9DS1_M   0x1E // Would be 0x1C if SDO_M is LOW - magnetometer address
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW - accel/gyro address

/**
 * Initialize and start the IMU reading job.
 */
void imu_job_init(void);

#endif
