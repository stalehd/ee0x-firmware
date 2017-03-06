#ifndef NMEALIB_H
#define NMEALIB_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Maximum size of NMEA buffer
 */
#define MAX_NMEA_BUFFER 254

/**
 * Preamble character.
 */
#define NMEA_PREAMBLE '$'

/**
 * Checksum character
 */
#define NMEA_CHECKSUM '*'

/**
 * Field separator
 */

#define FIELD_SEPARATOR ','

#define CR '\r'
#define LF '\n'

/**
 * The maximum number of fields in a sentence. The number might be a bit
 * conservative if you use all 255 bytes and/or skip a lot of fields.
 * There's probably a proprietary sentence out there that will break this
 * but we're only going to process GGA/GSV/GLL and so on.
 */
#define MAX_NMEA_FIELDS 64

typedef struct {
    uint8_t* fields[MAX_NMEA_FIELDS];       /* array of fields */
    uint8_t field_count;                    /* number of fields */
    uint8_t talker[3];                      /* Sentence talker or 'P' if proprietary */
    uint8_t* type;                          /* sentence type */
} nmea_sentence_t;

/**
 * Add checksum and CRLF to NMEA sentence, overwriting the end. Assumes that
 * either the sentence is 0-terminated, uses another checksum or with CRLF.
 * Will explode if there isn't enough room in the buffer for checksum and CRLF.
 */
void nmea_end(uint8_t* buffer);

/**
 * Parse NMEA sentence in buffer. This will modify the original buffer and
 * insert zero terminators into it.
 *
 * Returns false if the buffer doesn't contain a valid NMEA sentence.
 */
bool nmea_parse(uint8_t* buffer, nmea_sentence_t* output);

#endif
