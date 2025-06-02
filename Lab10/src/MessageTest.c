

#include <stdio.h>
#include <string.h>

#include "BOARD.h"
#include "Message.h"


int main(void)
{
    BOARD_Init();

    //********* Message_CalculateChecksum *********
    printf("Message_CalculateChecksum(\"CAT\")\n\tExpected: 0x56\n\tGot: 0x%02x\n", Message_CalculateChecksum((const char*) "CAT"));
    printf("Message_CalculateChecksum(\"RES,1,0,3\")\n\tExpected: 0x5A\n\tGot: 0x%02x\n", Message_CalculateChecksum((const char*) "RES,1,0,3"));

    //********* Message_ParseMessage *********
    char* payload_uut;
    char* checksum_uut;
    char* msg_uut;
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



    //********* Message_Decode *********
    msg_uut = "$SHO,4,8*58\r\n";
    char* msg_uut_ptr = msg_uut;
    memset(&event_uut, 0, sizeof(BB_Event));

    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        Message_Decode((unsigned char) *msg_uut_ptr, &event_uut);
    }
    
    printf("Using msg \"%s\"\n", msg_uut);
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);


    msg_uut = "$ACC,57203*5E\r\n";
    msg_uut_ptr = msg_uut;
    memset(&event_uut, 0, sizeof(BB_Event));

    for (; *msg_uut_ptr != '\0'; msg_uut_ptr++)
    {
        Message_Decode((unsigned char) *msg_uut_ptr, &event_uut);
    }
    
    printf("Using msg \"%s\"\n", msg_uut);
    printf("\tevent_uut.type:%u\n", event_uut.type);
    printf("\tevent_uut.param0:%u\n", event_uut.param0);
    printf("\tevent_uut.param1:%u\n", event_uut.param1);
    printf("\tevent_uut.param2:%u\n", event_uut.param2);




    //********* Message_Encode *********

    while (TRUE);

    return 0;
}