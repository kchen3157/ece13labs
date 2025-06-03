// Negotiation.c

/**
 * author: Sai Akhil Madurakavi (smadurak)
 * Negotiation.c
 *
 * Implements functions for the coin-flip commitment protocol used in BattleBoats.
 */

#include "Negotiation.h"

/**
 * NegotiationHash()
 *
 * Compute (secret * secret) mod PUBLIC_KEY.
 *
 * @param secret   The challenge number A.
 * @return         The hash value (#a).
 */
NegotiationData NegotiationHash(NegotiationData secret)
{
    return (NegotiationData)(((uint32_t)secret * (uint32_t)secret) % PUBLIC_KEY);
}

/**
 * NegotiationVerify()
 *
 * Verify that hash(secret) equals the given commitment.
 *
 * @param secret      The revealed secret A.
 * @param commitment  The previously sent hash (#a).
 * @return            1 if match, 0 otherwise.
 */
int NegotiationVerify(NegotiationData secret, NegotiationData commitment)
{
    return (NegotiationHash(secret) == commitment) ? 1 : 0;
}

/**
 * NegotiateCoinFlip()
 *
 * Compute parity of (A XOR B). Parity = 1 → HEADS, else TAILS.
 *
 * @param A    The challenging agent's random number.
 * @param B    The accepting agent's random number.
 * @return     HEADS if parity = 1, otherwise TAILS.
 */
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