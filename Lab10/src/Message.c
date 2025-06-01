/**
 * @file    Message.c
 *
 * Implementation of Message module
 *
 * @author  Kyle Chen
 *
 * @date    29 May 2025
 */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BOARD_H
#include <BOARD.h>
#endif  /*  BOARD_H */

#include "BattleBoats.h"
#include "Message.h"


typedef enum
{
    MSG_DECODE_STATE_WAITING_FOR_START,
    MSG_DECODE_STATE_REC_PAYLOAD,
    MSG_DECODE_STATE_REC_CHECKSUM
} MessageDecodeState;

/**
 * Given a payload string, calculate its checksum.
 * 
 * @param   payload The string whose checksum we wish to calculate.
 * @return  The resulting 8-bit checksum.
 */
uint8_t Message_CalculateChecksum(const char* payload)
{
    uint8_t checksum = 0;
    const unsigned char* payload_ptr = (const unsigned char*) payload;

    for (; *payload_ptr != '\0'; payload_ptr++)
    {
        checksum ^= *payload_ptr;  
    }

    return checksum;
}

/** Message_ParseMessage(*payload, *checksum_string, *message_event)
 *
 * ParseMessage() converts a message string into a BB_Event.  The payload and
 * checksum of a message are passed into ParseMessage(), and it modifies a
 * BB_Event struct in place to reflect the contents of the message.
 * 
 * @param   payload         The payload of a message.
 * @param   checksum        The checksum (in string form) of  a message,
 *                              should be exactly 2 chars long, plus a null
 *                              char.
 * @param   message_event   A BB_Event which will be modified by this function.
 *                          If the message could be parsed successfully,
 *                              message_event's type will correspond to the
 *                              message type and its parameters will match the
 *                              message's data fields.
 *                          If the message could not be parsed, message_events
 *                              type will be BB_EVENT_ERROR.
 * 
 * @return  STANDARD_ERROR if:
 *              the payload does not match the checksum,
 *              the checksum string is not two characters long, or
 *              the message does not match any message template;
 *          SUCCESS otherwise.
 * 
 * @note    Please note!  sscanf() has a couple compiler bugs that make it an
 *          unreliable tool for implementing this function.
 */
int Message_ParseMessage(const char* payload, const char* checksum_string,
        BB_Event* message_event)
{
    char* payload_ptr = (char*) payload;

    if (strlen(checksum_string) != MESSAGE_CHECKSUM_LEN)
    {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }

    uint8_t checksum = (uint8_t) strtoul(checksum_string, (char**) NULL, 16);
    if (Message_CalculateChecksum(payload) != checksum)
    {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }

    if (!strncmp(payload, "CHA,", 4))
    {
        message_event->type = BB_EVENT_CHA_RECEIVED;
        message_event->param0 = (uint16_t) strtoul(payload + 4, NULL, 10);
    }
    else if (!strncmp(payload, "ACC,", 4))
    {
        message_event->type = BB_EVENT_ACC_RECEIVED;
        message_event->param0 = (uint16_t) strtoul(payload + 4, NULL, 10);
    }
    else if (!strncmp(payload, "REV,", 4))
    {
        message_event->type = BB_EVENT_REV_RECEIVED;
        message_event->param0 = (uint16_t) strtoul(payload + 4, NULL, 10);
    }
    else if (!strncmp(payload, "SHO,", 4))
    {
        message_event->type = BB_EVENT_SHO_RECEIVED;
        message_event->param0 = (uint16_t) strtoul(payload + 4, &payload_ptr, 10);
        message_event->param1 = (uint16_t) strtoul(payload_ptr + 1, NULL, 10);
    }
    else if (!strncmp(payload, "RES,", 4))
    {
        message_event->type = BB_EVENT_RES_RECEIVED;
        message_event->param0 = (uint16_t) strtoul(payload + 4, &payload_ptr, 10);
        message_event->param1 = (uint16_t) strtoul(payload_ptr + 1, &payload_ptr, 10);
        message_event->param2 = (uint16_t) strtoul(payload_ptr + 1, NULL, 10);
    }
    else
    {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }

    return SUCCESS;
}

/** Message_Encode(*message_string, message_to_encode)
 *
 * Encodes the coordinate data for a guess into the string `message`. This
 * string must be big enough to contain all of the necessary data. The format is
 * specified in PAYLOAD_TEMPLATE_*, which is then wrapped within the message as
 * defined by MESSAGE_TEMPLATE. 
 * 
 * The final length of this message is then returned. There is no failure mode
 * for this function as there is no checking for NULL pointers.
 * 
 * @param   message             The character array used for storing the output. 
 *                                  Must be long enough to store the entire 
 *                                  string, see MESSAGE_MAX_LEN.
 * @param   message_to_encode   A message to encode
 * @return  The length of the string stored into 'message_string'. Return 0 if
 *          message type is MESSAGE_NONE.
 */
int Message_Encode(char *message_string, Message message_to_encode)
{
    // Recap: Encodes Message datatype into NMEA string
    char payload[MESSAGE_MAX_PAYLOAD_LEN];

    switch (message_to_encode.type)
    {
        case MESSAGE_CHA:
        {
            sprintf(payload, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
            break;
        }
        case MESSAGE_ACC:
        {
            sprintf(payload, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
            break;
        }
        case MESSAGE_REV:
        {
            sprintf(payload, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
            break;
        }
        case MESSAGE_SHO:
        {
            sprintf(payload, PAYLOAD_TEMPLATE_SHO,
                message_to_encode.param0, message_to_encode.param1);
            break;
        }
        case MESSAGE_RES:
        {
            sprintf(payload, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, 
                message_to_encode.param1, message_to_encode.param2);
            break;
        }
        default:
        {
            return -1;
        }
    }

    return sprintf(message_string, MESSAGE_TEMPLATE, payload, 
        Message_CalculateChecksum(payload));

}

/** Message_Decode(char_in, *decoded_message_event)
 *
 * Message_Decode reads one character at a time.  If it detects a full NMEA
 * message, it translates that message into a BB_Event struct, which can be
 * passed to other services.
 * 
 * @param   char_in         The next character in the NMEA0183 message to be
 *                              decoded.
 * @param   decoded_message A pointer to a message struct, used to "return" a
 *                              message:
 *                          If char_in is the last character of a valid message, 
 *                              then decoded_message
 *                              should have the appropriate message type.
 *                          If char_in is the last character of an invalid
 *                              message,
 *                              then decoded_message should have an ERROR type.
 *                          otherwise, it should have type NO_EVENT.
 * @return  SUCCESS if no error was detected,
 *          STANDARD_ERROR if an error was detected.
 * 
 * @note    ANY call to Message_Decode may modify decoded_message.
 * @todo    Make "returned" event variable name consistent.
 */
int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event)
{
    static MessageDecodeState msg_decode_state = MSG_DECODE_STATE_WAITING_FOR_START;
    static char payload[MESSAGE_MAX_PAYLOAD_LEN];
    static char *payload_ptr = payload;
    static char checksum[MESSAGE_CHECKSUM_LEN];
    static char *checksum_ptr = checksum;


    switch (msg_decode_state)
    {
        case MSG_DECODE_STATE_WAITING_FOR_START:
        {
            if (char_in == '$')
            {
                payload_ptr = payload;
                msg_decode_state = MSG_DECODE_STATE_REC_PAYLOAD;
            }
            break;
        }
        case MSG_DECODE_STATE_REC_PAYLOAD:
        {
            if ((payload_ptr - payload) >= MESSAGE_MAX_PAYLOAD_LEN)
            {
                msg_decode_state = MSG_DECODE_STATE_WAITING_FOR_START;
                return STANDARD_ERROR;
            }

            if (char_in == '$' || char_in == '\n')
            {
                msg_decode_state = MSG_DECODE_STATE_WAITING_FOR_START;
                return STANDARD_ERROR;
            }
            else if (char_in == '*')
            {
                checksum_ptr = checksum;
                *payload_ptr = '\0';
                msg_decode_state = MSG_DECODE_STATE_REC_CHECKSUM;
            }
            else
            {
                *payload_ptr = char_in;
                payload_ptr++;
            }
            break;
        }
        case MSG_DECODE_STATE_REC_CHECKSUM:
        {
            if ((checksum_ptr - checksum) >= MESSAGE_CHECKSUM_LEN)
            {
                msg_decode_state = MSG_DECODE_STATE_WAITING_FOR_START;
                return STANDARD_ERROR;
            }

            if ((char_in >= '0' && char_in <= '9') || (char_in >= 'A' && char_in <= 'F'))
            {
                *checksum_ptr = char_in;
                checksum_ptr++;
            }
            else if (char_in == '\n')
            {
                *checksum_ptr = '\0';

                if (Message_ParseMessage(payload, checksum, decoded_message_event) == SUCCESS)
                {
                    msg_decode_state = MSG_DECODE_STATE_WAITING_FOR_START;
                    return SUCCESS;
                }
                else
                {
                    msg_decode_state = MSG_DECODE_STATE_WAITING_FOR_START;
                    return STANDARD_ERROR;
                }
            }
            else
            {
                msg_decode_state = MSG_DECODE_STATE_WAITING_FOR_START;
                return STANDARD_ERROR;
            }
            break;
        }
    }

    return SUCCESS;
}
