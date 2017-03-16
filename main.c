#include <stdbool.h>

#include <nrf_drv_twi.h>
#include <nrf_delay.h>

#include "app_error.h"

/*
**   Copyright 2016 Telenor Digital AS
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**      http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

#include "oslmic.h"
#include "sx-radio.h"

#define LORA_BANDWIDTH                              0         // [0: 125 kHz,
                                                              //  1: 250 kHz,
                                                              //  2: 500 kHz,
                                                              //  3: Reserved]
#define LORA_SPREADING_FACTOR                       9         // [SF7..SF12]
#define LORA_CODINGRATE                             1         // [1: 4/5,
                                                              //  2: 4/6,
                                                              //  3: 4/7,
                                                              //  4: 4/8]
#define LORA_PREAMBLE_LENGTH                        8         // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT                         5         // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON                  false
#define LORA_FHSS_ENABLED                           false  
#define LORA_NB_SYMB_HOP                            4         // Symbols    
#define LORA_IQ_INVERSION_ON                        false
#define LORA_CRC_ENABLED                            true

#if 0
// This is the LF test code. Won't need this for a while
    debug("\r\n     TEST_LF_OUTPUT on SX1276MB1xAS: 14 dBm at 434 MHz \r\n" );
    Radio.SetChannel( 433000000 );
    TxOuputPower = 14;
    Radio.Write( 0x01, 0x88 );
    Radio.Write( 0x3D, 0xA1 );
    Radio.Write( 0x36, 0x01 );
    Radio.Write( 0x1e, 0x08 );
#endif
/**
 * @brief Function for application main entry.
 */
int main(void)
{
    NRF_LOG_INIT();
    NRF_LOG_PRINTF("**** Continuous TX test device (ID = %04x%04x)\n", NRF_FICR->DEVICEID[0], NRF_FICR->DEVICEID[1]);

    os_radio_init();

    uint32_t frequency = 868000000;
    uint8_t txPower = 14;

    // Set pin in tx mode
    hal_pin_rxtx(1);

    NRF_LOG_PRINTF("HF output on radio: %d dBm at %d Hz\n", txPower, frequency);
    Radio.SetChannel( frequency );

    Radio.Write( 0x01, 0x88 );
    Radio.Write( 0x3D, 0xA1 );
    Radio.Write( 0x36, 0x01 );
    Radio.Write( 0x1e, 0x08 );

    Radio.SetTxConfig( MODEM_LORA, txPower, 0, LORA_BANDWIDTH,
                        LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                        LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                        LORA_CRC_ENABLED, LORA_FHSS_ENABLED, LORA_NB_SYMB_HOP, 
                        LORA_IQ_INVERSION_ON, 3000000 );
    
    // Sets the radio in Tx mode
    Radio.Send( NULL, 0 );
 
    NRF_LOG( "Radio sending...\n" );

    while( 1 )
    {
        NRF_LOG(".");
        nrf_delay_ms( 10000 );
    }
}

