// Negotiation.c

/**
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

/**
 * NegotiateGenerateBGivenHash()
 *
 * EXTRA CREDIT: Choose B to bias coin flip, given commitment hash_a.
 * Count how many possible secrets produce even/odd parity. Pick B = 0 if
 * at least as many even-parity secrets; else pick B = 1.
 *
 * @param hash_a   The received commitment (#a).
 * @return         B value (0 or 1) that biases outcome.
 */
NegotiationData NegotiateGenerateBGivenHash(NegotiationData hash_a)
{
    int countEven = 0, countOdd = 0;
    for (uint32_t candidate = 0; candidate <= 0xFFFF; candidate++)
    {
        if (((candidate * candidate) % PUBLIC_KEY) == hash_a)
        {
            uint16_t temp = candidate;
            uint8_t p = 0;
            for (int i = 0; i < 16; i++)
            {
                p ^= (temp & 1);
                temp >>= 1;
            }
            if (p == 0)
            {
                countEven++;
            }
            else
            {
                countOdd++;
            }
        }
    }
    return (countEven >= countOdd) ? 0 : 1;
}

/**
 * NegotiateGenerateAGivenB()
 *
 * EXTRA CREDIT: Choose A to bias coin flip, given B. (Left unimplemented.)
 *
 * @param B   The accepting agent's number.
 * @return    A value (unused in base credit).
 */
NegotiationData NegotiateGenerateAGivenB(NegotiationData B)
{
    return 0;
}
