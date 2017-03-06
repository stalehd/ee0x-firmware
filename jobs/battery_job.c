#include "app_error.h"
#include "oslmic.h"

#include "battery_job.h"
#include "battery.h"

/**
 * Job handle for the init job.
 */
static osjob_t batteryjob;

/**
 * Battery update function.
 */
static void battery_func(osjob_t* job) {
    battery_sample();
    uint16_t mv = 0;
    battery_get_mv(&mv);
    NRF_LOG_PRINTF("Read battery: %d mV\n", mv);
    os_setTimedCallback(job, os_getTime() + sec2osticks(BATTERY_UPDATE_INTERVAL), battery_func);
}

void battery_job_init(void) {
  battery_init();

  os_setTimedCallback(&batteryjob, os_getTime() + sec2osticks(5), battery_func);
}
