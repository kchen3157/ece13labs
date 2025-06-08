/*
 * AgentTest.c
 *
 * Author: Sai Akhil Madurakavi
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BOARD.h"
#include "Message.h"

// Simple assertion macro
#define ASSERT(cond, msg)              \
    do                                 \
    {                                  \
        if (!(cond))                   \
        {                              \
            printf("FAIL: %s\n", msg); \
            exit(EXIT_FAILURE);        \
        }                              \
    } while (0)

int main(void)
{
    BOARD_Init();

    //********* Message_CalculateChecksum *********
    printf("Running tests on Message_CalculateChecksum...");
    ASSERT(Message_CalculateChecksum((const char *)"CAT") == 0x56,
           "\n\tFAIL: Message_CalculateChecksum(\"CAT\") returns wrong value.\n");
    ASSERT(Message_CalculateChecksum((const char *)"RES,1,0,3") == 0x5A,
           "\n\tFAIL: Message_CalculateChecksum(\"RES,1,0,3\") returns wrong value.\n");
    printf("Passed.\n");

    //********* Message_ParseMessage *********
    char *payload_uut;
    char checksum_uut[4];
    char *msg_str_uut;
    BB_Event event_uut;

    printf("Running tests on Message_ParseMessage...");

    payload_uut = "RES,1,0,3";
    strcpy(checksum_uut, "5A");
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL1: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 7 && event_uut.param0 == 1 && event_uut.param1 == 0 && event_uut.param2 == 3,
           "\n\tFAIL1: Wrong values returned in Event\n");

    payload_uut = "CHA,43182";
    strcpy(checksum_uut, "5A");
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL2: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 3 && event_uut.param0 == 43182,
           "\n\tFAIL2: Wrong values returned in Event\n");

    payload_uut = "ACC,57203";
    strcpy(checksum_uut, "5E");
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL3: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 4 && event_uut.param0 == 57203,
           "\n\tFAIL3: Wrong values returned in Event\n");

    payload_uut = "REV,12345";
    strcpy(checksum_uut, "5C");
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL4: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 5 && event_uut.param0 == 12345,
           "\n\tFAIL4: Wrong values returned in Event\n");

    payload_uut = "SHO,4,8";
    strcpy(checksum_uut, "58");
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL5: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 6 && event_uut.param0 == 4 && event_uut.param1 == 8,
           "\n\tFAIL5: Wrong values returned in Event\n");

    // negative test: bad checksum
    payload_uut = "RES,1,0,3";
    sprintf(checksum_uut, "%x", Message_CalculateChecksum(payload_uut) + 1);
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == STANDARD_ERROR,
           "\n\tFAIL6: Message_ParseMessage incorrectly returned SUCCESS\n");
    ASSERT(event_uut.type == 9,
           "\n\tFAIL6: Did not return Event of type Error (9)\n");

    // negative test: malformed payload (missing column in SHO)
    payload_uut = "SHO,4";
    sprintf(checksum_uut, "%x", Message_CalculateChecksum(payload_uut));
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == STANDARD_ERROR,
           "\n\tFAIL7: Message_ParseMessage incorrectly returned SUCCESS\n");
    ASSERT(event_uut.type == 9,
           "\n\tFAIL7: Did not return Event of type Error (9)\n");

    // negative test: malformed payload (unknown type)
    payload_uut = "XYZ,1,2,3";
    sprintf(checksum_uut, "%x", Message_CalculateChecksum(payload_uut));
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == STANDARD_ERROR,
           "\n\tFAIL8: Message_ParseMessage incorrectly returned SUCCESS\n");
    ASSERT(event_uut.type == 9,
           "\n\tFAIL8: Did not return Event of type Error (9)\n");

    // negative test: malformed payload (too few fields for RES)
    payload_uut = "RES,1,2";
    sprintf(checksum_uut, "%x", Message_CalculateChecksum(payload_uut));
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == STANDARD_ERROR,
           "\n\tFAIL9: Message_ParseMessage incorrectly returned SUCCESS\n");
    ASSERT(event_uut.type == 9,
           "\n\tFAIL9: Did not return Event of type Error (9)\n");

    // negative test: checksum length not equal to 2 (length 1)
    payload_uut = "CHA,123";
    strcpy(checksum_uut, "5"); // length 1
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == STANDARD_ERROR,
           "\n\tFAIL10: Message_ParseMessage incorrectly returned SUCCESS\n");
    ASSERT(event_uut.type == 9,
           "\n\tFAIL10: Did not return Event of type Error (9)\n");

    // negative test: checksum length not equal to 2 (length 3)
    payload_uut = "CHA,123";
    strcpy(checksum_uut, "5A5"); // length 3
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == STANDARD_ERROR,
           "\n\tFAIL11: Message_ParseMessage incorrectly returned SUCCESS\n");
    ASSERT(event_uut.type == 9,
           "\n\tFAIL11: Did not return Event of type Error (9)\n");

    // edge case: CHA with 0
    payload_uut = "CHA,0";
    sprintf(checksum_uut, "%x", Message_CalculateChecksum(payload_uut));
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL12: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 3 && event_uut.param0 == 0,
           "\n\tFAIL12: Wrong values returned in Event\n");

    // edge case: SHO with negative row ("-1" becomes large unsigned)
    payload_uut = "SHO,-1,10";
    sprintf(checksum_uut, "%x", Message_CalculateChecksum(payload_uut));
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL13: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 6 && event_uut.param0 == 65535 && event_uut.param1 == 10,
           "\n\tFAIL13: Wrong values returned in Event\n");

    // edge case: ACC with 65535
    payload_uut = "ACC,65535";
    sprintf(checksum_uut, "%x", Message_CalculateChecksum(payload_uut));
    memset(&event_uut, 0, sizeof(BB_Event));

    ASSERT(Message_ParseMessage(payload_uut, checksum_uut, &event_uut) == SUCCESS,
           "\n\tFAIL14: Message_ParseMessage returned STANDARD_ERROR\n");
    ASSERT(event_uut.type == 4 && event_uut.param0 == 65535,
           "\n\tFAIL14: Wrong values returned in Event\n");

    printf("Passed.\n");

    //********* Message_Decode *********
    printf("Running tests on Message_Decode...");

    // Valid test
    msg_str_uut = "$SHO,4,8*58\r\n";
    char *msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));

    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        ASSERT(Message_Decode((unsigned char)*msg_uut_ptr, &event_uut) == SUCCESS,
               "\n\tFAIL1: Message_Decode returned STANDARD_ERROR\n");
    }
    ASSERT(event_uut.type == 6 && event_uut.param0 == 4 && event_uut.param1 == 8 && event_uut.param2 == 0,
           "\n\tFAIL1: Wrong values returned in Event\n");

    // Valid test
    msg_str_uut = "$ACC,57203*5E\r\n";
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));

    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        ASSERT(Message_Decode((unsigned char)*msg_uut_ptr, &event_uut) == SUCCESS,
               "\n\tFAIL2: Message_Decode returned STANDARD_ERROR\n");
    }
    ASSERT(event_uut.type == 4 && event_uut.param0 == 57203,
           "\n\tFAIL2: Wrong values returned in Event\n");

    // negative test: bad checksum inside full frame
    msg_str_uut = "$SHO,4,8*59\r\n"; // wrong checksum
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));
    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        if (*msg_uut_ptr == '\n') // only check at the end of the str
        {
            ASSERT(Message_Decode((unsigned char)*msg_uut_ptr, &event_uut) == STANDARD_ERROR,
                   "\n\tFAIL3: Message_Decode did not return STANDARD_ERROR\n");
        }
        else
        {
            ASSERT(Message_Decode((unsigned char)*msg_uut_ptr, &event_uut) == SUCCESS,
                   "\n\tFAIL3: Message_Decode returned STANDARD_ERROR prematurely\n");
        }
    }
    ASSERT(event_uut.type == 9,
           "\n\tFAIL3: Message_Decode did not return an error Event (9)\n");

    // negative test: missing '\r' before '\n'
    msg_str_uut = "$SHO,4,8*58\n"; // missing carriage return
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));
    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        ASSERT(Message_Decode((unsigned char)*msg_uut_ptr, &event_uut) == SUCCESS,
               "\n\tFAIL4: Message_Decode returned STANDARD_ERROR\n");
    }
    ASSERT(event_uut.type == 6 && event_uut.param0 == 4 && event_uut.param1 == 8,
           "\n\tFAIL4: Wrong values returned in Event\n");

    // negative test: only one hex digit (one-digit checksum)
    msg_str_uut = "$SHO,4,8*5\r\n";
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));
    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        if (*msg_uut_ptr == '\n') // only check at the end of the str
        {
            ASSERT(Message_Decode((unsigned char)*msg_uut_ptr, &event_uut) == STANDARD_ERROR,
                   "\n\tFAIL5: Message_Decode did not return STANDARD_ERROR\n");
        }
        else
        {
            ASSERT(Message_Decode((unsigned char)*msg_uut_ptr, &event_uut) == SUCCESS,
                   "\n\tFAIL5: Message_Decode returned STANDARD_ERROR prematurely\n");
        }
    }
    ASSERT(event_uut.type == 9,
           "\n\tFAIL5: Message_Decode did not return an error Event (9)\n");

    // negative test: overlong payload before '*'
    {
        char long_payload[MESSAGE_MAX_PAYLOAD_LEN + 2];
        for (int i = 0; i < MESSAGE_MAX_PAYLOAD_LEN + 1; i++)
        {
            long_payload[i] = 'A';
        }
        long_payload[MESSAGE_MAX_PAYLOAD_LEN + 1] = '\0';

        memset(&event_uut, 0, sizeof(BB_Event));
        Message_Decode('$', &event_uut);
        for (int i = 0; i < MESSAGE_MAX_PAYLOAD_LEN + 1; i++)
        {
            Message_Decode((unsigned char)long_payload[i], &event_uut);
        }
        Message_Decode('*', &event_uut);
        Message_Decode('0', &event_uut);
        Message_Decode('0', &event_uut);
        Message_Decode('\r', &event_uut);
        int final = Message_Decode('\n', &event_uut);
        ASSERT(final == 1,
               "\n\tFAIL6: Message_Decode did not return STANDARD_ERROR\n");
    }

    printf("Passed.\n");

    //********* Message_Encode *********
    printf("Running tests on Message_Encode...");

    Message msg_uut;
    char msg_encoded[MESSAGE_MAX_PAYLOAD_LEN];

    memset(&msg_uut, 0, sizeof(msg_uut));
    msg_uut.type = MESSAGE_ACC;
    msg_uut.param0 = 57203;
    Message_Encode(msg_encoded, msg_uut);
    ASSERT(!strcmp(msg_encoded, "$ACC,57203*5E\r\n"),
           "\n\tFAIL1: Message_Encode encoded return is incorrect\n");

    memset(&msg_uut, 0, sizeof(msg_uut));
    msg_uut.type = MESSAGE_RES;
    msg_uut.param0 = 1;
    msg_uut.param1 = 0;
    msg_uut.param2 = 3;
    Message_Encode(msg_encoded, msg_uut);
    ASSERT(!strcmp(msg_encoded, "$RES,1,0,3*5A\r\n"),
           "\n\tFAIL2: Message_Encode encoded return is incorrect\n");

    // negative test: MESSAGE_NONE
    Message msg_none = {.type = MESSAGE_NONE, .param0 = 0, .param1 = 0, .param2 = 0};
    int len_none = Message_Encode(msg_encoded, msg_none);
    ASSERT(len_none == 0,
           "\n\tFAIL3: Message_Encode encoded return is incorrect\n");

    // negative test: invalid MessageType (out-of-range)
    Message msg_bad;
    msg_bad.type = (MessageType)42;
    msg_bad.param0 = 0;
    msg_bad.param1 = 0;
    msg_bad.param2 = 0;
    int len_bad = Message_Encode(msg_encoded, msg_bad);
    ASSERT(len_bad == 0,
           "\n\tFAIL4: Message_Encode encoded return is incorrect\n");

    printf("Passed.\n");

#ifdef STM32F4
    while (TRUE)
        ;
#endif

    return 0;
}
