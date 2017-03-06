#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "oslmic.h"
#include "nrf52_pins.h"
/*
 * Some quick declarations and wrappers to make the driver easier to port
 */

#define Gpio_t uint8_t
typedef struct Spi_s {
	uint8_t Nss;
} Spi_t;

void GpioWrite(const Gpio_t* pin, const uint8_t high);
uint8_t SpiInOut(const Spi_t* spi, uint8_t data);

typedef struct TimerEvent_s {
	uint8_t timer_id;
	uint32_t ticks;
	bool triggered;
} TimerEvent_t;

typedef void(* TimerEventHandler_t)(void);

void TimerInit(TimerEvent_t* event, const TimerEventHandler_t event_handler);
void TimerStop(const TimerEvent_t* event);
void TimerSetValue(TimerEvent_t* event, const uint32_t ticks);
void TimerStart(const TimerEvent_t* event);
void DelayMs(const uint32_t ms);

#define memcpy1 memcpy

#endif
