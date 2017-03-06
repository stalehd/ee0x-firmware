
#include "app_error.h"
#include "LSM9DS1.h"
#include "data_cache.h"
#include "oslmic.h"
#include "imu_job.h"

/**
 * IMU instance variable.
 */
static imu_t imu;

/**
 * Initialize IMU.
 */
static void imu_init(void) {
    NRF_LOG("Init IMU\n");
    imu_config_t config = {
        .enable_accel = true,
        .enable_mag = true,
        .enable_gyro = false,
        .ag_addr = LSM9DS1_AG,
        .mag_addr = LSM9DS1_M,
        .calibrate = false,
        .low_power_mode = true
    };
    if (!LSM9DS1_init(&imu, &config)) {
        NRF_LOG("*** Error initializing IMU\n");
    }
}

/**
 * Turn on IMU
 */
static void imu_on(void) {
    // TODO: Turn on IMU via TI chip thingy
}

/**
 * Turn off IMU/put to sleep
 */
static void imu_off(void) {
    // TODO: Turn off IMU via TI chip thingy
}

/**
 * Read values from IMU, update cache.
 */
static void imu_process(void) {
    LSM9DS1_readAccel(&imu);
    imu_update_accel(
        LSM9DS1_calcAccel(&imu, imu.ax),
        LSM9DS1_calcAccel(&imu, imu.ay),
        LSM9DS1_calcAccel(&imu, imu.az));

    LSM9DS1_readMag(&imu);
    imu_update_mag(
        LSM9DS1_calcMag(&imu, imu.mx),
        LSM9DS1_calcMag(&imu, imu.my),
        LSM9DS1_calcMag(&imu, imu.mz));

    LSM9DS1_readTemp(&imu);
    imu_update_temp(LSM9DS1_calcTemp(&imu));

}

/**
 * IMU job handle.
 */
static osjob_t imu_job;

/**
 * IMU reading job.
 */
static void imu_func(osjob_t* job) {
    imu_on();
    imu_process();
    imu_off();

    imu_data_t data;
    imu_get_data(&data);
    char tmp[128];
    sprintf(tmp, "IMU: A [%f, %f, %f],  M [%f, %f, %f],  T [%f]\n",
        data.accel_x, data.accel_y, data.accel_z,
        data.mag_x, data.mag_y, data.mag_z,
        data.temperature);
    NRF_LOG(tmp);

    os_setTimedCallback(job, os_getTime() + sec2osticks(IMU_INTERVAL), imu_func);
}

void imu_job_init(void) {
    imu_init();
    os_setTimedCallback(&imu_job, os_getTime(), imu_func);
}
/* ========================================================================== */
