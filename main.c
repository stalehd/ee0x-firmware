#include <stdbool.h>

#include <nrf_drv_twi.h>

#include "app_error.h"

#include "oslmic.h"

#include "nrf52_pins.h"
#include "gps_job.h"
#include "battery_job.h"
#include "imu_job.h"
#include "lora_job.h"
#include "tps22994.h"

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    NRF_LOG_INIT();
    NRF_LOG_PRINTF("Start main loop. Device ID = %04x%04x\n", NRF_FICR->DEVICEID[0], NRF_FICR->DEVICEID[1]);

    /* really lmic_init */
    os_init();

    NRF_LOG("LMiC HW init complete\n");

    lora_job_init();
    NRF_LOG("LoRa init complete\n");

    os_runloop();

    NRF_LOG("Not here!\n");
}

