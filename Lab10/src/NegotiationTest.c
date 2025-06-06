/**
 * @file    NegotiationTest.c
 * 
 * Testbench for Negotiation module
 *
 * @author  Kyle Chen
 *
 * @date    6 June 2025
 */

#include <stdio.h>
#include "Negotiation.h"

int main(void)
{

    //******** NegotiationHash ********
    printf("Testing NegotiationHash(3)...\n");
    printf("\tExpected: 9\n");
    printf("\tGot: %u\n", (uint16_t) NegotiationHash((NegotiationData) 3));

    printf("Testing NegotiationHash(12345)...\n");
    printf("\tExpected: 43182\n");
    printf("\tGot: %u\n", (uint16_t) NegotiationHash((NegotiationData) 12345));

    //******** NegotiationVerify ********
    printf("Testing NegotiationVerify(3, 9)...\n");
    printf("\tExpected: 1\n");
    printf("\tGot: %d\n", NegotiationVerify(3, 9));
    printf("Testing NegotiationVerify(12345, 43182)...\n");
    printf("\tExpected: 1\n");
    printf("\tGot: %d\n", NegotiationVerify(12345, 43182));
    printf("Testing NegotiationVerify(12345, 13742)...\n");
    printf("\tExpected: 0\n");
    printf("\tGot: %d\n", NegotiationVerify(12345, 13742));

    //******** NegotiationCoinFlip ********
    printf("Testing NegotiateCoinFlip(0b00001011, 0b01100000)...\n");
    printf("\tExpected: 0 (HEADS)\n");
    printf("\tGot: %u\n", NegotiateCoinFlip((NegotiationData) 0b00001011, (NegotiationData) 0b01100000));

    printf("Testing NegotiateCoinFlip(0b10000000, 0b00000001)...\n");
    printf("\tExpected: 1 (TAILS)\n");
    printf("\tGot:%u\n", NegotiateCoinFlip((NegotiationData) 0b10000000, (NegotiationData) 0b00000001));
    return 0;
}