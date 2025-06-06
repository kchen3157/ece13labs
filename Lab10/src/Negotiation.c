// Negotiation.c

/**
 * author: Sai Akhil Madurakavi (smadurak)
 * Negotiation.c
 *
 * Implements functions for the coin-flip commitment protocol used in BattleBoats.
 */

#include "Negotiation.h"

NegotiationData NegotiationHash(NegotiationData secret)
{
    return (NegotiationData)(((uint32_t)secret * (uint32_t)secret) % PUBLIC_KEY);
}

int NegotiationVerify(NegotiationData secret, NegotiationData commitment)
{
    return (NegotiationHash(secret) == commitment) ? 1 : 0;
}

NegotiationOutcome NegotiateCoinFlip(NegotiationData A, NegotiationData B)
{
    uint16_t x = A ^ B;
    uint8_t parity = 0;
    for (int i = 0; i < 16; i++)
    {
        parity ^= (x & 1);
        x >>= 1;
    }
    return (parity == 1) ? HEADS : TAILS;
}