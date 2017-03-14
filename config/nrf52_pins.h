#ifndef NRF52_PINS_H
#define NRF52_PINS_H

//#define NRF52_DK
#define EE02
#define EE02_EXT_ANT 1
//#define EE02_CHIP_ANT 1

// Channel 1: GPS main power
// Channel 2: GPS VBackup (always on)
// Channel 3: Accelerometer/gyro
// Channel 4: Accelerometer/gyro IO (turn on )

#define TPS22994_GPS_PIN 1
#define TPS22994_VBACKUP_PIN 2
#define TPS22994_MEMS_PIN 3
#define TPS22994_MEMS_IO_PIN 4

#ifdef EE02
    //Platform wide pins
    //I2C
    #define PLAT_I2C_SDA 26
    #define PLAT_I2C_SCL 27

    //SPI (chipselect pr component)
    #define PLAT_SPI_MISO 24
    #define PLAT_SPI_MOSI 23
    #define PLAT_SPI_SCK 25

    // sx1276 pins
    #define SX1276_RXTX_PIN 21
    #define SX1276_RST_PIN 18
    #define SX1276_NSS_PIN 22
    #define SX1276_DIO0_PIN 13
    #define SX1276_DIO1_PIN 14
    #define SX1276_DIO2_PIN 15
    #define SX1276_DIO3_PIN 16
    #define SX1276_DIO4_A_PIN 19
    #define SX1276_DIO4_B_PIN 20

    #define SX1276_ANT_HF_CTRL 27

    #define GPS_RX_PIN 29
    #define GPS_TX_PIN 28
    #define GPS_CTS_PIN -1
    #define GPS_RTS_PIN -1

    // SPI pins for IMU

    #define IMU_CS_M_PIN 6
    #define IMU_CS_AG_PIN 5

#endif
// Configuration for nRF52 DK with sheild and breakout boards.

#ifdef NRF52_DK
//SPI (chipselect pr component)
    #define PLAT_SPI_MISO 24
    #define PLAT_SPI_MOSI 23
    #define PLAT_SPI_SCK 25

    #define PLAT_I2C_SDA 26
    #define PLAT_I2C_SCL 27

    // sx1276 pins
    #define SX1276_RXTX_PIN 30
    #define SX1276_RST_PIN 3
    #define SX1276_NSS_PIN 22
    #define SX1276_DIO0_PIN 13
    #define SX1276_DIO1_PIN 14
    #define SX1276_DIO2_PIN 15
    #define SX1276_DIO3_PIN 16
    #define SX1276_DIO4_A_PIN 19
    #define SX1276_DIO4_B_PIN 29

    
    // RX/TX pins for the GPS UART
    #define GPS_RX_PIN 17
    #define GPS_TX_PIN 18
    #define GPS_CTS_PIN -1
    #define GPS_RTS_PIN -1

    // SPI pins for the IMU
    #define IMU_MISO_PIN 18
    #define IMU_MOSI_PIN 17
    #define IMU_SCK_PIN 16
    #define IMU_CS_M_PIN 19
    #define IMU_CS_AG_PIN 20


#endif

// TODO: Pins for the TPS22994 chip.

#define POWER_CHANNEL_GPS 0
#define POWER_CHANNEL_GPS_BACKUP 1
#define POWER_CHANNEL_MEMS 2
#define POWER_CHANNEL_MEMS_IO 3

#endif

