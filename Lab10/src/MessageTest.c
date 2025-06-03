

#include <stdio.h>
#include <string.h>

#include "BOARD.h"
#include "Message.h"

int main(void)
{
    BOARD_Init();

    //********* Message_CalculateChecksum *********
    printf("Message_CalculateChecksum(\"CAT\")\n\tExpected: 0x56\n\tGot: 0x%02x\n", Message_CalculateChecksum((const char *)"CAT"));
    printf("Message_CalculateChecksum(\"RES,1,0,3\")\n\tExpected: 0x5A\n\tGot: 0x%02x\n", Message_CalculateChecksum((const char *)"RES,1,0,3"));

    //********* Message_ParseMessage *********
    char *payload_uut;
    char *checksum_uut;
    char *msg_str_uut;
    BB_Event event_uut;

    payload_uut = "RES,1,0,3";
    checksum_uut = "5A";
    memset(&event_uut, 0, sizeof(BB_Event));

    printf("Using payload \"%s\", with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\t%d\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut));
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);

    payload_uut = "CHA,43182";
    checksum_uut = "5A";
    memset(&event_uut, 0, sizeof(BB_Event));

    printf("Using payload \"%s\", with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\t%d\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut));
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);

    payload_uut = "ACC,57203";
    checksum_uut = "5E";
    memset(&event_uut, 0, sizeof(BB_Event));

    printf("Using payload \"%s\", with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\t%d\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut));
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);

    payload_uut = "REV,12345";
    checksum_uut = "5C";
    memset(&event_uut, 0, sizeof(BB_Event));

    printf("Using payload \"%s\", with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\t%d\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut));
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);

    payload_uut = "SHO,4,8";
    checksum_uut = "58";
    memset(&event_uut, 0, sizeof(BB_Event));

    printf("Using payload \"%s\", with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\t%d\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut));
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);

    // negative test: bad checksum
    payload_uut = "RES,1,0,3";
    checksum_uut = "5B";
    memset(&event_uut, 0xFF, sizeof(BB_Event));
    printf("\n[Test] Message_ParseMessage: bad checksum for payload \"%s\" with \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type);

    // negative test: malformed payload (missing column in SHO)
    payload_uut = "SHO,4";
    checksum_uut = "00";
    memset(&event_uut, 0, sizeof(BB_Event));
    printf("\n[Test] Message_ParseMessage: malformed payload \"%s\" (missing col) with \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type);

    // negative test: malformed payload (unknown type)
    payload_uut = "XYZ,1,2,3";
    checksum_uut = "00";
    memset(&event_uut, 0, sizeof(BB_Event));
    printf("\n[Test] Message_ParseMessage: malformed payload \"%s\" (unknown type) with \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type);

    // negative test: malformed payload (too few fields for RES)
    payload_uut = "RES,1,2";
    checksum_uut = "00";
    memset(&event_uut, 0, sizeof(BB_Event));
    printf("\n[Test] Message_ParseMessage: malformed payload \"%s\" (too few fields) with \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type);

    // negative test: checksum length not equal to 2 (length 1)
    payload_uut = "CHA,123";
    checksum_uut = "5"; // length 1
    memset(&event_uut, 0, sizeof(BB_Event));
    printf("\n[Test] Message_ParseMessage: bad checksum length (1) for \"%s\" with \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type);

    // negative test: checksum length not equal to 2 (length 3)
    payload_uut = "CHA,123";
    checksum_uut = "5A5"; // length 3
    memset(&event_uut, 0, sizeof(BB_Event));
    printf("\n[Test] Message_ParseMessage: bad checksum length (3) for \"%s\" with \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type);

    // edge case: CHA with 0
    payload_uut = "CHA,0";
    checksum_uut = "43";
    memset(&event_uut, 0, sizeof(BB_Event));
    printf("\n[Test] Edge case: \"%s\" with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u, param0: %u (expect SUCCESS & BB_EVENT_CHA_RECEIVED, 0)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type, event_uut.param0);

    // edge case: SHO with negative row ("-1" becomes large unsigned)
    payload_uut = "SHO,-1,10";
    checksum_uut = "00"; // arbitrary (incorrect)
    memset(&event_uut, 0xFF, sizeof(BB_Event));
    printf("\n[Test] Edge case: \"%s\" with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u (expect error or well-defined failure)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type);

    // edge case: ACC with 65535
    payload_uut = "ACC,65535";
    checksum_uut = "46";
    memset(&event_uut, 0, sizeof(BB_Event));
    printf("\n[Test] Edge case: \"%s\" with checksum \"%s\"\n", payload_uut, checksum_uut);
    printf("\tReturn: %d, type: %u, param0: %u (expect SUCCESS & BB_EVENT_ACC_RECEIVED, 65535)\n", Message_ParseMessage(payload_uut, checksum_uut, &event_uut), event_uut.type, event_uut.param0);

    //********* Message_Decode *********
    msg_str_uut = "$SHO,4,8*58\r\n";
    char *msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));

    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        Message_Decode((unsigned char)*msg_uut_ptr, &event_uut);
    }

    printf("Using msg \"%s\"\n", msg_str_uut);
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);

    msg_str_uut = "$ACC,57203*5E\r\n";
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));

    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        Message_Decode((unsigned char)*msg_uut_ptr, &event_uut);
    }

    printf("Using msg \"%s\"\n", msg_str_uut);
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);

    // negative test: bad checksum inside full frame
    msg_str_uut = "$SHO,4,8*59\r\n"; // wrong checksum
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0xFF, sizeof(BB_Event));
    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        int ret = Message_Decode((unsigned char)*msg_uut_ptr, &event_uut);
        if (ret == STANDARD_ERROR)
        {
            printf("\n[Test] Message_Decode: bad checksum frame \"%s\"\n", msg_str_uut);
            printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n",
                   ret, event_uut.type);
            break;
        }
    }

    // negative test: missing '\r' before '\n'
    msg_str_uut = "$SHO,4,8*58\n"; // missing carriage return
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0, sizeof(BB_Event));
    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        Message_Decode((unsigned char)*msg_uut_ptr, &event_uut);
    }
    printf("\n[Test] Message_Decode: missing '\\r' for frame \"%s\"\n", msg_str_uut);
    printf("\tevent_uut.type: %u (expect NO_EVENT or BB_EVENT_ERROR)\n", event_uut.type);

    // negative test: only one hex digit (one-digit checksum)
    msg_str_uut = "$SHO,4,8*5\r\n";
    msg_uut_ptr = msg_str_uut;
    memset(&event_uut, 0xFF, sizeof(BB_Event));
    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        int ret = Message_Decode((unsigned char)*msg_uut_ptr, &event_uut);
        if (ret == STANDARD_ERROR)
        {
            printf("\n[Test] Message_Decode: one-digit checksum frame \"%s\"\n", msg_str_uut);
            printf("\tReturn: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n",
                   ret, event_uut.type);
            break;
        }
    }

    // negative test: overlong payload before '*'
    {
        char long_payload[MESSAGE_MAX_PAYLOAD_LEN + 2];
        for (int i = 0; i < MESSAGE_MAX_PAYLOAD_LEN + 1; i++)
        {
            long_payload[i] = 'A';
        }
        long_payload[MESSAGE_MAX_PAYLOAD_LEN + 1] = '\0';

        memset(&event_uut, 0xFF, sizeof(BB_Event));
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
        printf("\n[Test] Message_Decode: overlong payload (len %d)\n", MESSAGE_MAX_PAYLOAD_LEN + 1);
        printf("\tFinal return: %d, type: %u (expect STANDARD_ERROR & BB_EVENT_ERROR)\n",
               final, event_uut.type);
    }

    //********* Message_Encode *********
    Message msg_uut;
    char msg_encoded[MESSAGE_MAX_PAYLOAD_LEN];

    memset(&msg_uut, 0, sizeof(msg_uut));
    msg_uut.type = MESSAGE_ACC;
    msg_uut.param0 = 57203;
    Message_Encode(msg_encoded, msg_uut);
    printf("Trying to encode ACC,57203\n\tResult:\"%s\"\n", msg_encoded);

    memset(&msg_uut, 0, sizeof(msg_uut));
    msg_uut.type = MESSAGE_RES;
    msg_uut.param0 = 1;
    msg_uut.param1 = 0;
    msg_uut.param2 = 3;
    Message_Encode(msg_encoded, msg_uut);
    printf("Trying to encode ACC,57203\n\tResult:\"%s\"\n", msg_encoded);

    // negative test: MESSAGE_NONE
    Message msg_none = {.type = MESSAGE_NONE, .param0 = 0, .param1 = 0, .param2 = 0};
    int len_none = Message_Encode(msg_encoded, msg_none);
    printf("\n[Test] Message_Encode: MESSAGE_NONE\n\tReturned length: %d (expect 0)\n", len_none);

    // negative test: invalid MessageType (out-of-range)
    Message msg_bad;
    msg_bad.type = (MessageType)42;
    msg_bad.param0 = 0;
    msg_bad.param1 = 0;
    msg_bad.param2 = 0;
    int len_bad = Message_Encode(msg_encoded, msg_bad);
    printf("\n[Test] Message_Encode: invalid MessageType (42)\n\tReturned length: %d (expect -1)\n", len_bad);

    while (TRUE)
        ;
    return 0;
}