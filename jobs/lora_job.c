#include <string.h>
#include "lora_job.h"
#include "lmic.h"
#include "nrf_delay.h"
#include "app_error.h"
#include "data_cache.h"
#include "battery.h"

#if !LORAWAN_OTAA
static u1_t NWSKEY[16] =  LORAWAN_NWKSKEY;
static u1_t APPSKEY[16] = LORAWAN_APPSKEY;
#endif

// application router ID (LSBF)
static const u1_t APPEUI[8]  = LORAWAN_APP_EUI;

// unique device ID (LSBF)
static const u1_t DEVEUI[8]  = LORAWAN_DEVICE_EUI;

// device-specific AES key (derived from device EUI)
// AKA "Application Key" in LoRaWAN lingo.
static const u1_t DEVKEY[16] = LORAWAN_APP_KEY;

// Note: Unused callbacks
// provide application router ID (8 bytes, LSBF)
void os_getArtEui (u1_t* buf) {
    LMIC_reverse_memcpy(buf, APPEUI, 8);
}

// provide device ID (8 bytes, LSBF)
void os_getDevEui (u1_t* buf) {
    LMIC_reverse_memcpy(buf, DEVEUI, 8);
}

// provide device key (16 bytes) q
void os_getDevKey (u1_t* buf) {
    memcpy(buf, DEVKEY, 16);
}

#define MSG_DATA_LEN (sizeof(float) * 4 + sizeof(uint16_t) + sizeof(uint8_t) * 2)

typedef union {
    struct {
        float fix_time;
        float latitude;
        float longitude;
        float altitude;
        uint16_t rssi;
        uint8_t snr;
        uint8_t dummy;
    };
    uint8_t data[MSG_DATA_LEN];
} lora_message_t;

// Default: 14, max 27
#define TXPOWER 14

static int freq = 0;
static int counter = 0;
static void send_frame(void) {
    counter++;
    // The 0xAA...0xFF separator bytes are just for show. Remove in final version
    // (the loriot output can be hard to vgrep in the console)
    uint32_t byte = 0;
    // RSSI/SNR
    LMIC.frame[byte++] = 'R';
    LMIC.frame[byte++] = 'o';
    LMIC.frame[byte++] = 'c';
    LMIC.frame[byte++] = 'k';
    LMIC.frame[byte++] = ' ';
    LMIC.frame[byte++] = 'T';
    LMIC.frame[byte++] = 'h';
    LMIC.frame[byte++] = 'e';
    LMIC.frame[byte++] = ' ';
    LMIC.frame[byte++] = 'N';
    LMIC.frame[byte++] = 'i';
    LMIC.frame[byte++] = 'g';
    LMIC.frame[byte++] = 'h';
    LMIC.frame[byte++] = 't';
    LMIC.frame[byte++] = 0xFF;
    LMIC.frame[byte++] = counter % 255;

    NRF_LOG_PRINTF("LoRa: Sending %d bytes\n", byte);

    int port = 15;
    switch (freq++) {
        case 0:
            port = 12;
            break;
        case 1:
            port = 11;
            break;
        case 2:
            port = 10;
            break;
        case 3:
            port = 9;
            break;
        case 4:
            port = 8;
            break;
        default:
            port = 7;
            freq = 0;
            break;
    }
    if (LMIC_setTxData2( port, LMIC.frame, byte, LORAWAN_CONFIRMED_MSG_ON ) != 0) {
        NRF_LOG_PRINTF("LoRa: *** Error sending frame!\n");
    }
}


static osjob_t sendjob;
static void sendfunc(osjob_t* job) {
    send_frame();
}

static void dump_received_frame() {
    //(LMIC.frame+LMIC.dataBeg, LMIC.dataLen
    NRF_LOG("===== data frame ======== ");
    for (int i = 0; i < LMIC.dataLen; i++) {
        NRF_LOG_PRINTF("%02x ", LMIC.frame[LMIC.dataBeg + i]);
    }
    NRF_LOG_PRINTF("\n");
    NRF_LOG("========================= ");
}


void onEvent (ev_t ev) {
    switch (ev) {
        case EV_SCAN_TIMEOUT:   NRF_LOG("Got event SCAN_TIMEOUT\n"); break;
        case EV_BEACON_FOUND:   NRF_LOG("Got event BEACON_FOUND\n"); break;
        case EV_BEACON_MISSED:  NRF_LOG("Got event BEACON_MISSED\n"); break;
        case EV_BEACON_TRACKED: NRF_LOG("Got event BEACON_TRACKED\n"); break;
        case EV_JOINING:        NRF_LOG("Got event JOINING\n"); break;
        case EV_JOINED:         NRF_LOG("Got event JOINED\n");
            os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(SEND_RATE), sendfunc);
        break;
        case EV_RFU1:           NRF_LOG("Got event RFU1\n"); break;
        case EV_JOIN_FAILED:    NRF_LOG("Got event JOIN_FAILED\n"); break;
        case EV_REJOIN_FAILED:  NRF_LOG("Got event REJOIN_FAILED\n"); break;
        case EV_TXCOMPLETE:
            NRF_LOG("LoRa: Got event TXCOMPLETE\n");
            dump_received_frame();
            os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(SEND_RATE), sendfunc);
            break;
        case EV_LOST_TSYNC:     NRF_LOG("Got event LOST_TSYNC\n"); break;
        case EV_RESET:          NRF_LOG("Got event RESET\n"); break;
        case EV_RXCOMPLETE:     NRF_LOG("Got event RXCOMPLETE\n");
            dump_received_frame();
            break;
        case EV_LINK_DEAD:      NRF_LOG("Got event LINK_DEAD\n"); break;
        case EV_LINK_ALIVE:     NRF_LOG("Got event LINK_ALIVE\n"); break;
        default:
            NRF_LOG("LoRa: Uknown event: %d\n", ev);
            break;
    }
}

static osjob_t initjob;
static void initfunc (osjob_t* job) {
    NRF_LOG("LoRa reset\n");
    LMIC_reset();

    NRF_LOG("LoRa adr mode\n");
    LMIC_setAdrMode( LORAWAN_ADR_ON );

    NRF_LOG("LoRa drtxpow\n");
    LMIC_setDrTxpow(DR_SF7, 20);
    LMIC_setDrTxpow(DR_SF8, 20);
    LMIC_setDrTxpow(DR_SF10, 20);
    LMIC_setDrTxpow(DR_SF12, 20);
    LMIC_setLinkCheckMode(false);
    NRF_LOG_PRINTF("LoRa: Initializing LMiC with device address 0x%08x\n", LORAWAN_DEVICE_ADDRESS);

    #if LORAWAN_OTAA
        NRF_LOG("LoRa: Using OTAA\n");
        LMIC_startJoining();
    #else
        NRF_LOG("LoRa: Pre-provisioned device\n");
        LMIC_setSession(LORAWAN_NET_ID, LORAWAN_DEVICE_ADDRESS, NWSKEY, APPSKEY);
    #endif
    NRF_LOG("LoRa: Init func completed\n");
}

#if DUMP_STATUS
static osjob_t statusjob;
static void statusfunc(osjob_t* job) {
    NRF_LOG_PRINTF("LoRa: SNR = %d,  RSSI = %d, freq = %d, TxRx flags = ",
        LMIC.snr, LMIC.rssi,
        LMIC.freq);
    if (LMIC.txrxFlags & TXRX_ACK) {
        NRF_LOG("ACK ");
    }
    if (LMIC.txrxFlags & TXRX_NACK) {
        NRF_LOG("NACK ");
    }
    if (LMIC.txrxFlags & TXRX_NOPORT) {
        NRF_LOG("NOPORT ");
    }
    if (LMIC.txrxFlags & TXRX_PORT) {
        NRF_LOG("PORT ");
    }
    if (LMIC.txrxFlags & TXRX_DNW1) {
        NRF_LOG("DNW1 ");
    }
    if (LMIC.txrxFlags & TXRX_DNW2) {
        NRF_LOG("DNW2 ");
    }
    if (LMIC.txrxFlags & TXRX_PING) {
        NRF_LOG("PING ");
    }
    NRF_LOG_PRINTF("(0x%08x)\n", LMIC.txrxFlags);
    os_setTimedCallback(job, os_getTime() + sec2osticks(STATUS_RATE), statusfunc);
}
#endif


void lora_job_init(void) {
    os_setCallback(&initjob, initfunc);
    #if DUMP_STATUS
    NRF_LOG("LoRa: Will print status at regular intervals\n");
    os_setTimedCallback(&statusjob, os_getTime() + sec2osticks(STATUS_RATE), statusfunc);
    #endif
    // Only start sending if OTAA is off.
    #if !LORAWAN_OTAA
    os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(SEND_RATE), sendfunc);
    #endif
}
